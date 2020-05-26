#pragma once
#include <vector>
#include <sstream>
#include <iomanip>
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/wfstream.h"

class cMain : public wxFrame
{

private:
	bool asset_loaded, link_loaded, directory_saved;
	unsigned int asset_size, link_size;
	std::vector<unsigned long int> sprite_loc, sprite_link, sprite_temp_size, sprite_temp2_size, asset_links;
	UINT8* asset_hold, *link_hold;
	std::vector<UINT8> temp_hold, temp2_hold;

	wxStaticText* txt_open, *txt_open2, *txt_open_status, *txt_open2_status, *txt_dir, *txt_dir_status, *txt_func, *txt_func_status;
	wxTextCtrl* ctrl_open, *ctrl_open2, *ctrl_dir;
	wxButton* btn_open, *btn_open2, *btn_dir, *btn_func;
	wxListBox* list_funcs;

	wxDir dir_path;

public:
	cMain();
	~cMain();

	// Global funcs
	unsigned long int reverse_read(UINT8* input, int size, int offset = 0);
	unsigned long int reverse_read(std::vector<UINT8> input, int size, int offset = 0);
	std::vector<UINT8> split_hex(unsigned long int input);

	// Specific funcs
	void check_enable();
	void relink_offsets();
	void repack();
	void dump_all();

	// Event funcs
	void open_pressed(wxCommandEvent& evt);
	void open2_pressed(wxCommandEvent& evt);
	void dir_pressed(wxCommandEvent& evt);
	void func_pressed(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

