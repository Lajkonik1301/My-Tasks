#include "MainAppWindow.h"

MainAppWindow::MainAppWindow(MainFrame* mainFrame, DatabaseManager* databaseManager) {
	this->mainFrame = mainFrame;
	this->databaseManager = new DatabaseManager();
	
	panel = new wxPanel(mainFrame);

	//place items
	addNewTaskButton = new wxButton(panel, wxID_ANY, "Dodaj", wxDefaultPosition, wxSize(150, -1));
	modifyTaskButton = new wxButton(panel, wxID_ANY, "Zmieñ", wxDefaultPosition, wxSize(150, -1));
	markAsDoneButton = new wxButton(panel, wxID_ANY, "Oznacz jako wykonane", wxDefaultPosition, wxSize(150, -1));
	deleteTaskButton = new wxButton(panel, wxID_ANY, "Usuñ", wxDefaultPosition, wxSize(150, -1));;

	taskListsHeadline = new wxStaticText(panel, wxID_ANY, "Listy zadañ");
	taskListsContainer = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(150, -1));

	loggedInUserHeadline = new wxStaticText(panel, wxID_ANY, "Zalogowany u¿ytkownik:");
	loggedInUsername = new wxStaticText(panel, wxID_ANY, "test-username");

	manageUserButton = new wxButton(panel, wxID_ANY, "Zarz¹dzaj", wxDefaultPosition, wxSize(100, -1));
	logOutButton = new wxButton(panel, wxID_ANY, "Wyloguj siê", wxDefaultPosition, wxSize(100, -1));

	tasksHeadline = new wxStaticText(panel, wxID_ANY, "Zadania:");
	tasksContainer = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 200));
	//place items

	//setup sizers
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	leftSizer = new wxBoxSizer(wxVERTICAL);
	rightSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(leftSizer);
	mainSizer->AddSpacer(20);
	mainSizer->Add(rightSizer, wxSizerFlags().Expand());

	leftTopSizer = new wxBoxSizer(wxVERTICAL);

	leftTopSizer->Add(addNewTaskButton);
	leftTopSizer->AddSpacer(4);
	leftTopSizer->Add(modifyTaskButton);
	leftTopSizer->AddSpacer(4);
	leftTopSizer->Add(markAsDoneButton);
	leftTopSizer->AddSpacer(4);
	leftTopSizer->Add(deleteTaskButton);
	leftTopSizer->AddSpacer(4);

	leftBottomSizer = new wxBoxSizer(wxVERTICAL);

	leftBottomSizer->Add(taskListsHeadline);
	leftBottomSizer->Add(taskListsContainer);

	leftSizer->Add(leftTopSizer);
	leftSizer->Add(leftBottomSizer); 

	rightTopSizer = new wxBoxSizer(wxHORIZONTAL);
	rightSizer->Add(rightTopSizer, wxSizerFlags().Align(wxALIGN_RIGHT));

	userInfoSizer = new wxBoxSizer(wxVERTICAL);

	userInfoSizer->Add(loggedInUserHeadline);
	userInfoSizer->Add(loggedInUsername, wxSizerFlags().Align(wxALIGN_RIGHT));

	userManageSizer = new wxBoxSizer(wxHORIZONTAL);

	userManageSizer->Add(manageUserButton);
	userManageSizer->AddSpacer(4);
	userManageSizer->Add(logOutButton);

	rightTopSizer->Add(userInfoSizer);
	rightTopSizer->AddSpacer(20);
	rightTopSizer->Add(userManageSizer);

	rightBottomSizer = new wxBoxSizer(wxVERTICAL);

	rightBottomSizer->Add(tasksHeadline, wxSizerFlags().CenterHorizontal());
	rightBottomSizer->Add(tasksContainer);

	rightSizer->Add(rightBottomSizer);

	outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 20).Expand());

	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(mainFrame);
	//setup sizers

	//binding buttons
	BindButtons();
	//binding buttons
}

void MainAppWindow::BindButtons(){
	addNewTaskButton->Bind(wxEVT_BUTTON, &MainAppWindow::onAddNewTaskButtonClicked, this);
	modifyTaskButton->Bind(wxEVT_BUTTON, &MainAppWindow::onModifyTaskButtonClicked, this);
	markAsDoneButton->Bind(wxEVT_BUTTON, &MainAppWindow::onMarkAsDoneButtonClicked, this);
	deleteTaskButton->Bind(wxEVT_BUTTON, &MainAppWindow::onDeleteTaskButtonClicked, this);

	manageUserButton->Bind(wxEVT_BUTTON, &MainAppWindow::onManageUserButtonClicked, this);
	logOutButton->Bind(wxEVT_BUTTON, &MainAppWindow::onLogOutButtonClicked, this);
}

void MainAppWindow::onAddNewTaskButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onModifyTaskButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onMarkAsDoneButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onDeleteTaskButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onManageUserButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onLogOutButtonClicked(wxCommandEvent& evt){

}
