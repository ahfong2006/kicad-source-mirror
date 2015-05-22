/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file drag_round_corner.cpp
 * @brief Routines used to create round trace corners
 */

#include <fctsys.h>
#include <class_drawpanel.h>
#include <confirm.h>
#include <wxPcbStruct.h>
#include <trigo.h>
#include <macros.h>
#include <gr_basic.h>

#include <class_board.h>

#include <pcbnew.h>
#include <drc_stuff.h>
#include <drag.h>
#include <pcbnew_id.h>

#define N_SEGMENTS 32

static void Show_MoveNode( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aPosition,
                           bool aErase );
static void Abort_CreateRoundTrack( EDA_DRAW_PANEL* Panel, wxDC* DC );

static wxPoint s_LastPos;

static PICKED_ITEMS_LIST s_ItemsListPicker;


/** Abort function for creating a round track corner
 */
static void Abort_CreateRoundTrack( EDA_DRAW_PANEL* aPanel, wxDC* aDC )
{
    PCB_EDIT_FRAME* frame = (PCB_EDIT_FRAME*) aPanel->GetParent();
    BOARD * pcb = frame->GetBoard();

    pcb->HighLightOFF();
    pcb->PopHighLight();

    frame->SetCurItem( NULL );
    aPanel->SetMouseCapture( NULL, NULL );

    // Undo move and redraw trace segments.
    for( unsigned jj=0 ; jj < g_DragSegmentList.size(); jj++ )
    {
        TRACK* track = g_DragSegmentList[jj].m_Track;
        g_DragSegmentList[jj].RestoreInitialValues();
        track->SetState( IN_EDIT, false );
        track->ClearFlags();
    }

    // Clear the undo picker list:
    s_ItemsListPicker.ClearListAndDeleteItems();
    EraseDragList();
    aPanel->Refresh();
}


// Redraw the moved node according to the mouse cursor position
static void Show_MoveNode( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aPosition,
                           bool aErase )
{
    DISPLAY_OPTIONS* displ_opts = (DISPLAY_OPTIONS*) aPanel->GetDisplayOptions();
    wxPoint      moveVector;
    int          tmp = displ_opts->m_DisplayPcbTrackFill;
    GR_DRAWMODE  draw_mode = GR_XOR | GR_HIGHLIGHT;

    displ_opts->m_DisplayPcbTrackFill = false;

#ifndef USE_WX_OVERLAY
    aErase = true;
#else
    aErase = false;
#endif

    // set the new track coordinates
    wxPoint Pos = aPanel->GetParent()->GetCrossHairPosition();

    moveVector = Pos - s_LastPos;
    s_LastPos  = Pos;

    TRACK *track = NULL;

    for( unsigned ii = 0; ii < g_DragSegmentList.size(); ii++ )
    {
        track = g_DragSegmentList[ii].m_Track;

        if( aErase )
            track->Draw( aPanel, aDC, draw_mode );

        if( track->GetFlags() & STARTPOINT )
            track->SetStart( track->GetStart() + moveVector );

        if( track->GetFlags() & ENDPOINT )
            track->SetEnd( track->GetEnd() + moveVector );

        if( track->Type() == PCB_VIA_T )
            track->SetEnd( track->GetStart() );

        track->Draw( aPanel, aDC, draw_mode );
    }

    displ_opts->m_DisplayPcbTrackFill = tmp;

    // Display track length
    if( track )
    {
        PCB_BASE_FRAME* frame = (PCB_BASE_FRAME*) aPanel->GetParent();
        frame->SetMsgPanel( track );
    }
}

