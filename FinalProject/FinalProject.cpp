// lab6.cpp : Defines the entry point for the application.
//

#include <iostream>

#include <wx/wx.h>
#include "Source.h"
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

