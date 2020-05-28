#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)

EVT_BUTTON(10002, cMain::open_pressed)
EVT_BUTTON(10004, cMain::dir_pressed)
EVT_BUTTON(10006, cMain::func_pressed)
EVT_BUTTON(10008, cMain::open2_pressed)

wxEND_EVENT_TABLE()

/*
	ID LIST
	-----------------------------------
	Asset Txtbox =				10001,
	Asset Open Btn =			10002,
	Directory Txtbox =			10003,
	Directory Select Btn =		10004,
	Function box =				10005,
	Function Select Btn =		10006,
	Asset links Txtbox =		10007,
	Asset links Btn =			10008,
*/

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MM Mod Tool (v1.1)", wxPoint(200, 200), wxSize(450, 340), wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{
	asset_loaded = false;
	directory_saved = false;
	link_loaded = false;
	
	SetBackgroundColour(wxColour(23, 26, 28));

	txt_open = new wxStaticText(this, wxID_ANY, "OPEN ASSET FILE (MECHANICMINER_ASSET_64)", wxPoint(4, 4));
	txt_open->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open->SetForegroundColour(wxColour(173, 190, 201));
	txt_open_status = new wxStaticText(this, wxID_ANY, "UNLOADED", wxPoint(260, 4));
	txt_open_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open_status->SetForegroundColour(wxColour(209, 10, 10));

	txt_open2 = new wxStaticText(this, wxID_ANY, "OPEN LINKS FILE (MECHANICMINER_ASSET_64_LINKS)", wxPoint(4, 50));
	txt_open2->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open2->SetForegroundColour(wxColour(173, 190, 201));
	txt_open2_status = new wxStaticText(this, wxID_ANY, "UNLOADED", wxPoint(292, 50));
	txt_open2_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_open2_status->SetForegroundColour(wxColour(209, 10, 10));

	txt_dir = new wxStaticText(this, wxID_ANY, "SELECT WORKSPACE FOLDER", wxPoint(4, 96)); 
	txt_dir->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_dir->SetForegroundColour(wxColour(173, 190, 201));
	txt_dir_status = new wxStaticText(this, wxID_ANY, "DISCONNECTED", wxPoint(164, 96));
	txt_dir_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_dir_status->SetForegroundColour(wxColour(209, 10, 10));

	txt_func = new wxStaticText(this, wxID_ANY, "ASSET OPTIONS", wxPoint(4, 142));
	txt_func->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_func->SetForegroundColour(wxColour(173, 190, 201));
	txt_func_status = new wxStaticText(this, wxID_ANY, "DISABLED", wxPoint(94, 142));
	txt_func_status->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	txt_func_status->SetForegroundColour(wxColour(209, 10, 10));

	ctrl_open = new wxTextCtrl(this, 10001, wxEmptyString, wxPoint(4, 20), wxSize(366, 20));
	ctrl_open->SetBackgroundColour(wxColour(23, 26, 28));
	ctrl_open->SetForegroundColour(wxColour(173, 190, 201));

	ctrl_open2 = new wxTextCtrl(this, 10007, wxEmptyString, wxPoint(4, 66), wxSize(366, 20));
	ctrl_open2->SetBackgroundColour(wxColour(23, 26, 28));
	ctrl_open2->SetForegroundColour(wxColour(173, 190, 201));

	ctrl_dir = new wxTextCtrl(this, 10003, wxEmptyString, wxPoint(4, 112), wxSize(366, 20));
	ctrl_dir->SetBackgroundColour(wxColour(23, 26, 28));
	ctrl_dir->SetForegroundColour(wxColour(173, 190, 201));

	btn_open = new wxButton(this, 10002, "OPEN", wxPoint(370, 19), wxSize(60, 22));
	btn_open->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_open->SetBackgroundColour(wxColour(173, 190, 201));
	btn_open->SetForegroundColour(wxColour(23, 26, 28));

	btn_open2 = new wxButton(this, 10008, "OPEN", wxPoint(370, 65), wxSize(60, 22));
	btn_open2->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_open2->SetBackgroundColour(wxColour(173, 190, 201));
	btn_open2->SetForegroundColour(wxColour(23, 26, 28));

	btn_dir = new wxButton(this, 10004, "SELECT", wxPoint(370, 111), wxSize(60, 22));
	btn_dir->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_dir->SetBackgroundColour(wxColour(173, 190, 201));
	btn_dir->SetForegroundColour(wxColour(23, 26, 28));

	btn_func = new wxButton(this, 10006, "SELECT", wxPoint(4, 278), wxSize(426, 22));
	btn_func->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	btn_func->SetBackgroundColour(wxColour(173, 190, 201));
	btn_func->SetForegroundColour(wxColour(23, 26, 28));
	btn_func->Disable();

	list_funcs = new wxListBox(this, 10005, wxPoint(4, 158), wxSize(426, 120));
	list_funcs->SetFont(wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	list_funcs->SetBackgroundColour(wxColour(23, 26, 28));
	list_funcs->SetForegroundColour(wxColour(173, 190, 201));
	wxArrayString functions;
	functions.Add("REPACK ASSET FILE (.MMTP)");
	functions.Add("REPACK ASSET FILE (RAW)");
	functions.Add("DUMP ALL SPRITE ASSETS");
	list_funcs->Append(functions);
	list_funcs->Disable();
}

