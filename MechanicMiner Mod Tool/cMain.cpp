#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)

EVT_BUTTON(10002, cMain::open_pressed)
EVT_BUTTON(10004, cMain::dir_pressed)
EVT_BUTTON(10006, cMain::func_pressed)

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

	txt_dir = new wxStaticText(this, wxID_ANY, "SELECT WORKSPACE FOLDER", wxPoint(4, 50));
	txt_dir->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_dir->SetForegroundColour(wxColour(173, 190, 201));
	txt_dir_status = new wxStaticText(this, wxID_ANY, "DISCONNECTED", wxPoint(164, 50));
	txt_dir_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_dir_status->SetForegroundColour(wxColour(209, 10, 10));

	txt_func = new wxStaticText(this, wxID_ANY, "ASSET OPTIONS", wxPoint(4, 96));
	txt_func->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_func->SetForegroundColour(wxColour(173, 190, 201));
	txt_func_status = new wxStaticText(this, wxID_ANY, "DISABLED", wxPoint(94, 96));
	txt_func_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_func_status->SetForegroundColour(wxColour(209, 10, 10));

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

	btn_func = new wxButton(this, 10006, "SELECT", wxPoint(4, 232), wxSize(426, 22));
	btn_func->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_func->SetBackgroundColour(wxColour(173, 190, 201));
	btn_func->SetForegroundColour(wxColour(23, 26, 28));
	btn_func->Disable();

	list_funcs = new wxListBox(this, 10005, wxPoint(4, 112), wxSize(426, 120));
	list_funcs->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	list_funcs->SetBackgroundColour(wxColour(23, 26, 28));
	list_funcs->SetForegroundColour(wxColour(173, 190, 201));
	wxArrayString functions;
	functions.Add("REPACK ASSET FILE");
	functions.Add("DUMP ALL SPRITE ASSETS");
	list_funcs->Append(functions);
	list_funcs->Disable();
}

cMain::~cMain()
{
	asset_loc.clear();
	temp_hold.clear();
	free(asset_hold);
}

void cMain::check_enable()
{
	if (asset_loaded && directory_saved)
	{
		list_funcs->Enable();
		btn_func->Enable();
		txt_func_status->SetForegroundColour(wxColour(30, 189, 33));
		txt_func_status->SetLabelText(std::to_string(asset_loc.size()) + " ASSETS FOUND");
	}
}

void cMain::repack()
{
	temp_hold.clear();
	unsigned int i = 0, p = 0, endp = 0;
	txt_func_status->SetForegroundColour(wxColour(247, 203, 27));
	txt_func_status->SetLabelText("REPACKING ASSETS");
	while (i < asset_size)
	{
		if (i + 4 < asset_size)
		{
			if (asset_hold[i] == 0x89 && asset_hold[i + 1] == 0x50 && asset_hold[i + 2] == 0x4E && asset_hold[i + 3] == 0x47)
			{
				if (dir_path.HasFiles("asset_" + std::to_string(p) + ".png"))
				{
					endp = 0;
					while (1)
					{
						if (asset_hold[i + endp] == 0x49 && asset_hold[i + endp + 1] == 0x45 && asset_hold[i + endp + 2] == 0x4E && asset_hold[i + endp + 3] == 0x44 && asset_hold[i + endp + 4] == 0xAE && asset_hold[i + endp + 5] == 0x42 && asset_hold[i + endp + 6] == 0x60 && asset_hold[i + endp + 7] == 0x82)
						{
							endp += 8;
							break;
						}
						endp++;
					}

					wxFFileInputStream pack(dir_path.GetName() + "\\asset_" + std::to_string(p) + ".png");
					UINT8* pack_hold = (UINT8*)malloc(pack.GetSize());
					if (pack_hold == nullptr) return;
					unsigned int pack_size = pack.GetSize();
					pack.ReadAll(pack_hold, pack.GetSize());

					for (unsigned int ph = 0; ph < pack_size; ph++)
					{
						temp_hold.push_back(pack_hold[ph]);
					}
					free(pack_hold);
					i += endp;
				}
				p++;
			}
		}
		temp_hold.push_back(asset_hold[i]);
		i++;
	}

	wxFFileOutputStream packed_file(dir_path.GetName() + "\\main.mechanicminer_asset_64");
	UINT8* buffer = (UINT8*)malloc(temp_hold.size());
	if (buffer == nullptr) return;
	for (unsigned int ii = 0; ii < temp_hold.size(); ii++) { buffer[ii] = temp_hold[ii]; }

	packed_file.WriteAll(buffer, temp_hold.size());
	free(buffer);
	temp_hold.clear();
	txt_func_status->SetForegroundColour(wxColour(30, 189, 33));
	txt_func_status->SetLabelText("ASSET FILE REPACKED");
}

void cMain::dump_all()
{
	unsigned int p = 0;
	txt_func_status->SetForegroundColour(wxColour(247, 203, 27));
	txt_func_status->SetLabelText("DUMPING 0/" + std::to_string(asset_loc.size()) + "ASSETS");
	for (unsigned int i = 0; i < asset_loc.size(); i++)
	{
		wxFFileOutputStream asset(dir_path.GetName() + "\\asset_" + std::to_string(i) + ".png");
		txt_func_status->SetLabelText("DUMPING " + std::to_string(i + 1) + "/" + std::to_string(asset_loc.size()) + " ASSETS");
		temp_hold.clear();
		p = 0;
		while (1)
		{
			temp_hold.push_back(asset_hold[asset_loc[i] + p]);
			if (asset_hold[asset_loc[i] + p] == 0x49 && asset_hold[asset_loc[i] + p + 1] == 0x45 && asset_hold[asset_loc[i] + p + 2] == 0x4E && asset_hold[asset_loc[i] + p + 3] == 0x44 && asset_hold[asset_loc[i] + p + 4] == 0xAE && asset_hold[asset_loc[i] + p + 5] == 0x42 && asset_hold[asset_loc[i] + p + 6] == 0x60 && asset_hold[asset_loc[i] + p + 7] == 0x82)
			{
				temp_hold.push_back(0x45);
				temp_hold.push_back(0x4E);
				temp_hold.push_back(0x44);
				temp_hold.push_back(0xAE);
				temp_hold.push_back(0x42);
				temp_hold.push_back(0x60);
				temp_hold.push_back(0x82);
				break;
			}
			p++;
		}
		UINT8* buffer = (UINT8*)malloc(temp_hold.size());
		if (buffer == nullptr) return;
		for (unsigned int ii = 0; ii < temp_hold.size(); ii++) { buffer[ii] = temp_hold[ii]; }
		asset.WriteAll(buffer, temp_hold.size());
		free(buffer);
	}
	temp_hold.clear();

	txt_func_status->SetForegroundColour(wxColour(30, 189, 33));
	txt_func_status->SetLabelText("ALL ASSETS DUMPED");
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

void cMain::func_pressed(wxCommandEvent& evt)
{
	if (list_funcs->GetSelection() == wxNOT_FOUND) { evt.Skip(); return; }

	wxString selected = list_funcs->GetString(list_funcs->GetSelection());

	if (selected == "REPACK ASSET FILE")
	{
		btn_func->Disable();
		repack();
		btn_func->Enable();
	}

	if (selected == "DUMP ALL SPRITE ASSETS")
	{
		btn_func->Disable();
		dump_all();
		btn_func->Enable();
	}

	evt.Skip();
}