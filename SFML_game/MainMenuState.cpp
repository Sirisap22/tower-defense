#include "MainMenuState.h"

// Initialzer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("public/backgrounds/mainmenu_bg.png"))
	{
		throw "ERROR::MAINMENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/EvilEmpire-4BBVK.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		300.f, 440.f, 200.f, 50.f,
		&this->font, "New Game", 72,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["LEADERBOARD"] = new Button(
		300, 540, 200, 50,
		&this->font, "Leaderboard", 72,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["HOW_TO_PLAY"] = new Button(
		300, 640, 200, 50,
		&this->font, "How to Play", 72,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CREDIT"] = new Button(
		300, 740, 200, 50,
		&this->font, "Credit", 72,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);


	this->buttons["EXIT_STATE"] = new Button(
		300, 840, 200, 50,
		&this->font, "Quit", 72,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void MainMenuState::initLeaderBoard()
{
	this->leaderBoard = new Plane(1030.f, 275.f, 500.f, 450.f, &this->font, 72, 48);
}

void MainMenuState::initInputField()
{
	this->InputPlane = new InputFieldPlane(1030.f, 375.f, 500.f, 300.f, &this->font, 72, 0);
	this->buttons["START_GAME"] = new Button(
		1060, 600, 200, 50,
		&this->font, "Start", 52,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CANCEL_GAME"] = new Button(
		1300, 600, 200, 50,
		&this->font, "Cancel", 52,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 100), sf::Color(70, 70, 70, 200),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);


}

void MainMenuState::initSounds()
{
	if (!this->clickBuffer.loadFromFile("public/sounds/menu_click.wav")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_SOUND");
	}

	this->click.setBuffer(this->clickBuffer);
	this->click.setVolume(50.f);
}

void MainMenuState::initCreditPlane()
{
	this->creditPlane = new CreditPlane(
		1030.f, 275.f, 500.f, 250.f, &this->font, 72, 48
	);
}

void MainMenuState::initGoalsAndContralPlane()
{
	this->goalsPlane = new GoalsPlane(
		900.f, 275.f, 800.f, 200.f, &this->font, 48, 36
	);

	this->contralPlane = new ContralPlane(
		900.f, 500.f, 800.f, 250.f, &this->font, 48, 36
	);
}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, bool* shouldPollEvent)
	: State(window, supportedKeys, states)
{
	this->toggleLeaderBoard = false;
	this->toggleInputField = false;
	this->toggleCreditPlane = false;
	this->toggleGoalsAndContralPlane = false;
	this->shouldPollEvent = shouldPollEvent;
	*this->shouldPollEvent = true;

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initFonts();
	this->initLeaderBoard();
	this->initInputField();
	this->initCreditPlane();
	this->initGoalsAndContralPlane();
	this->initSounds();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->leaderBoard;

	delete this->creditPlane;

	delete this->goalsPlane;

	delete this->contralPlane;
	//if (this->input)
	//	delete this->input;

}

void MainMenuState::toggleStatePaused()
{
}

void MainMenuState::updateInput(const float& dt)
{
	this->input->update(dt, this->mousePosView);

}

void MainMenuState::updateShouldPollEvent()
{
	if (this->toggleInputField) {
		*this->shouldPollEvent = false;
	}
	else {
		*this->shouldPollEvent = true;
	}
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->click.play();
		this->input = new InputField(this->window, 1130.f, 500.f, 300.f, 50.f, &this->font, 34);
		this->toggleInputField = !this->toggleInputField;

		this->toggleLeaderBoard = false;
		this->toggleCreditPlane = false;
		this->toggleGoalsAndContralPlane = false;
		if (!this->toggleInputField) {
			delete this->input;
		}
	}

	if (this->buttons["START_GAME"]->isPressed() && this->input->getName().size() > 0) {
		this->click.play();
		this->toggleInputField = false;
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->input->getName()));
		delete this->input;
		*this->shouldPollEvent = true;
	}

	if (this->buttons["CANCEL_GAME"]->isPressed()) {
		this->click.play();
		this->toggleInputField = false;
		delete this->input;
	}

	if (this->buttons["LEADERBOARD"]->isPressed()) {
		this->click.play();
		if (this->toggleInputField) {
			this->toggleInputField = false;
			delete this->input;
		}
		this->toggleCreditPlane = false;	
		this->toggleGoalsAndContralPlane = false;

		this->leaderBoard = new Plane(1030.f, 275.f, 500.f, 450.f, &this->font, 72, 48);;
		this->toggleLeaderBoard = !this->toggleLeaderBoard;
	}

	if (this->buttons["HOW_TO_PLAY"]->isPressed()) {
		this->click.play();
			if (this->toggleInputField) {
			this->toggleInputField = false;
			delete this->input;
		}
		this->toggleLeaderBoard = false;
		this->toggleCreditPlane = false;

		this->toggleGoalsAndContralPlane = !this->toggleGoalsAndContralPlane;
	}

	if (this->buttons["CREDIT"]->isPressed()) {
		this->click.play();
		if (this->toggleInputField) {
			this->toggleInputField = false;
			delete this->input;
		}
		this->toggleLeaderBoard = false;
		this->toggleGoalsAndContralPlane = false;

		this->toggleCreditPlane = !this->toggleCreditPlane;
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->click.play();
		this->endState();
	}



}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateShouldPollEvent();

	if (this->toggleInputField) {
		this->updateInput(dt);
	}

	this->updateButtons();


}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		if (it.first == "START_GAME" || it.first == "CANCEL_GAME") {
			if (this->toggleInputField) it.second->render(target);
		}
		else {
			it.second->render(target);
		}
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	if (this->input && this->InputPlane && this->toggleInputField) {
		this->InputPlane->render(target);
		this->input->render(target);

	}

		
	this->renderButtons(target);


	if (this->toggleLeaderBoard) {
		this->leaderBoard->render(target);
	}

	if (this->toggleCreditPlane) {
		this->creditPlane->render(target);
	}

	if (this->toggleGoalsAndContralPlane) {
		this->goalsPlane->render(target);
		this->contralPlane->render(target);
	}


	// remove later
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y-50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(18);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}
