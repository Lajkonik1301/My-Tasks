#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	DrawLoginPage();
}

void MainFrame::DrawLoginPage(){
	loginPageInstance = new LoginPage(this);
}