cMain::~cMain()
{
	temp_hold.clear();
	temp2_hold.clear();
	all_assets.clear();
	free(asset_hold);
	free(link_hold);
}

unsigned long cMain::reverse_read(UINT8* input, int size, int offset)
{
	std::stringstream hexstream;
	char hold[2];
	for (int i = size; i > -1; i--)
	{
		itoa(input[i + offset], hold, 16);
		hexstream << std::setfill('0') << std::setw(2) << hold;
	} 
	return static_cast<unsigned>(strtoul(hexstream.str().c_str(), NULL, 16));
}

std::vector<UINT8> cMain::split_hex(unsigned long input)
{
	std::vector<UINT8> output, hold_hex;
	bool first_charmet = false;
	char hold[16], hex[3];
	itoa(input, hold, 16);
	int i = 1;
	hex[2] = '\0';
	while (i < 16)
	{
		hex[0] = '0';
		if (i - 1 < strnlen_s(hold, sizeof hold)) hex[0] = hold[i - 1];
		hex[1] = '0';
		if (i < strnlen_s(hold, sizeof hold))
		{
			hex[1] = hold[i];
		}
		else if (hex[0] != '0') {
			hex[1] = hex[0];
			hex[0] = '0';
		}

		hold_hex.push_back(static_cast<UINT8>(strtoul(hex, NULL, 16)));
		i += 2;
	}
	std::reverse(hold_hex.begin(), hold_hex.end());
	for (int i = 0; i < hold_hex.size(); i++)
	{
		if (!first_charmet)
		{
			if (hold_hex[i] != 0) first_charmet = true;
		}

		if (first_charmet)
		{
			output.push_back(hold_hex[i]);
		}
	}
	if (output.size() != 16)
	{
		while (output.size() != 16)
		{
			output.push_back(0);
		}
	}

	return output;
}

void cMain::check_enable()
{
	if (asset_loaded && link_loaded && directory_saved)
	{
		txt_func_status->SetForegroundColour(wxColour(247, 203, 27));
		txt_func_status->SetLabelText(wxString("LINKING ASSETS"));

		unsigned long i = 0, get_link, get_asset;
		while (i < link_size)
		{
			get_link = reverse_read(link_hold, 7, i);
			get_asset = reverse_read(asset_hold, 7, get_link);
			
			all_assets.push_back(asset_obj());
			all_assets[all_assets.size() - 1].link = get_link;

			// Link to PNGs
			if (asset_hold[get_asset + 4] == 0x89 && asset_hold[get_asset + 5] == 0x50 && asset_hold[get_asset + 6] == 0x4E && asset_hold[get_asset + 7] == 0x47)
			{
				all_assets[all_assets.size() - 1].data_size = reverse_read(asset_hold, 3, get_asset);
				all_assets[all_assets.size() - 1].type = "sprite";
				sprite_locations.push_back(all_assets.size() - 1);
			}

			i += 8;
		}

		list_funcs->Enable();
		btn_func->Enable();
		txt_func_status->SetForegroundColour(wxColour(30, 189, 33));
		txt_func_status->SetLabelText("LINKED " + std::to_string(sprite_locations.size()) + " ASSETS");
	}
}

