#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
	m_frame = new cMain();
	m_frame->Show();
	m_frame->SetIcon(wxICON(appicon));

	return true;
}
