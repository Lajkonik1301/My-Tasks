#pragma once
#include <wx/wx.h>
#include "DatabaseManager.h"
#include "LoginWindow.h"
#include "MainAppWindow.h"
#include "App.h"
#include "User.h"

class LoginWindow;
class MainAppWindow;

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
	void ContinueAfterLogin(User* user);
	void ContinueAfterLogOut();
private:
	LoginWindow* loginWindowInstance;
	MainAppWindow* mainAppWindowInstance;
	User* user;

	DatabaseManager* databaseManager;

	int loggedInUserId;
	std::string loggedInUsername;

	void ClearMainFrame();

	void DrawLoginWindow();
	void DrawMainAppWindow();
};