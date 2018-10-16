//
// Created by Michal Loska on 25/05/2018.
//test
// 

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Source.h"
///////////////////////////////////////////////////////////////////////////

/*
MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Demo 09") {
SetTitle(_("Demo 09 - Wykorzystanie schowka"));
SetIcon(wxNullIcon);
Center();

}*/


MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "PHOTO INDEXER MLOSKA", wxDefaultPosition, wxSize(400, 230), wxCAPTION | wxCLOSE_BOX)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_InputPicker1 = new wxDirPickerCtrl(this, wxID_ANY, wxT("Source"), wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE);
	bSizer1->Add(m_InputPicker1, 0, wxALIGN_CENTER | wxALL | wxEXPAND, 5);

	m_OutputPicker2 = new wxDirPickerCtrl(this, wxID_ANY, wxT("Output"), wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE);
	bSizer1->Add(m_OutputPicker2, 0, wxALIGN_CENTER | wxALL | wxEXPAND, 5);

	m_PathText1 = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_PathText1->Wrap(-1);
	bSizer1->Add(m_PathText1, 0, wxALIGN_LEFT | wxALL, 5);

	m_executebutton = new wxButton(this, wxID_ANY, wxT("EXECUTE"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_executebutton, 0, wxALIGN_CENTER | wxALL, 5);

	m_gauge1 = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gauge1->SetValue(0);
	bSizer1->Add(m_gauge1, 0, wxALL | wxEXPAND, 5);

	m_statusText2 = new wxStaticText(this, wxID_ANY, wxT("Micha³ Loska ©"), wxDefaultPosition, wxDefaultSize, 0);
	m_statusText2->Wrap(-1);
	bSizer1->Add(m_statusText2, 0, wxALIGN_CENTER | wxALL | wxBOTTOM, 5);

	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);
	m_InputPicker1->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(MyFrame::m_dirPicker1OnDirChanged), NULL, this);
	m_OutputPicker2->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(MyFrame::m_dirPicker2OnDirChanged), NULL, this);    m_executebutton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::m_button1OnButtonClick), NULL, this);
	m_loadedImg.AddHandler(new wxJPEGHandler);


	m_scaleWidth = 130.0;
	m_scaleHeight = 115.0;
	m_gauge1->SetRange(100);


}

MyFrame::~MyFrame() {
	m_InputPicker1->Disconnect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(MyFrame::m_dirPicker1OnDirChanged), NULL, this);
	m_OutputPicker2->Disconnect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(MyFrame::m_dirPicker2OnDirChanged), NULL, this);    m_executebutton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::m_button1OnButtonClick), NULL, this);


}
