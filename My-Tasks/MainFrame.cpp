#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	DrawLoginWindow();

	
	
}

void MainFrame::DrawLoginWindow(){
	loginWindowInstance = new LoginWindow(this);
}

void MainFrame::SetLoggedInUser(int userId, std::string username){
	loggedInUserId = userId;
	loggedInUsername = username;
}
