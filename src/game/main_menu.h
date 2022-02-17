#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <algorithm>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MainMenu
{
    public:
        MainMenu();
        ~MainMenu();

        int option_selected = 0;
        int option_selected_endless = 0;
        bool themeLoaded = false;

        void initStuff(sf::RenderWindow* window, float dt);
        void handleOptions(sf::RenderWindow* window, sf::Event evnt);

        void rendering_drawText(const std::string textToDraw, const std::string pathToFont, float fontSize, sf::Color color, float xPos, float yPos, float xScale, float yScale, std::string alignment, sf::RenderWindow* window);

        sf::Texture logo_tex;
        sf::Sprite logo_spr;

        sf::Music music;

        sf::Color txtColorPlay = sf::Color::White;
        sf::Color txtColorQuit = sf::Color::Red;

        float text_scale_value_play = 1;
        float text_scale_value_quit = 1;

        bool triggerGame = false;
        float fadeAlpha = 255;
};

#endif // MAIN_MENU_H
