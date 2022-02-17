#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <experimental/random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/System/Vector2.hpp>

#define PI 3.14159265359

class Ball
{
    public:
        Ball();

        sf::Texture txt_ball;
        sf::Sprite spr_ball;

        sf::Vector2f speed = sf::Vector2f(2, 2);

        float random_x;
        float random_y;

        bool launched = false;
        bool player1Scored = false;
        bool player2Scored = true;

        sf::Vector2f velocity;

        float xPos = 960 / 2;
        float yPos = 544 / 2;

        void drawAndUpdateBall(sf::RenderWindow* window, float _dt);
        void launch();
};

#endif // MAIN_MENU_H
