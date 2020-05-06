#pragma once
#include "cMain.h"


class cApp : public wxApp
{

private:
	cMain* m_frame = nullptr;

public:
	cApp();
	~cApp();
	virtual bool OnInit();

};

