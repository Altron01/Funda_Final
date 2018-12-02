#include "App.h"
#include "ScreenList.h"
#include "InstructionsScreen.h"


App::App()
{
}


void App::onInit() {

}

void App::setScreen(int index) {
	_screenList->setScreen(index);
}
void App::addScreens() {
	_menuScreen = std::make_unique<MenuScreen>(&_window);
	_instructionsScreen = std::make_unique<InstructionsScreen>(&_window);
	_playScreen = std::make_unique<PlayScreen>(&_window);
	_endScreen = std::make_unique<EndScreen>(&_window);
	_screenList->addScreen(_menuScreen.get());
	_screenList->addScreen(_instructionsScreen.get());
	_screenList->addScreen(_playScreen.get());
	_screenList->addScreen(_endScreen.get());
	_screenList->setScreen(_menuScreen->getIndex());

}


void App::onExit() {
}


App::~App()
{
}
