#pragma once
#include <wx/wx.h>
#include "UserManager.h"
#include "User.h"
#include "LoginWindow.h"
#include "MainAppWindow.h"
#include "App.h"

class LoginWindow;
class MainAppWindow;

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
	void SetLoggedInUser(int userId, std::string username);
private:
	LoginWindow* loginWindowInstance;
	MainAppWindow* mainAppWindowInstance;

	int loggedInUserId;
	std::string loggedInUsername;

	void ClearMainFrame();

	void DrawLoginWindow();
	void DrawMainAppWindow();
};