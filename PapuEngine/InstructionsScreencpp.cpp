#include "InstructionsScreen.h"
#include "MyScreens.h"
#include "Game.h"


InstructionsScreen::InstructionsScreen(Window* window) :
	_window(window), btnGameClicked(false)
{
	timer = 0;
	_screenIndex = SCREEN_INDEX_MENU;
}

void InstructionsScreen::initGUI() {
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
	_button = new Button("Textures/menu_button.png");
}

void InstructionsScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void InstructionsScreen::destroy() {
	delete _background;
	delete _button;
}

void InstructionsScreen::onExit() {}

void InstructionsScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	_background = new Background("Textures/background.png");
	initGUI();
}

void InstructionsScreen::update() {
	_camera2D.update();
	timer += 1;
	if (timer == 240) {
		_currentState = ScreenState::CHANGE_NEXT;
	}
	checkInput();
}

void InstructionsScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void InstructionsScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();
	_background->draw(_spriteBatch);
	_spriteBatch.end();
	_spriteBatch.renderBatch();


	char buffer[256];
	_spriteBatch.begin();
	sprintf(buffer, "Instructions");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 180), glm::vec2(0.3), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_spriteBatch.begin();
	sprintf(buffer, "1: (Left Click) Shoot");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 160), glm::vec2(0.3), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_spriteBatch.begin();
	sprintf(buffer, "2: (R) Reload");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 140), glm::vec2(0.3), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_spriteBatch.begin();
	sprintf(buffer, "3: (Arrows) Move");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 120), glm::vec2(0.3), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();


	_spriteBatch.begin();
	sprintf(buffer, "4: Kill the enemies, dont let them go to the other side of the road");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50,100), glm::vec2(0.3), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();


	_spriteBatch.begin();
	sprintf(buffer, "5: Zombies: Green(1 shot), Red(2 shot), Blue(3 shot)");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 80), glm::vec2(0.3), 0.0f,
		ColorRGBA(255, 255, 255, 255));

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void InstructionsScreen::build() {}

int InstructionsScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int InstructionsScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

InstructionsScreen::~InstructionsScreen()
{
}