void cMain::repack()
{
	temp_hold.clear();
	std::vector<UINT8>().swap(temp_hold);

	txt_func_status->SetForegroundColour(wxColour(247, 203, 27));
	txt_func_status->SetLabelText(wxString("REPACKING ASSETS"));

	for (unsigned long i = 0; i < asset_size; i++)
	{
		temp_hold.push_back(asset_hold[i]);
	}

	unsigned long pack_size, sprite_loc, get_asset_link;
	std::vector<UINT8> pack_hex, new_asset_link;
	for (unsigned long i = 0; i < sprite_locations.size(); i++)
	{
		if (!dir_path.HasFiles("asset_" + std::to_string(i) + ".png")) continue;

		wxFFileInputStream pack(dir_path.GetName() + "\\asset_" + std::to_string(i) + ".png");
		UINT8* pack_hold = (UINT8*)malloc(pack.GetSize());
		if (pack_hold == nullptr) return;
		pack_size = pack.GetSize();
		pack_hex = split_hex(pack_size);
		pack.ReadAll(pack_hold, pack.GetSize());
		sprite_loc = temp_hold.size();
		for (int ph = 0; ph < 4; ph++)
		{
			temp_hold.push_back(pack_hex[ph]);
		}
		pack_hex.clear();
		std::vector<UINT8>().swap(pack_hex);
		for (unsigned long ph = 0; ph < pack_size; ph++)
		{
			temp_hold.push_back(pack_hold[ph]);
		}
		free(pack_hold);

		get_asset_link = all_assets[sprite_locations[i]].link;
		new_asset_link = split_hex(sprite_loc);
		for (int na = 0; na < 8; na++)
		{
			temp_hold[get_asset_link + na] = new_asset_link[na];
		}
		
		new_asset_link.clear();
		std::vector<UINT8>().swap(new_asset_link);
	}


	wxFFileOutputStream packed_file(dir_path.GetName() + "\\main.mechanicminer_asset_64");
	UINT8* buffer = (UINT8*)malloc(temp_hold.size());
	if (buffer == nullptr) return;
	for (unsigned int ii = 0; ii < temp_hold.size(); ii++) { buffer[ii] = temp_hold[ii]; }

	packed_file.WriteAll(buffer, temp_hold.size());
	free(buffer);
	temp_hold.clear();
	std::vector<UINT8>().swap(temp_hold);

	txt_func_status->SetForegroundColour(wxColour(30, 189, 33));
	txt_func_status->SetLabelText("ASSET FILE REPACKED");
}

void cMain::dump_all()
{
	txt_func_status->SetForegroundColour(wxColour(247, 203, 27));
	txt_func_status->SetLabelText("DUMPING 0/" + std::to_string(sprite_locations.size()) + " ASSETS");
	
	temp_hold.clear();
	std::vector<UINT8>().swap(temp_hold);

	unsigned long dumped_total = 0;
	for (unsigned long i = 0; i < sprite_locations.size(); i++)
	{
		wxFFileOutputStream asset(dir_path.GetName() + "\\asset_" + std::to_string(dumped_total) + ".png");
		txt_func_status->SetLabelText("DUMPING " + std::to_string(dumped_total + 1) + "/" + std::to_string(sprite_locations.size()) + " ASSETS");
		
		temp_hold.clear();
		std::vector<UINT8>().swap(temp_hold);

		for (unsigned long ii = 0; ii < all_assets[sprite_locations[i]].data_size; ii++)
		{
			temp_hold.push_back(asset_hold[reverse_read(asset_hold, 7, all_assets[sprite_locations[i]].link) + 4 + ii]);
		}

		UINT8* buffer = (UINT8*)malloc(temp_hold.size());
		if (buffer == nullptr) return;
		for (unsigned long ii = 0; ii < temp_hold.size(); ii++) { buffer[ii] = temp_hold[ii]; }
		asset.WriteAll(buffer, temp_hold.size());
		free(buffer);

		dumped_total++;
	}

	temp_hold.clear();
	std::vector<UINT8>().swap(temp_hold);

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
			txt_open_status->SetLabelText("OUT OF MEM");
			evt.Skip();
			return;
		}
		asset_size = asset.GetLength();
		asset.ReadAll(asset_hold, asset.GetLength());

		// Check Asset File is the original
		if (asset_hold[1688] != 0xF0 || asset_hold[4352] != 0xC0 || asset_hold[7194] != 0x5D)
		{
			txt_open_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open_status->SetLabelText("INCORRECT FILE");
			evt.Skip();
			return;
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

void cMain::open2_pressed(wxCommandEvent& evt) 
{
	if (!link_loaded)
	{
		wxFFileInputStream link(ctrl_open2->GetValue());

		if (!link.IsOk() || !link.CanRead()) { evt.Skip(); return; }
		txt_open2_status->SetForegroundColour(wxColour(247, 203, 27));
		txt_open2_status->SetLabelText("LOADING FILE");

		if (link.GetLength() < 88544)
		{
			txt_open2_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open2_status->SetLabelText("INCORRECT FILE");
			evt.Skip();
			return;
		}

		link_hold = (UINT8*)malloc(link.GetLength());
		if (link_hold == nullptr)
		{
			txt_open2_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open2_status->SetLabelText("OUT OF MEM");
			evt.Skip();
			return;
		}
		link_size = link.GetLength();
		link.ReadAll(link_hold, link.GetLength());

		// Check Links File is the original
		if (link_hold[65050] != 0x9E || link_hold[66384] != 0x48 || link_hold[23417] != 0x5B)
		{
			txt_open2_status->SetForegroundColour(wxColour(209, 10, 10));
			txt_open2_status->SetLabelText("INCORRECT FILE");
			evt.Skip();
			return;
		}

		link_loaded = true;

		txt_open2_status->SetForegroundColour(wxColour(30, 189, 33));
		txt_open2_status->SetLabelText("LOADED");
		btn_open2->Disable();
		ctrl_open2->Disable();

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

	if (selected == "REPACK ASSET FILE (RAW)")
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