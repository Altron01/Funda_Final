#include "EndScreen.h"
#include "Game.h"
#include "MyScreens.h"




EndScreen::EndScreen(Window* window) :
	_window(window)
{
}
void EndScreen::initGUI() {
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
}

void EndScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void EndScreen::destroy() {
	delete _background;
}

void EndScreen::onExit() {}

void EndScreen::onEntry() {
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

void EndScreen::update() {
	_camera2D.update();
	checkInput();
}

void EndScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void EndScreen::draw() {
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
	sprintf(buffer, "ESPERO QUE LE GUSTE PROFE NECESITO LA BECA :'v");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 100), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	buffer[256];
	_spriteBatch.begin();
	sprintf(buffer, "Aqui termina");
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(50, 140), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 255, 255));
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void EndScreen::build() {}

int EndScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int EndScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}




EndScreen::~EndScreen() {
}