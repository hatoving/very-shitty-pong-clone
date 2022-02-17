#include "ball.h"

Ball::Ball() {
};

void Ball::drawAndUpdateBall(sf::RenderWindow* window, float _dt)
{
    txt_ball.loadFromFile("assets/sprites/spr_ball.png");
    spr_ball.setTexture(txt_ball);

    spr_ball.setOrigin(spr_ball.getGlobalBounds().width / 2, spr_ball.getGlobalBounds().height / 2);

    if (!launched)
    {
        launch();
        launched = true;
    }

    //spr_ball.move(speed, speed);
    xPos += (velocity.x / 2) * speed.x;
    yPos += (velocity.y / 2) * speed.y;
    spr_ball.setPosition(xPos,yPos);

    spr_ball.setScale(2, 2);

    window->draw(spr_ball);
}

void Ball::launch()
{
    xPos = 960 / 2;
    yPos = 544 / 2;

    //random_x = std::experimental::randint(-2, 2);
    random_y = std::experimental::randint(-2, 2);

    if (player1Scored) random_x = -2;
    else if (player2Scored) random_x = 2;

    if (random_y == 0) random_y = std::experimental::randint(-2, 2);

    velocity = sf::Vector2f(random_x, random_y);
}
