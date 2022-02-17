#include "paddle.h"

Paddle::Paddle() {
};

Paddle::~Paddle() {
};

void Paddle::drawAndUpdatePaddlePlayerOne(sf::RenderWindow* window)
{
    //Handle the player paddle :0
    txt_paddle.loadFromFile("assets/sprites/spr_paddle.png");

    spr_paddle.setTexture(txt_paddle);
    spr_paddle.setOrigin((spr_paddle.getGlobalBounds().width / 2), (spr_paddle.getGlobalBounds().height / 2));
    spr_paddle.setPosition(xPos, yPos);
    spr_paddle.setScale(3, 3);

    window->draw(spr_paddle);

    if(yPos > 595) yPos = 595;
    else if(yPos < 153) yPos = 153;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        yPos -= speed;
        //a + (b - a) * x;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        yPos += speed;
    }
}

void Paddle::drawAndUpdatePaddlePlayerTwo(sf::RenderWindow* window)
{
    //Handle the AI paddle
    txt_paddle_right.loadFromFile("assets/sprites/spr_paddle.png");

    spr_paddle_right.setTexture(txt_paddle_right);
    spr_paddle_right.setOrigin(spr_paddle_right.getGlobalBounds().width / 2, spr_paddle_right.getGlobalBounds().height / 2);
    spr_paddle_right.setPosition(xPos_right, yPos_right);
    spr_paddle_right.setScale(-3, 3);

    window->draw(spr_paddle_right);

    if(yPos_right > 595) yPos_right = 595;
    else if(yPos_right < 153) yPos_right = 153;
}
