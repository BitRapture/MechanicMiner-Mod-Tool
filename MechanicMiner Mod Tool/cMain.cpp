#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)

EVT_BUTTON(10002, cMain::open_pressed)
EVT_BUTTON(10004, cMain::dir_pressed)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MM Mod Tool", wxPoint(200, 200), wxSize(450, 300), wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{
	asset_loaded = false;
	directory_saved = false;
	
	SetBackgroundColour(wxColour(23, 26, 28));

	txt_open = new wxStaticText(this, wxID_ANY, "OPEN ASSET FILE (MECHANICMINER_ASSET_64)", wxPoint(4, 4));
	txt_open->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open->SetForegroundColour(wxColour(173, 190, 201));
	txt_open_status = new wxStaticText(this, wxID_ANY, "UNLOADED", wxPoint(260, 4));
	txt_open_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open_status->SetForegroundColour(wxColour(209, 10, 10));

	txt_dir = new wxStaticText(this, wxID_ANY, "SELECT WORKSPACE FOLDER", wxPoint(4, 51));
	txt_dir->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_dir->SetForegroundColour(wxColour(173, 190, 201));
	txt_dir_status = new wxStaticText(this, wxID_ANY, "DISCONNECTED", wxPoint(164, 51));
	txt_dir_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_dir_status->SetForegroundColour(wxColour(209, 10, 10));

	ctrl_open = new wxTextCtrl(this, 10001, wxEmptyString, wxPoint(4, 20), wxSize(366, 20));
	ctrl_open->SetBackgroundColour(wxColour(23, 26, 28));
	ctrl_open->SetForegroundColour(wxColour(173, 190, 201));

	ctrl_dir = new wxTextCtrl(this, 10003, wxEmptyString, wxPoint(4, 66), wxSize(366, 20));
	ctrl_dir->SetBackgroundColour(wxColour(23, 26, 28));
	ctrl_dir->SetForegroundColour(wxColour(173, 190, 201));

	btn_open = new wxButton(this, 10002, "OPEN", wxPoint(370, 19), wxSize(60, 22));
	btn_open->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_open->SetBackgroundColour(wxColour(173, 190, 201));
	btn_open->SetForegroundColour(wxColour(23, 26, 28));

	btn_dir = new wxButton(this, 10004, "SELECT", wxPoint(370, 65), wxSize(60, 22));
	btn_dir->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_dir->SetBackgroundColour(wxColour(173, 190, 201));
	btn_dir->SetForegroundColour(wxColour(23, 26, 28));

	list_funcs = new wxListBox(this, 10005, wxPoint(4, 112), wxSize(426, 120));
	list_funcs->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	list_funcs->SetBackgroundColour(wxColour(23, 26, 28));
	list_funcs->SetForegroundColour(wxColour(173, 190, 201));
	wxArrayString functions;
	functions.Add("DUMP ALL ASSETS");
	functions.Add("DUMP JOHN SPRITES");
	functions.Add("DUMP HOLOJOHN SPRITES");
	list_funcs->Append(functions);
	list_funcs->Disable();
}

cMain::~cMain()
{
	asset_loc.clear();
}

void cMain::check_enable()
{
	if (asset_loaded && directory_saved)
	{
		list_funcs->Enable();
	}
}

void cMain::open_pressed(wxCommandEvent& evt)
{
	if (!asset_loaded)
	{
		wxFFileInputStream asset(ctrl_open->GetValue());

		if (!asset.IsOk() || !asset.CanRead()) { evt.Skip(); return; }
		txt_open_status->SetForegroundColour(wxColour(247, 203, 27));
		txt_open_status->SetLabelText("LOADING FILE");

		if (asset.GetLength() < 337895356)
		{

			txt_open_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open_status->SetLabelText("INCORRECT FILE");
			evt.Skip();
			return;
		}

		asset_hold = (UINT8*)malloc(asset.GetLength());
		if (asset_hold == nullptr)
		{

			txt_open_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open_status->SetLabelText("FILE TOO BIG");
			evt.Skip();
			return;
		}
		asset_size = asset.GetLength();
		asset.ReadAll(asset_hold, asset.GetLength());

		if (asset_hold[1688] != 0xF0 || asset_hold[4352] != 0xC0 || asset_hold[7194] != 0x5D)
		{

			txt_open_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open_status->SetLabelText("INCORRECT FILE");
			evt.Skip();
			return;
		}

		for (unsigned int i = 0; i < asset_size; i++)
		{
			if (i + (unsigned)4 < asset_size)
			{
				if (asset_hold[i] == 0x89 && asset_hold[i + 1] == 0x50 && asset_hold[i + 2] == 0x4E && asset_hold[i + 3] == 0x47)
				{
					asset_loc.push_back(i);
				}
			}
		}

		asset_loaded = true;

		txt_open_status->SetForegroundColour(wxColour(30, 189, 33));
		txt_open_status->SetLabelText("LOADED");
		btn_open->Disable();
		ctrl_open->Disable();

		check_enable();

		evt.Skip();
	}
}

void cMain::dir_pressed(wxCommandEvent& evt)
{
	if (!directory_saved)
	{
		dir_path.Open(ctrl_dir->GetValue());

		txt_dir_status->SetForegroundColour(wxColour(247, 203, 27));
		txt_dir_status->SetLabelText("CONNECTING");

		if (!dir_path.IsOpened())
		{
			txt_dir_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_dir_status->SetLabelText("DIRECTORY DOESN'T EXIST");
			evt.Skip();
			return;
		}

		directory_saved = true;

		txt_dir_status->SetForegroundColour(wxColour(30, 189, 33));
		txt_dir_status->SetLabelText("CONNECTED");
		btn_dir->Disable();
		ctrl_dir->Disable();


		check_enable();

		evt.Skip();
	}
}