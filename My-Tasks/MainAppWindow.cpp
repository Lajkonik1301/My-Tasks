#include "MainAppWindow.h"

MainAppWindow::MainAppWindow(MainFrame* mainFrame, DatabaseManager* databaseManager, User* user) {
	this->mainFrame = mainFrame;
	this->user = user;
	this->databaseManager = new DatabaseManager();
	panel = new wxPanel(mainFrame);
	categoriesChoices = {};
	tasksChoices = {};

	populateCategoriesContainer();
	populateTasksContainer();

	//place items
	addNewTaskButton = new wxButton(panel, wxID_ANY, "Dodaj", wxDefaultPosition, wxSize(150, -1));
	modifyTaskButton = new wxButton(panel, wxID_ANY, "Zmieñ", wxDefaultPosition, wxSize(150, -1));
	markAsDoneButton = new wxButton(panel, wxID_ANY, "Oznacz jako wykonane", wxDefaultPosition, wxSize(150, -1));
	deleteTaskButton = new wxButton(panel, wxID_ANY, "Usuñ", wxDefaultPosition, wxSize(150, -1));;

	taskListsHeadline = new wxStaticText(panel, wxID_ANY, "Listy zadañ");
	taskListsContainer = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(150, -1), categoriesChoices);

	loggedInUserHeadline = new wxStaticText(panel, wxID_ANY, "Zalogowany u¿ytkownik:");
	loggedInUsername = new wxStaticText(panel, wxID_ANY, "test-username");

	manageUserButton = new wxButton(panel, wxID_ANY, "Zarz¹dzaj", wxDefaultPosition, wxSize(100, -1));
	logOutButton = new wxButton(panel, wxID_ANY, "Wyloguj siê", wxDefaultPosition, wxSize(100, -1));

	tasksHeadline = new wxStaticText(panel, wxID_ANY, "Zadania:");
	tasksContainer = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 200), tasksChoices);
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

void MainAppWindow::populateCategoriesContainer() {
	std::vector<std::string> categories;

	databaseManager->getCategories(categories, user->getId());
	
	for (const auto& category : categories) {
		categoriesChoices.Add(wxString::FromUTF8(category));
	}
}

void MainAppWindow::populateTasksContainer(){
	std::vector<std::string> tasks;

	databaseManager->getTasks(tasks, user->getId());

	for (const auto& task : tasks) {
		tasksChoices.Add(wxString::FromUTF8(task));
	}
}

void MainAppWindow::onAddNewTaskButtonClicked(wxCommandEvent& evt){
	//addTaskWindowInstance = new addTaskWindow(mainFrame, databaseManager, user->getId());
	std::string kod = databaseManager->addNewTask(1, 1, "Testowy task", "Opis testowego taska", 2);
	wxMessageBox(kod);
}

void MainAppWindow::onModifyTaskButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onMarkAsDoneButtonClicked(wxCommandEvent& evt){
	databaseManager->markAsDone(1);
}

void MainAppWindow::onDeleteTaskButtonClicked(wxCommandEvent& evt){
	int selected = tasksContainer->GetSelection();
	if (selected == wxNOT_FOUND) {
		wxMessageBox("Nie wybrano ¿adnego elementu.", "B³¹d", wxOK | wxICON_ERROR);
		return;
	}

	wxString selectedTask = tasksContainer->GetString(selected);

	int response = wxMessageBox("Czy na pewno chcesz usun¹æ '" + selectedTask + "'?",
		"Potwierdzenie usuniêcia",
		wxYES_NO | wxICON_QUESTION);

	if (response == wxYES) {
		tasksContainer->Delete(selected);
		databaseManager->deleteTask(selectedTask.ToStdString());
		wxMessageBox("Element zosta³ usuniêty.", "Sukces", wxOK | wxICON_INFORMATION);
	}
}

void MainAppWindow::onManageUserButtonClicked(wxCommandEvent& evt){

}

void MainAppWindow::onLogOutButtonClicked(wxCommandEvent& evt){
	delete user;
	mainFrame->ContinueAfterLogOut();
}
