#pragma once
#include <wx/wx.h>
#include "UserManager.h"
#include "User.h"
#include "LoginPage.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	void ClearPanel();
	void MainPage();

	LoginPage* loginPage;
	wxPanel* panel;
	UserManager* userManager;
};