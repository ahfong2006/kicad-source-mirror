/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2014 John Beard, john.j.beard@gmail.com
 * Copyright (C) 1992-2014 KiCad Developers, see AUTHORS.txt for contributors.
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

#include <wxPcbStruct.h>
#include <base_units.h>
#include <macros.h>

#include <module_editor_frame.h>

#include "dialog_zone_via_stitching.h"

// initialise statics
DIALOG_ZONE_VIA_STITCHING::ZONE_VIA_STITCHING_OPTIONS DIALOG_ZONE_VIA_STITCHING::m_options;


DIALOG_ZONE_VIA_STITCHING::DIALOG_ZONE_VIA_STITCHING( PCB_BASE_FRAME* aParent ):
    DIALOG_ZONE_VIA_STITCHING_BASE( aParent )
{
    // set the unit labels
    m_spacingUnit->SetLabelText( GetAbbreviatedUnitsLabel( g_UserUnit ) );
    m_diameterUnit->SetLabelText( GetAbbreviatedUnitsLabel( g_UserUnit ) );
    m_drillUnit->SetLabelText( GetAbbreviatedUnitsLabel( g_UserUnit ) );

    // tabbing goes through the entries in sequence
    m_diameterEntry->MoveAfterInTabOrder( m_spacingEntry );
    m_drillEntry->MoveAfterInTabOrder( m_diameterEntry );

    // and set up the entries according to the saved options
    m_spacingEntry->SetValue( wxString::FromDouble( m_options.viaSpacing ) );
    m_diameterEntry->SetValue( wxString::FromDouble( m_options.viaDiameter ) );
    m_drillEntry->SetValue( wxString::FromDouble( m_options.viaDrill ) );

    m_stdButtonsOK->SetDefault();

    GetSizer()->SetSizeHints(this);
}


DIALOG_ZONE_VIA_STITCHING::~DIALOG_ZONE_VIA_STITCHING()
{
}


void DIALOG_ZONE_VIA_STITCHING::OnCancelClick( wxCommandEvent& event )
{
    EndModal( wxID_ABORT );
}


void DIALOG_ZONE_VIA_STITCHING::OnOkClick( wxCommandEvent& event )
{
    if ( ok )
    {
        // save the settings
        m_spacingEntry->GetValue().ToDouble( &m_options.viaSpacing );
        m_diameterEntry->GetValue().ToDouble( &m_options.viaDiameter );
        m_drillEntry->GetValue().ToDouble( &m_options.viaDrill );

        EndModal( wxID_OK);
    }
}


void DIALOG_ZONE_VIA_STITCHING::OnTextFocusLost( wxFocusEvent& event )
{
    wxTextCtrl* obj = static_cast<wxTextCtrl*>( event.GetEventObject() );

    if( obj->GetValue().IsEmpty() )
        obj->SetValue("0");

    event.Skip();
}
