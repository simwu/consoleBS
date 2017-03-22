#include "view.h"
#include "controller.h"

void main() {

	Controller controller;
	View view(controller);
	view.mainMenu();
}
