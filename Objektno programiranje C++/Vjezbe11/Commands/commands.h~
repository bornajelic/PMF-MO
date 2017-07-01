#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <queue>
#include <functional>

class SceneNode;
struct Command;

// Klasa koja predstavlja igru. Osim konstruktora ima samo
// jednu javnu metodu - run().
class Game {
public:
	// konstruktor
	Game();
	// pokreni aplikaciju
	void run();
	using Category = int;
	static const Category PLANE;
	static const Category HELLO;
private:
	// procesiraj događaje
	void processEvents();
	// konstruiraj novo stanje igre
	void update();
	// iscrtaj novo stanje
	void render();
private:
	// glavni prozor
	sf::RenderWindow mWindow;
	// slika
	sf::Texture mTexture;
	// font
	sf::Font mFont;

	// Graf scene čine svi objekti koje iscrtavamo na ekranu.
	// Ovdje imamo samo dva objekta na sceni, jednu sliku i jedan tekst.
	std::array<std::unique_ptr<SceneNode>, 2> mSceneGraph;

	std::queue<Command> mQueue;
};

struct Command {
	Command(std::function<void(SceneNode*)> _action, Game::Category _category) :
			action(_action), category(_category) {
	}
	std::function<void(SceneNode*)> action;
	Game::Category category = -1;
};

// Apstraktna klasa koja predstavlja sve što iscrtavamo na ekranu.
// Nasljeđuje sf::Drawable koja deklarira metodu draw() koju treba
// preraditi u izvedenim klasama. Nasljeđuje klasu sf:Drawable u
// kojoj su definirane metode rotate() i move() (i mnoge druge).
class SceneNode: public sf::Transformable,
		public sf::Drawable,
		private sf::NonCopyable {
public:
	virtual void update()= 0;
	virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states) const = 0;
	virtual Game::Category getCategory() = 0;
	virtual void onCommand(Command const & cmd) {
		if (cmd.category == getCategory()) {
			cmd.action(this);
		}
	}
};

// Klasa koja predstavlja sliku koju ćemo iscrtavati na ekranu.
class SpriteNode: public SceneNode {
public:
	explicit SpriteNode(const sf::Texture& texture) :
			mSprite(texture) {
	}
	// update slike prije iscrtavanja. Ovdje se radi o rotaciji za 10 stupnjeva
	// u pozitivnom smjeru. rotate() je funkcija naslijeđena iz sf::Transformable
	virtual void update() {
	}
	// iscrtavanje -- ne mijenjati
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}
	virtual Game::Category getCategory() {
		return Game::PLANE;
	}
private:
	// slika za iscrtavanje
	sf::Sprite mSprite;
};

// Klasa koja predstavlja tekst koji ćemo iscrtavati na ekranu.
class TextNode: public SceneNode {
public:
	// Konstruktor.
	explicit TextNode(const sf::Font & font) {
		mText.setFont(font);
		mText.setString("Hello");
		mText.setCharacterSize(36);
		mText.setColor(sf::Color::Blue);
	}
	// update teksta prije iscrtavanja. Ovdje se radi o rotaciji za 10 stupnjeva
	// u pozitivnom smjeru. rotate() je funkcija naslijeđena iz sf::Transformable
	virtual void update() {
//		rotate(-10.0f);
	}
	// iscrtavanje -- ne mijenjati
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(mText, states);
	}
	virtual Game::Category getCategory() {
		return Game::HELLO;
	}
private:
	// tekst za iscrtavanje
	sf::Text mText;
};

#endif // COMMANDS_H_INCLUDED
