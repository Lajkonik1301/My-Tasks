#pragma once
#include <wx/wx.h>
#include <vector>
#include <string>
#include "MainFrame.h"
#include "DatabaseManager.h"
#include "User.h"

class MainFrame;

class MainAppWindow{
public:
	MainAppWindow(MainFrame* mainFrame, DatabaseManager* databaseManager, User* user);
private:
	MainFrame* mainFrame;
	User* user;
	DatabaseManager* databaseManager;

	wxPanel* panel;

	wxButton* addNewTaskButton;
	wxButton* modifyTaskButton;
	wxButton* markAsDoneButton;
	wxButton* deleteTaskButton;

	wxArrayString categoriesChoices;
	wxStaticText* taskListsHeadline;
	wxListBox* taskListsContainer;

	wxStaticText* loggedInUserHeadline;
	wxStaticText* loggedInUsername;

	wxButton* manageUserButton;
	wxButton* logOutButton;

	wxArrayString tasksChoices;
	wxStaticText* tasksHeadline;
	wxListBox* tasksContainer;

	wxBoxSizer* mainSizer;
	wxBoxSizer* leftSizer;
	wxBoxSizer* rightSizer;
	wxBoxSizer* leftTopSizer;
	wxBoxSizer* leftBottomSizer;
	wxBoxSizer* rightTopSizer;
	wxBoxSizer* rightBottomSizer;
	wxBoxSizer* userInfoSizer;
	wxBoxSizer* userManageSizer;
	wxGridSizer* outerSizer;

	void BindButtons();
	void populateCategoriesContainer();
	void populateTasksContainer();

	void onAddNewTaskButtonClicked(wxCommandEvent& evt);
	void onModifyTaskButtonClicked(wxCommandEvent& evt);
	void onMarkAsDoneButtonClicked(wxCommandEvent& evt);
	void onDeleteTaskButtonClicked(wxCommandEvent& evt);

	void onManageUserButtonClicked(wxCommandEvent& evt);
	void onLogOutButtonClicked(wxCommandEvent& evt);

};