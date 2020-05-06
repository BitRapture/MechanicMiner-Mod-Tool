#include "cMain.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MM Mod Tool", wxPoint(200, 200), wxSize(450, 300), wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{
	SetBackgroundColour(wxColour(23, 26, 28));

	txt_open = new wxStaticText(this, wxID_ANY, "OPEN ASSET FILE");
	txt_open->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open->SetForegroundColour(wxColour(173, 190, 201));
}

cMain::~cMain()
{

}
