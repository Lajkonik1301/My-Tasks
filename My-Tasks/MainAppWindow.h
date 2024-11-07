#pragma once
#include <wx/wx.h>
#include "MainFrame.h"
#include "DatabaseManager.h"

class MainFrame;

class MainAppWindow{
public:
	MainAppWindow(MainFrame* mainFrame, DatabaseManager* databaseManager);
private:
	MainFrame* mainFrame;
	DatabaseManager* databaseManager;

	wxPanel* panel;

	wxButton* addNewTaskButton;
	wxButton* modifyTaskButton;
	wxButton* markAsDoneButton;
	wxButton* deleteTaskButton;

	wxStaticText* taskListsHeadline;
	wxListBox* taskListsContainer;

	wxStaticText* loggedInUserHeadline;
	wxStaticText* loggedInUsername;

	wxButton* manageUserButton;
	wxButton* logOutButton;

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

	void onAddNewTaskButtonClicked(wxCommandEvent& evt);
	void onModifyTaskButtonClicked(wxCommandEvent& evt);
	void onMarkAsDoneButtonClicked(wxCommandEvent& evt);
	void onDeleteTaskButtonClicked(wxCommandEvent& evt);

	void onManageUserButtonClicked(wxCommandEvent& evt);
	void onLogOutButtonClicked(wxCommandEvent& evt);

};

