#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	databaseManager = new DatabaseManager();

	DrawLoginWindow();

	//for test purposes, REMOVE LATER
	//ClearMainFrame();
	//DrawMainAppWindow();
	//!!
}

void MainFrame::ClearMainFrame(){
	//clearing all MainFrame children in order to place new items
	this->DestroyChildren();
}

void MainFrame::DrawLoginWindow(){
	loginWindowInstance = new LoginWindow(this, databaseManager);
}

void MainFrame::DrawMainAppWindow(){
	mainAppWindowInstance = new MainAppWindow(this, databaseManager, user);
}

void MainFrame::ContinueAfterLogin(User* user){
	this->user = user;
	ClearMainFrame();
	DrawMainAppWindow();
}
