#pragma once
#include <vector>
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/wfstream.h"

class cMain : public wxFrame
{

private:
	bool asset_loaded, directory_saved;
	unsigned int asset_size;
	std::vector<unsigned int> asset_loc;
	UINT8* asset_hold;

	wxStaticText* txt_open, *txt_open_status, *txt_dir, *txt_dir_status;
	wxTextCtrl* ctrl_open, *ctrl_dir;
	wxButton* btn_open, *btn_dir;
	wxListBox* list_funcs;

	wxDir dir_path;

public:
	cMain();
	~cMain();

	void check_enable();

	void open_pressed(wxCommandEvent& evt);
	void dir_pressed(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

