#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"



PlayScreen::PlayScreen(Window* window):_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_spriteFont = new SpriteFont("Fonts/arial.ttf", 42);
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	
	_background = new Background("Textures/background.png");
	initGUI();
	_jugador = new Jugador(
		36,58,
		glm::vec2(_window->getScreenWidth()/2.0f,100),
		"Textures/player_idle.png",&_game->_inputManager
		);
	tickTimer = 120;
	timer = 0;
	srand(NULL);
}



void PlayScreen::update() {
	checkInput();//CAMBIADO-> ESTO ESTABA AL FINAL DEL UPDATE
	_camera2D.update();
	_jugador->update(0.02f, false);

	if (_game->_inputManager.wasKeyPressed(SDL_BUTTON_LEFT)) {
		if(_jugador->canShoot()) _bullets.push_back(new Bullet(5, 3, _jugador->_position + glm::vec2(30, 25), "Textures/Bullet.png"));
		_jugador->useBullet();
	}

	for (unsigned int i = 0; i < _bullets.size(); i++) {
		_bullets[i]->update(0.02f, false);
	}

	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i]->update(0.02f, false);

		if (_enemies[i]->_position.x == 0) {
			_currentState = ScreenState::CHANGE_NEXT;
			break;
		}

		for (unsigned int j = 0; j < _bullets.size(); j++) {
			if (_enemies[i]->collideWithAgent(_bullets[j])) {
				_enemies[i]->life -= 1;
				if (_enemies[i]->life == 0) {
					_jugador->score += 10;
					Enemy* temp = _enemies[i];
					_enemies.erase(_enemies.begin() + i);
					delete temp;
				}
				Bullet* temp2 = _bullets[j];
				_bullets.erase(_bullets.begin() + j);
				delete temp2;
				i -= 1;
				break;
			}
		}
	}

	if (timer == tickTimer) {
		tickTimer = 60 + rand() % 20;
		timer = 0;
		_enemies.push_back(new Enemy(38, 58, glm::vec2(1050, 58 + rand() % (_window->getScreenHeight() - 58)), "Textures/zombie_idle.png", rand() % 3));
	}

	timer += 1;
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::draw() {
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
	_jugador->draw(_spriteBatch);

	for (unsigned int i = 0; i < _enemies.size(); i++) {
		_enemies[i]->draw(_spriteBatch);
	}

	for (unsigned int i = 0; i < _bullets.size(); i++) {
		_bullets[i]->draw(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();
	sprintf_s(buffer, ("Bullets: " + std::to_string(_jugador->bulletCount) + " Magazines: " + std::to_string(_jugador->magazineCount)).c_str());
	_spriteFont->draw(_hudBach, buffer, glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255)
	);

	sprintf_s(buffer, ("Score: " + std::to_string(_jugador->score)).c_str());
	_spriteFont->draw(_hudBach, buffer, glm::vec2(0, 20),
		glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255)
	);

	if (_jugador->bulletCount == 0) {

		sprintf_s(buffer, ("RELOAD!!!!!"));
		_spriteFont->draw(_hudBach, buffer, glm::vec2(350, 220),
			glm::vec2(0.7), 0.0f, ColorRGBA(0, 0, 0, 255)
		);

		sprintf_s(buffer, ("press R"));
		_spriteFont->draw(_hudBach, buffer, glm::vec2(400, 200),
			glm::vec2(0.5), 0.0f, ColorRGBA(0, 0, 0, 255)
		);
	}

	_hudBach.end();
	_hudBach.renderBatch();
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