void PCB_EDIT_FRAME::Start_DragRoundCorner( TRACK* aTrack, wxDC* aDC )
{
    if( !aTrack )
        return;

    EraseDragList();

    // Change highlighted net: the new one will be highlighted
    GetBoard()->PushHighLight();

    if( GetBoard()->IsHighLightNetON() )
        HighLight( aDC );

    STATUS_FLAGS diag = aTrack->IsPointOnEnds( GetCrossHairPosition(), -1 );

    //Start by breaking first segment into N_SEGMENTS different segments
    PICKED_ITEMS_LIST itemsListPicker;
    wxPoint start_point = aTrack->GetStart();
    wxPoint end_point = aTrack->GetEnd();
    for(int ii=0; ii < N_SEGMENTS; ii++){
        double fraction_down_line = (double)(N_SEGMENTS-ii)/(N_SEGMENTS+1);
        wxPoint pos = (start_point*(1.0-fraction_down_line)) + (end_point*fraction_down_line);
        GetBoard()->CreateLockPoint(pos, aTrack, &itemsListPicker);
    }

    wxPoint pos;

    pos = (diag & STARTPOINT) ? aTrack->GetStart() : aTrack->GetEnd();
    //Collect_TrackSegmentsToDrag( GetBoard(), pos, aTrack->GetLayerSet(),
    //                             aTrack->GetNetCode(), aTrack->GetWidth() / 2 );
    wxPoint PosInit = pos;

    aTrack->SetFlags( IS_DRAGGED );

    // Prepare the Undo command
    ITEM_PICKER picker( aTrack, UR_CHANGED );
    picker.SetLink( aTrack->Clone() );
    s_ItemsListPicker.PushItem( picker );

    for( unsigned ii = 0; ii < g_DragSegmentList.size(); ii++ )
    {
        TRACK* draggedtrack = g_DragSegmentList[ii].m_Track;
        picker.SetItem( draggedtrack );
        picker.SetLink( draggedtrack->Clone() );
        s_ItemsListPicker.PushItem( picker );
        draggedtrack = (TRACK*) picker.GetLink();
        draggedtrack->SetStatus( 0 );
        draggedtrack->ClearFlags();
    }

    s_LastPos = PosInit;
    m_canvas->SetMouseCapture( Show_MoveNode, Abort_CreateRoundTrack );

    GetBoard()->SetHighLightNet( aTrack->GetNetCode() );
    GetBoard()->HighLightON();

    GetBoard()->DrawHighLight( m_canvas, aDC, GetBoard()->GetHighLightNetCode() );
    m_canvas->CallMouseCapture( aDC, wxDefaultPosition, true );

    UndrawAndMarkSegmentsToDrag( m_canvas, aDC );
}

// Place a dragged (or moved) track segment or via
bool PCB_EDIT_FRAME::PlaceRoundTrackSegment( TRACK* Track, wxDC* DC )
{
    int        errdrc;

    if( Track == NULL )
        return false;

    int current_net_code = Track->GetNetCode();

    // DRC control:
    if( g_Drc_On )
    {
        errdrc = m_drc->Drc( Track, GetBoard()->m_Track );

        if( errdrc == BAD_DRC )
            return false;

        // Redraw the dragged segments
        for( unsigned ii = 0; ii < g_DragSegmentList.size(); ii++ )
        {
            errdrc = m_drc->Drc( g_DragSegmentList[ii].m_Track, GetBoard()->m_Track );

            if( errdrc == BAD_DRC )
                return false;
        }
    }

    // DRC Ok: place track segments
    Track->ClearFlags();
    Track->SetState( IN_EDIT, false );

    // Draw dragged tracks
    for( unsigned ii = 0; ii < g_DragSegmentList.size(); ii++ )
    {
        Track = g_DragSegmentList[ii].m_Track;
        Track->SetState( IN_EDIT, false );
        Track->ClearFlags();

        /* Test the connections modified by the move
         *  (only pad connection must be tested, track connection will be
         * tested by TestNetConnection() ) */
        LSET layerMask( Track->GetLayer() );

        Track->start = GetBoard()->GetPadFast( Track->GetStart(), layerMask );

        if( Track->start )
            Track->SetState( BEGIN_ONPAD, true );
        else
            Track->SetState( BEGIN_ONPAD, false );

        Track->end = GetBoard()->GetPadFast( Track->GetEnd(), layerMask );

        if( Track->end )
            Track->SetState( END_ONPAD, true );
        else
            Track->SetState( END_ONPAD, false );
    }

    EraseDragList();

    SaveCopyInUndoList( s_ItemsListPicker, UR_UNSPECIFIED );
    s_ItemsListPicker.ClearItemsList(); // s_ItemsListPicker is no more owner of picked items

    GetBoard()->PopHighLight();

    OnModify();
    m_canvas->SetMouseCapture( NULL, NULL );

    if( current_net_code > 0 )
        TestNetConnection( DC, current_net_code );

    m_canvas->Refresh();

    return true;
}
