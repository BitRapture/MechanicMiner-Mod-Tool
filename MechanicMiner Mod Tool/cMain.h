#pragma once
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/wfstream.h"

struct asset_obj
{
	std::string type = "other";
	bool changed = false;
	unsigned long data_size = 0;
	unsigned long link = 0;
	std::vector<UINT8> data;
};

class cMain : public wxFrame
{

private:
	bool asset_loaded, link_loaded, directory_saved;
	unsigned int asset_size, link_size;
	std::vector<unsigned long> sprite_locations;
	UINT8* asset_hold, *link_hold;
	std::vector<UINT8> temp_hold, temp2_hold;
	std::vector<asset_obj> all_assets;

	wxStaticText* txt_open, *txt_open2, *txt_open_status, *txt_open2_status, *txt_dir, *txt_dir_status, *txt_func, *txt_func_status;
	wxTextCtrl* ctrl_open, *ctrl_open2, *ctrl_dir;
	wxButton* btn_open, *btn_open2, *btn_dir, *btn_func;
	wxListBox* list_funcs;

	wxDir dir_path;

public:
	cMain();
	~cMain();

	// Global funcs
	unsigned long reverse_read(UINT8* input, int size, int offset = 0);
	unsigned long reverse_read(std::vector<UINT8> input, int size, int offset = 0);
	std::vector<UINT8> split_hex(unsigned long input);

	// Specific funcs
	void check_enable();
	void repack();
	void dump_all();

	// Event funcs
	void open_pressed(wxCommandEvent& evt);
	void open2_pressed(wxCommandEvent& evt);
	void dir_pressed(wxCommandEvent& evt);
	void func_pressed(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

