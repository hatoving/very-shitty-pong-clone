#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Paddle
{
    public:
        Paddle();
        ~Paddle();

        sf::Texture txt_paddle;
        sf::Sprite spr_paddle;

        sf::Texture txt_paddle_right;
        sf::Sprite spr_paddle_right;

        float xPos = 50;
        float xPos_right = 910;

        float yPos = 544 / 2;
        float yPos_right = 544 / 2;

        float speed = 2;
        float speed_right = 5;

        void drawAndUpdatePaddlePlayerOne(sf::RenderWindow* window);
        void drawAndUpdatePaddlePlayerTwo(sf::RenderWindow* window);

        // AI PADDLE SHIT
        float aiReaction = 0.2;
        int aiError = 40;
};

#endif // MAIN_MENU_H
