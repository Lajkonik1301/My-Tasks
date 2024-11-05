#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	//DrawLoginWindow();

	//for test purposes, REMOVE LATER
	ClearMainFrame();
	DrawMainAppWindow();
	//!!
}

void MainFrame::ClearMainFrame(){
	//clearing all MainFrame children in order to place new items
	this->DestroyChildren();
}

void MainFrame::DrawLoginWindow(){
	loginWindowInstance = new LoginWindow(this);
}

void MainFrame::DrawMainAppWindow(){
	mainAppWindowInstance = new MainAppWindow(this);
}

void MainFrame::SetLoggedInUser(int userId, std::string username){
	loggedInUserId = userId;
	loggedInUsername = username;

	wxString loggedInUserMessage = wxString::Format("ID zalogowanego u¿ytkownika: %d", loggedInUserId);
	wxMessageBox(loggedInUserMessage);

	ClearMainFrame();
	DrawMainAppWindow();
}
