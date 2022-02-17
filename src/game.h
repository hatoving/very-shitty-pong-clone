#pragma once

#include <iostream>
#include <experimental/random>
#include <fstream>

#include <SFML/System/Vector2.hpp>
//#include <string>
#include <SFML/Graphics.hpp>

#include "game/main_menu.h"
#include "game/actual_game.h"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 544

enum _CurrentState {TITLE, GAME, GAME_OVER};

class MainGame
{
    public:
        sf::RenderWindow window;
        sf::Event event;

        MainGame(int framerate);
        ~MainGame();

        // -- MAIN GAME STUFF --

        sf::Clock dtClock;
        float _dt;

        float fadeAlpha = 255;

        void run();
        void gameLoop();
        void handleEvents();

        void updateDT();
        void loadHighscore();

        void rendering_drawImage();
        void rendering_drawText(const std::string textToDraw, const std::string pathToFont, float fontSize, sf::Color color, float xPos, float yPos, std::string alignment);

        _CurrentState _cs;

        int highscore;

        // SUTFF //
        MainMenu _mainMenu;
        ActualGame actualGame;
};
