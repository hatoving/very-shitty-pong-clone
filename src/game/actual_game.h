#ifndef ACTUAL_GAME_H
#define ACTUAL_GAME_H

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../game.h"

#include "game_entities/paddle.h"
#include "game_entities/ball.h"

class ActualGame
{
    public:
        ActualGame();
        ~ActualGame();

        int score_plyr1 = 0;
        int score_plyr2 = 0;

        int highscore;
        int difficulty = 2;

        sf::Texture txt_line;
        sf::Sprite spr_line;

        void drawAndUpdateStuff(sf::RenderWindow* window, sf::Clock clock, float _dt, int option_endless_selected_this, sf::Event evnt);
        void handlePaddleAI();

        void saveHighscore();

        void rendering_drawText(const std::string textToDraw, const std::string pathToFont, float fontSize, sf::Color color, float xPos, float yPos, float xScale, float yScale, std::string alignment, sf::RenderWindow* window);

        float scale_anim = 1.25;
        float scale_timer = 0.3;

        bool moveToGameOverScreen = false;
        bool endless = false;
        int option_endless_selected = 0;

        sf::Texture loseImage_tex;
        sf::Sprite loseImage_spr;

        bool loseImageTriggered = false;
        float loseImage_alpha = 255;

        sf::SoundBuffer ds_buffer;
        sf::Sound ds_audio;

        sf::Texture winImage_tex;
        sf::Sprite winImage_spr;

        bool winImageTriggered = false;
        float winImage_alpha = 255;

        sf::SoundBuffer hehe_buffer;
        sf::Sound hehe_audio;

        void loseImage(sf::RenderWindow *window);
        void winImage(sf::RenderWindow *window);

        Paddle paddle;
        Ball _ball;
};

#endif // MAIN_MENU_H
