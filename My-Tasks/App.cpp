#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("My Tasks");
	mainFrame->Show();

	return true;
}