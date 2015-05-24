///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 23 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialog_zone_via_stitching_base.h"

///////////////////////////////////////////////////////////////////////////

DIALOG_ZONE_VIA_STITCHING_BASE::DIALOG_ZONE_VIA_STITCHING_BASE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DIALOG_SHIM( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bMainSizer;
	bMainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_spacingLabel = new wxStaticText( this, wxID_ANY, _("Via Spacing:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_spacingLabel->Wrap( -1 );
	fgSizer2->Add( m_spacingLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_spacingEntry = new wxTextCtrl( this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_spacingEntry, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spacingUnit = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_spacingUnit->Wrap( -1 );
	fgSizer2->Add( m_spacingUnit, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	m_diameterLabel = new wxStaticText( this, wxID_ANY, _("Via Diameter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_diameterLabel->Wrap( -1 );
	fgSizer2->Add( m_diameterLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_diameterEntry = new wxTextCtrl( this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_diameterEntry, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_diameterUnit = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_diameterUnit->Wrap( -1 );
	fgSizer2->Add( m_diameterUnit, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_drillLabel = new wxStaticText( this, wxID_ANY, _("Via Drill Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_drillLabel->Wrap( -1 );
	fgSizer2->Add( m_drillLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_drillEntry = new wxTextCtrl( this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_drillEntry, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_drillUnit = new wxStaticText( this, wxID_ANY, _("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_drillUnit->Wrap( -1 );
	fgSizer2->Add( m_drillUnit, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bMainSizer->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bMainSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_stdButtons = new wxStdDialogButtonSizer();
	m_stdButtonsOK = new wxButton( this, wxID_OK );
	m_stdButtons->AddButton( m_stdButtonsOK );
	m_stdButtonsCancel = new wxButton( this, wxID_CANCEL );
	m_stdButtons->AddButton( m_stdButtonsCancel );
	m_stdButtons->Realize();
	
	bMainSizer->Add( m_stdButtons, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bMainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnClose ) );
	m_spacingEntry->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnTextFocusLost ), NULL, this );
	m_diameterEntry->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnTextFocusLost ), NULL, this );
	m_drillEntry->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnTextFocusLost ), NULL, this );
	m_stdButtonsCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnCancelClick ), NULL, this );
	m_stdButtonsOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnOkClick ), NULL, this );
}

DIALOG_ZONE_VIA_STITCHING_BASE::~DIALOG_ZONE_VIA_STITCHING_BASE()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnClose ) );
	m_spacingEntry->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnTextFocusLost ), NULL, this );
	m_diameterEntry->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnTextFocusLost ), NULL, this );
	m_drillEntry->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnTextFocusLost ), NULL, this );
	m_stdButtonsCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnCancelClick ), NULL, this );
	m_stdButtonsOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_ZONE_VIA_STITCHING_BASE::OnOkClick ), NULL, this );
	
}
