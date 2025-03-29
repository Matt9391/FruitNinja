#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#pragma once
class Slash
{
public:
	//constructor for slash, takes the window and the soundBuffer of the slash
	Slash(sf::RenderWindow& window, sf::SoundBuffer& sb);
	void update(sf::RenderWindow& window);

	//function that return the head of the slash, that is the last element of the array of circles
	sf::CircleShape getHead();
	//function that return if you're dragging your mouse
	bool getSlashing();

	void display(sf::RenderWindow& window);

	static void SlashSoundPlay();
private:

	//function that check if you're dragging your mouse
	bool checkSlashing();
	//method that update the slash composed of vertex
	void moveSlash();
	//method that add a circle to the vector 
	void addCircle(sf::Vector2f& mousePos, sf::Vector2f* spawnPos);

	bool slashing;
	//number of tails/circles of the slash
	int maxTails;
	float radius;
	//vertex of the slash
	sf::VertexArray slash;
	//cirlces used to generate the slash of vertex
	std::vector<sf::CircleShape> circles;

	static sf::Sound slashSound;
};

