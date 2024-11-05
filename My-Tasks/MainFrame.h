#pragma once
#include <wx/wx.h>
#include "UserManager.h"
#include "User.h"
#include "LoginPage.h"

class LoginPage;

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	LoginPage* loginPageInstance;

	void DrawLoginPage();
};