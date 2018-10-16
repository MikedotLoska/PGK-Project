//
// Created by Michal Loska on 25/05/2018.
//

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#define SHOWENDL(x) std::cout << x << std::endl
#include <wx/artprov.h>
#include <wx/wxprec.h>
#include <wx/dcmemory.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/filepicker.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/filefn.h>
#include <wx/dir.h>
#include <iostream>
#include <fstream>  
//#include <tgmath.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame
{
private:

protected:

	///GUI VARIABLES

		///Input Directory Picker pointer
	wxDirPickerCtrl * m_InputPicker1;
		///Output Directory Picker pointer
	wxDirPickerCtrl * m_OutputPicker2;
		///Static text field showing the chosen Input Path
	wxStaticText* m_PathText1;
		///Static text field showing Copyright Mark and displaying currently made actions
	wxStaticText* m_statusText2;
		///Execute button- starts the whole application
	wxButton* m_executebutton;
		///Gauge shows the progress made by the app
	wxGauge* m_gauge1;
		
		///wxString variable holding the path to the input directory as a pure string
	wxString m_directoryPath;
		///wxString variable holding a temporary path- used for various operations
	wxString m_tempDirectoryPath;
		///wxString variable holding the path to the output directory as a pure string
	wxString m_outputDirectoryPath;
		///wxImage holding the Image in a given moment- it is used for loading each picture
	wxImage m_loadedImg;
		///wxImage which holds the covers - it is the index itself
	wxImage m_imgBitmap;
		
		/// wxArrayString used for storing file names in the main directory- implemented as as stack
	wxArrayString * m_fileArray;
		/// wxArrayString used for storing sub-directories- implemented as as stack
	wxArrayString * m_directoryArray;
		/// wxArrayString used for storing file names in a given directory- implemented as as stack
	wxArrayString * m_localFileArray;

		///variable specifying the max width of a picture after rescaling
	double m_scaleWidth;
		///variable specifying the max height of a picture after rescaling
	double m_scaleHeight;

		///Function checks for directories in the given path. Returns nothing. Saves all of the directories name to the m_directoryArray(in form of a stack)
	void CheckDirectories(wxString directoryPath) {
		m_directoryArray = new wxArrayString;
		//        wxDir::GetAllFiles(m_directoryPath, m_directoryArray, wxEmptyString, wxDIR_DIRS);
		wxString filename;
		wxDir dir(directoryPath);

		bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_DIRS);
		while (cont) {
			m_directoryArray->Add(filename);
			cont = dir.GetNext(&filename);
		}

	}
		///Function checks for files in the given path. Returns nothing. Saves all of the directories name to the m_directoryArray(in form of a stack)
	void CheckFiles(wxString directoryPath) {
		m_localFileArray = new wxArrayString;
		//        wxDir::GetAllFiles(m_directoryPath, m_directoryArray, wxEmptyString, wxDIR_DIRS);
		wxString filename;
		wxDir dir(directoryPath);

		bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
		while (cont) {
			m_localFileArray->Add(filename);
			cont = dir.GetNext(&filename);
		}
	}
		///Function counts files in the given directory
	int CheckFilesCount(wxString directoryPath) {
		m_fileArray = new wxArrayString;
		return wxDir::GetAllFiles(directoryPath, m_fileArray, wxEmptyString, wxDIR_FILES);
	}

	///This function is used for deleting directories recursively. It was taken from the internet - used purely for deleting directories recursively
	bool DeleteDirectory(wxString filename)
	{
		bool dir_empty = false;
		{
			wxDir dir(filename);
			if (!dir.IsOpened())
			{
				// deal with the error here - wxDir would already log an error message
				// explaining the exact reason of the failure
				return FALSE;
			}
			wxString file;

			bool cont = dir.GetFirst(&file);
			file = filename + wxFileName::GetPathSeparator() + file;
			while (cont)
			{
				if (wxFileName::FileExists(file)) wxRemoveFile(file);
				if (wxFileName::DirExists(file)) DeleteDirectory(file);
				cont = dir.GetNext(&file);
				file = filename + wxFileName::GetPathSeparator() + file;
			}
			if (!(dir.HasFiles() || dir.HasSubDirs()))dir_empty = true;
		}
		if (dir_empty) {
			bool error = wxRmdir(filename);
			return TRUE;
		}
		return FALSE;
	}

		///Function used for setting the position of the progress Gauge
	void SetGauge(int value) {
		m_gauge1->SetValue(value);
		wxYield();
		Update();
	}
		///Invoke funtion to invoke indexing in a given directory
	void Invoke(wxString directoryPath) {
		m_statusText2->SetLabel("Invoking");
		


		CheckFiles(directoryPath);
		int initial_size = m_localFileArray->GetCount();
		int number_of_iterations = initial_size / 20;

		m_imgBitmap.Create(800, 600);

		int indexer = 0;
		while (m_localFileArray->GetCount() > 0) {
			
			
			CreateBitmap(directoryPath, indexer++);
			SetGauge(indexer / initial_size * 100);
		}
		//log.close();
	}
	
		///Function scales every picture so it's size is lesser than the m_scaleWidth and m_scaleHeight
	int IMGRescale(wxImage & img) {
		m_statusText2->SetLabel("Scaling Images");

		int scaler = 0;
		if (img.GetSize().x > img.GetSize().y) {
			scaler = std::ceil( (static_cast<double>(m_loadedImg.GetSize().x)) / m_scaleWidth );
		}
		else {
			scaler = std::ceil((static_cast<double>(m_loadedImg.GetSize().y)) / m_scaleHeight);
		}
		
		img.Rescale((m_loadedImg.GetSize().x / scaler), (m_loadedImg.GetSize().y / scaler));
		return scaler;
	}

		///This function creates the actual index- pictures are being pasted into the main wxImage and text is being added by a AddText function
	void CreateBitmap(wxString directoryPath, int index) {
		m_imgBitmap.Clear();
		//std::ofstream log;
		//log.open("Resize_log" + std::to_string(index) + ".txt");
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (!m_localFileArray->IsEmpty()) {
					m_loadedImg.LoadFile(directoryPath + "\\" + m_localFileArray->Last());
					
					
				//	log << "PRZED: ROZMIAR X: " << m_loadedImg.GetSize().x << "ROZMIAR Y: " << m_loadedImg.GetSize().y << std::endl;
				//	log << IMGRescale(m_loadedImg) << std::endl;
					IMGRescale(m_loadedImg);
				//	log << "PO: ROZMIAR X: " << m_loadedImg.GetSize().x << "ROZMIAR Y: " << m_loadedImg.GetSize().y << std::endl;
					m_imgBitmap.Paste(m_loadedImg,
						20 + j * (m_scaleWidth + 20) + (m_scaleWidth - m_loadedImg.GetSize().x) / 2,
						i * (m_scaleHeight + 28) + 28);
					m_imgBitmap = AddText(m_imgBitmap, 20 + (j) * (m_scaleWidth + 20), (i + 1) * (m_scaleHeight + 24), m_localFileArray->Last());
					
					m_localFileArray->RemoveAt(m_localFileArray->GetCount() - 1);
					if (m_localFileArray->IsEmpty()) break;
									}
			}
					}
		m_statusText2->SetLabel("Exporting and Saving");

		if (!m_directoryArray->IsEmpty()) {
			wxMkdir(m_outputDirectoryPath + "\\" + "INDEXING_OUTPUT\\" + m_directoryArray->Last());
			m_imgBitmap.SaveFile(m_outputDirectoryPath + "\\" + "INDEXING_OUTPUT\\" + m_directoryArray->Last() + "\\" + "index" +
				(wxString::Format(wxT("%i"), index)) + ".jpg");
		}
		else {
			m_imgBitmap.SaveFile(m_outputDirectoryPath + "\\" + "INDEXING_OUTPUT\\index" +
				(wxString::Format(wxT("%i"), index)) + ".jpg");
		}
	//	log.close();
	}

		///Adds a text(in this case picture's name) in the given coordinates (in this case under each picture). Cuts the name after 12 characters and adds a ~ symbol
	wxImage AddText(wxImage & img, int coord_x, int coord_y, wxString textToEnter) {
		m_statusText2->SetLabel("Adding Captions");

		static int iterator = 0;
		wxBitmap output_bitmap(img);
		wxMemoryDC MemDC(output_bitmap);
		MemDC.SetPen(wxPen(*wxWHITE, 2));
		MemDC.SetBrush(wxBrush(*wxLIGHT_GREY, wxSOLID));
		MemDC.SelectObject(output_bitmap);
		MemDC.SetTextForeground(*wxWHITE);
		MemDC.SetFont(wxFont(12, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false ));
		if (textToEnter.Len() > 15) {
			textToEnter = textToEnter.SubString(0, 14);
			textToEnter += "~";
		}
		MemDC.DrawText(textToEnter, coord_x, coord_y);
		output_bitmap = MemDC.GetAsBitmap();
		wxImage temp_img = output_bitmap.ConvertToImage();
		return temp_img;
	}

		///Function invoked by the Input directory picker.
	virtual void m_dirPicker1OnDirChanged(wxFileDirPickerEvent& event) {
	
		m_directoryPath = m_InputPicker1->GetPath();

		m_PathText1->SetLabel(m_directoryPath);
	}
		///Function invoked by the Output directory picker.
		virtual void m_dirPicker2OnDirChanged(wxFileDirPickerEvent& event) {
		m_outputDirectoryPath = m_OutputPicker2->GetPath();
	}

		///Function invoked by the Execute button.
	virtual void m_button1OnButtonClick(wxCommandEvent& event) {
		m_gauge1->SetValue(0);
		
		if (m_directoryPath.IsEmpty()) m_PathText1->SetLabel("SPECIFY THE SOURCE FOLDER!");
		else if (m_outputDirectoryPath.IsEmpty()) m_PathText1->SetLabel("SPECIFY THE OUTPUT FOLDER!");
		if (!m_directoryPath.IsEmpty() && !m_outputDirectoryPath.IsEmpty()) {
			if (wxDirExists(m_outputDirectoryPath + "\\INDEXING_OUTPUT")) {
				if (wxMessageDialog(NULL, "Do you wish to override it? ", "Output folder already exist in the given directory", wxOK | wxCANCEL).ShowModal() == wxID_OK) {
					DeleteDirectory(m_outputDirectoryPath + "\\INDEXING_OUTPUT");
				}
				else return;
			}
			wxMkdir(m_outputDirectoryPath + "\\INDEXING_OUTPUT");

			CheckDirectories(m_directoryPath);
			m_statusText2->SetLabel("Creating Directories");
			while (!m_directoryArray->IsEmpty()) {
				Invoke(m_directoryPath + "/" + m_directoryArray->Last());
				m_directoryArray->RemoveAt(m_directoryArray->GetCount() - 1);
			}
			Invoke(m_directoryPath);
			m_gauge1->SetValue(100);
			m_statusText2->SetLabel("DONE!");
		}
	}

public:
		///Constructor
	MyFrame();
		///Deconstructor
	~MyFrame();

};

#endif //__NONAME_H__



