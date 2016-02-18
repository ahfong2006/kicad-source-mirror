///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 23 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOG_ZONE_VIA_STITCHING_BASE_H__
#define __DIALOG_ZONE_VIA_STITCHING_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class DIALOG_SHIM;

#include "dialog_shim.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_ZONE_VIA_STITCHING_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_ZONE_VIA_STITCHING_BASE : public DIALOG_SHIM
{
	private:
	
	protected:
		wxStaticText* m_spacingLabel;
		wxTextCtrl* m_spacingEntry;
		wxStaticText* m_spacingUnit;
		wxStaticText* m_diameterLabel;
		wxTextCtrl* m_diameterEntry;
		wxStaticText* m_diameterUnit;
		wxStaticText* m_drillLabel;
		wxTextCtrl* m_drillEntry;
		wxStaticText* m_drillUnit;
		wxStaticLine* m_staticline1;
		wxStdDialogButtonSizer* m_stdButtons;
		wxButton* m_stdButtonsOK;
		wxButton* m_stdButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTextFocusLost( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnCancelClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOkClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DIALOG_ZONE_VIA_STITCHING_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Zone Via Stitching"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 282,197 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~DIALOG_ZONE_VIA_STITCHING_BASE();
	
};

#endif //__DIALOG_ZONE_VIA_STITCHING_BASE_H__
