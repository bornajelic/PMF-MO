#include "commands.h"
#include <iostream>

const Game::Category Game::PLANE = 0;
const Game::Category Game::HELLO = 1;

// Game konstruktor.
// Otvara ekran širine 800x600 pixela s naslovom zadatak 11.
// Zatim učitava sliku i font, te kreira dva objekta scene.
Game::Game() :
		mWindow(sf::VideoMode(800, 600), "zadatak 11"), mTexture(), mFont(), mQueue() {
	// učitaj sliku aviona
	if (!mTexture.loadFromFile("Raptor.png"))
		throw std::runtime_error("Cannot open file Raptor.png!");

	// učitaj fontove
	if (!mFont.loadFromFile("Sansation.ttf"))
		throw std::runtime_error("Cannot open file Sansation.ttf!");

	// kreiraj dva objekta na sceni -- sliku i tekst
	// Kako su dinamički alocirani prepuštamo unique_ptr klasi brigu o
	// dealokaciji.
	mSceneGraph[PLANE] = std::unique_ptr<SpriteNode>(new SpriteNode(mTexture));
	mSceneGraph[PLANE]->setPosition(200, 300);
	mSceneGraph[HELLO] = std::unique_ptr<TextNode>(new TextNode(mFont));
	mSceneGraph[HELLO]->setPosition(600, 300);
}

// game-loop. Ovo je glavna petlja programa.
void Game::run() {
	// beskonačna petlja koja se izvršava sve dok ne zatvorimo
	// prozor.
	while (mWindow.isOpen()) {
		processEvents();
		update();
		render();  // iscrtavanje
	}
}

// obrada događaja
void Game::processEvents() {
// Od prozora zahtjevamo sve događaje koji su se desili
	sf::Event event;

	// rotate function:
	auto rotate_cclockwise = [](SceneNode* node) {node->rotate(-10.0f);};
	auto rotate_clockwise = [](SceneNode* node) {node->rotate(10.0f);};
	auto move_right = [](SceneNode* node) {node-> move(10,0);};
	auto move_left = [](SceneNode* node) {node-> move(-10,0);};
	auto move_up = [](SceneNode* node) {node-> move(0,-10);};
	auto move_down = [](SceneNode* node) {node-> move(0,10);};
	while (mWindow.pollEvent(event)) {
		// event.type je tip događaja.
		// sf::Event::Closed znači prozor je zatvoren
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		} else if (event.type == sf::Event::KeyPressed) {
			// sf::Event::KeyPressed = stisnuta je tipka na tastaturi
			// event.key.code daje kod stisnute tipke.
			sf::Keyboard::Key code = event.key.code;
			// event.key.alt signalizira da li je istovremeno stisnuta tipka ALT
			bool alt = event.key.alt;
			// event.key.control signalizira da li je istovremeno stisnuta tipka CRTL
			bool ctrl = event.key.control;
			// odluka o tome što ćemo rotirati u update() metodi
			if (alt && code == sf::Keyboard::R) {
				mQueue.push(Command(rotate_cclockwise, Game::PLANE));
			}
			if (ctrl && code == sf::Keyboard::R) {
				mQueue.push(Command(rotate_cclockwise, Game::HELLO));
			}
			if (alt && code == sf::Keyboard::W) {
				mQueue.push(Command(rotate_clockwise, Game::PLANE));
			}
			if (ctrl && code == sf::Keyboard::W) {
				mQueue.push(Command(rotate_clockwise, Game::HELLO));
			}
			// transformacije:
			if (alt && code == sf::Keyboard::Up) {
				mQueue.push(Command(move_up, Game::PLANE));
			}
			if (ctrl && code == sf::Keyboard::Up) {
				mQueue.push(Command(move_up, Game::HELLO));
			}
			if (alt && code == sf::Keyboard::Down) {
				mQueue.push(Command(move_down, Game::PLANE));
			}
			if (ctrl && code == sf::Keyboard::Down) {
				mQueue.push(Command(move_down, Game::HELLO));
			}
			if (alt && code == sf::Keyboard::Left) {
				mQueue.push(Command(move_left, Game::PLANE));
			}
			if (ctrl && code == sf::Keyboard::Left) {
				mQueue.push(Command(move_left, Game::HELLO));
			}
			if (alt && code == sf::Keyboard::Right) {
				mQueue.push(Command(move_right, Game::PLANE));
			}
			if (ctrl && code == sf::Keyboard::Right) {
				mQueue.push(Command(move_right, Game::HELLO));
			}
		}
	}
}

// update vrši rotaciju objekta u grafu scene
// (i sve druge tražene transformacije)
void Game::update() {
	while (!mQueue.empty()) {
		Command command = mQueue.front();
		for (std::unique_ptr<SceneNode> & node : mSceneGraph) {
			node->onCommand(command);
		}
		mQueue.pop();
	}
}

// Iscrtavanje
// -- očisti prozor,
// -- iscrtaj sve objekte na sceni (to se radi u "pozadini"),
// -- prikaži novo stanje prozora
// Metodu ne mijenjati.
void Game::render() {
	mWindow.clear();
	for (auto & node : mSceneGraph) {
		mWindow.draw(*node);
	}
	mWindow.display();
}
