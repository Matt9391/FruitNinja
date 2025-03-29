#include <iostream>
#include <vector>
//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//libraries
#include "Fruit.h"
#include "Functions.h"
#include "Random.h"
#include "Slash.h"
#include "Bomb.h"
#include "HalfFruit.h"
#include "UI.h"
#include "Menu.h"

//vector of game objects
std::vector<HalfFruit> halfFruits;
std::vector<Fruit> fruits;
std::vector<Bomb> bombs;
//varabile that keep track of the scene
int scene = 0;

int main()
{    
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fruit Ninja");
    window.setFramerateLimit(60);

    //loaded sounds vector
    std::vector<sf::SoundBuffer> sounds;
    //sounds paths
    std::vector<std::string> soundsPaths = {
           "./Audio/Dance of the Dragon Fruit.ogg",
           "./Audio/SlashSound.ogg"
    };

    //loading sounds
    for (const auto& path : soundsPaths) {
        sf::SoundBuffer sb;
        if (sb.loadFromFile(path)) {
            sounds.push_back(std::move(sb));
        }
        else {
            std::cerr << "errore nell'import delle sound";
        }
    }

    //loaded textures vector
    std::vector<sf::Texture> textures;
    //textures paths
    std::vector<std::string> texturesPaths = {
        "./Sprites/orange.png",
        "./Sprites/orangeTop.png",
        "./Sprites/orangeBottom.png",
        "./Sprites/peach.png",
        "./Sprites/peachTop.png",
        "./Sprites/peachBottom.png",
        "./Sprites/watermelon.png",
        "./Sprites/watermelonTop.png",
        "./Sprites/watermelonBottom.png",
        "./Sprites/bomb.png",
        "./Sprites/background.png"
    };

    //loading textures
    for (const auto& path : texturesPaths) {
        sf::Texture txt;
        if (txt.loadFromFile(path)) {
            textures.push_back(std::move(txt));
        }
        else {
            std::cerr << "errore nell'import delle immagine";
        }
    }

    //loaded texturesGUI vector
    std::vector<sf::Texture> texturesGUI;
    //texturesGUI paths
    std::vector<std::string> texturesGUIPaths = {
        "./Sprites/heart.png",
        "./Sprites/button.png",
        "./Sprites/alert.png"
    };

    //loading texturesGUI
    for (const auto& path : texturesGUIPaths) {
        sf::Texture txt;
        if (txt.loadFromFile(path)) {
            texturesGUI.push_back(std::move(txt));
        }
        else {
            std::cerr << "errore nell'import delle immagine";
        }
    }
    
    //initializing random
    Random::Init();
    //game frame count 
    int frameCount = 0;
    //initializing UI
    UI::init(window, texturesGUI[0], texturesGUI[2], sounds[0], texturesGUI[1]);
    //initializing Menu
    Menu::init(window, texturesGUI[1]);

    //background image
    sf::Sprite background;
    sf::Texture& bgTxt = textures[textures.size() - 1];
    background.setTexture(bgTxt);
    background.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    background.setOrigin(bgTxt.getSize().x / 2.f, bgTxt.getSize().y / 2.f);

    //Slash / Cursor
    Slash slash(window,sounds[1]);

    //increment of rate of spawing of entitys
    int incr = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        if(scene == 0){
            sceneMenu(window,background,slash);
        }else{
            sceneGameplay(frameCount,incr, window,fruits,bombs,background,slash,textures);
        }
        
    }

    return 0;
}




