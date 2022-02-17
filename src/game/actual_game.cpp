#include "../game.h"
#include "actual_game.h"

#include <experimental/random>
#include <fstream>

ActualGame::ActualGame() {
};

ActualGame::~ActualGame(){};

void ActualGame::drawAndUpdateStuff(sf::RenderWindow* window, sf::Clock clock, float _dt, int option_endless_selected_this, sf::Event evnt)
{
    txt_line.loadFromFile("assets/sprites/spr_line.png");

    spr_line.setTexture(txt_line);
    spr_line.setOrigin(spr_line.getGlobalBounds().width / 2, spr_line.getGlobalBounds().height / 2);
    spr_line.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    window->draw(spr_line);

    //std::cout << std::to_string(scale_timer) << std::endl;

    //scale_anim = custom_lerp(scale_anim, 1, 0.15);

    if (scale_timer < 0)
    {
        scale_timer = 0.3;
        scale_anim = 1.25;
    }
    else if(scale_anim > 0)
    {
        scale_timer -= 0.01;
        //yPos = yPos + (yPos - 2 - 0) * 0.3;
        scale_anim = scale_anim + (1 - scale_anim) * 0.3;
    }

    rendering_drawText(std::to_string(score_plyr1), "assets/font.otf", 13.333 * 5, sf::Color::White, 474 / 2, 75, scale_anim, scale_anim, "center", window);
    rendering_drawText(std::to_string(score_plyr2), "assets/font.otf", 13.333 * 5, sf::Color::White, 720, 75, scale_anim, scale_anim, "center", window);

    _ball.drawAndUpdateBall(window, _dt);

    paddle.drawAndUpdatePaddlePlayerOne(window);
    paddle.drawAndUpdatePaddlePlayerTwo(window);

    if (_ball.spr_ball.getPosition().x < 0)
    {
        score_plyr2++;
        _ball.launched = false;

        _ball.player2Scored = true;
        _ball.player1Scored = false;

        loseImage_alpha = 255;
        loseImageTriggered = true;

        ds_buffer.loadFromFile("assets/audio/ds.wav");
        ds_audio.setBuffer(ds_buffer);

        if(ds_audio.getStatus() != sf::Sound::Playing)
        {
            ds_audio.play();
        }
    }
    if (_ball.spr_ball.getPosition().x >= 959)
    {
        score_plyr1++;
        _ball.launched = false;

        //if (difficulty > 1) difficulty--;

        _ball.speed.x += 0.5;
        _ball.speed.y += 0.5;

        if (score_plyr1 > 4) paddle.speed += 0.5;
        else paddle.speed += 0.25;

        if (score_plyr1 > 4) paddle.speed_right += 0.5;
        else paddle.speed_right += 0.25;

        _ball.player2Scored = false;
        _ball.player1Scored = true;

        winImage_alpha = 255;
        winImageTriggered = true;

        hehe_buffer.loadFromFile("assets/audio/hehe.wav");
        hehe_audio.setBuffer(hehe_buffer);

        if(hehe_audio.getStatus() != sf::Sound::Playing)
        {
            hehe_audio.play();
        }

        //_ball.velocity.x = -2;
    }
    if (_ball.spr_ball.getPosition().y < 0)
    {
        if (_ball.launched) _ball.velocity.y = 2;
    }
    if (_ball.spr_ball.getPosition().y >= 543)
    {
         if (_ball.launched) _ball.velocity.y = -2;
    }

    if(paddle.spr_paddle.getGlobalBounds().intersects(_ball.spr_ball.getGlobalBounds()))
    {
        _ball.velocity.x = 2;

        int random_velocity = std::experimental::randint(-2, 2);
        if (random_velocity == 0) random_velocity = std::experimental::randint(-2, 2);
        else _ball.velocity.y = random_velocity;
    }

    handlePaddleAI();

    if((score_plyr1 > 9 || score_plyr2 > 9) && !endless)
    {
        saveHighscore();
        moveToGameOverScreen = true;
    }
    if (endless && window->pollEvent(evnt) && (score_plyr1 > 0 || score_plyr2 > 0))
    {
        if (evnt.type == evnt.KeyPressed && evnt.key.code == sf::Keyboard::Enter)
        {
            saveHighscore();
            moveToGameOverScreen = true;
        }
    }
    if (!endless && window->pollEvent(evnt) && (score_plyr1 > 0 || score_plyr2 > 0))
    {
        if (evnt.type == evnt.KeyPressed && evnt.key.code == sf::Keyboard::Enter)
        {
            saveHighscore();
            moveToGameOverScreen = true;
        }
    }

    if (option_endless_selected_this == 1)
    {
        rendering_drawText("  ENDLESS ACTIVATED\nPRESS ENTER TO LEAVE", "assets/font.otf", 13.333 * 2, sf::Color(40, 200, 40, 255), 960/2, 485, 1, 1, "center", window);
        endless = true;
    }
    else
    {
        rendering_drawText("ENDLESS DEACTIVATED", "assets/font.otf", 13.333 * 2, sf::Color(40, 40, 40, 255), 960/2, 505, 1, 1, "center", window);
        endless = false;
    }

    if (loseImageTriggered)
    {
        loseImage(window);

        loseImage_alpha -= 5;
        if (loseImage_alpha < 0.1) loseImageTriggered = false;
    }

    if (winImageTriggered)
    {
        winImage(window);

        winImage_alpha -= 5;
        if (winImage_alpha < 0.1) winImageTriggered = false;
    }
}

void ActualGame::handlePaddleAI()
{
        // --- NOTE !! ---
    /*
        This AI blows complete dick. As in, it sucks.
        This is my first time coding in C++ and I'm surprised I made it this far.
        God kill me.
    */

    if (score_plyr1 > 4) difficulty = 1;

    float height = 68;

    if (_ball.yPos > paddle.yPos_right - height && std::experimental::randint(0, difficulty) == 0)
        paddle.yPos_right += paddle.speed_right;
    else if (_ball.yPos < paddle.yPos_right - height && std::experimental::randint(0, difficulty) == 0)
        paddle.yPos_right -= paddle.speed_right;

    if(paddle.spr_paddle_right.getGlobalBounds().intersects(_ball.spr_ball.getGlobalBounds()))
    {
        _ball.velocity.x = -2;

        int random_velocity = std::experimental::randint(-2, 2);
        if (random_velocity == 0) random_velocity = std::experimental::randint(-2, 2);
        else _ball.velocity.y = random_velocity;
    }

}

void ActualGame::saveHighscore()
{
    std::ifstream input;
    input.open("highscorelol.txt");

    if(input.is_open())
    {
        while(!input.eof())
        {
            input >> highscore;
        }
    }

    input.close();

    std::ofstream output("highscorelol.txt");

    if(output.is_open())
    {
        if(score_plyr1 > highscore)
        {
            highscore = score_plyr1;
        }

        output << highscore;
    }

    output.close();
}

void ActualGame::loseImage(sf::RenderWindow *window)
{
    bool playedSound = false;

    loseImage_tex.loadFromFile("assets/sprites/spr_lose.png");
    loseImage_spr.setTexture(loseImage_tex);

    loseImage_spr.setColor(sf::Color(255, 255, 255, loseImage_alpha));

    window->draw(loseImage_spr);
}

void ActualGame::winImage(sf::RenderWindow *window)
{
    bool playedSound = false;

    winImage_tex.loadFromFile("assets/sprites/spr_win.png");
    winImage_spr.setTexture(winImage_tex);

    winImage_spr.setColor(sf::Color(255, 255, 255, winImage_alpha));

    window->draw(winImage_spr);
}

// --------------------- RENDRIN' SHIT --------------------- //

// draw text lmao
void ActualGame::rendering_drawText(const std::string textToDraw, const std::string pathToFont, float fontSize, sf::Color color, float xPos, float yPos, float xScale, float yScale, std::string alignment, sf::RenderWindow* window)
{
    sf::Font fnt;
    fnt.loadFromFile(pathToFont);

    sf::Text txt;

    txt.setString(textToDraw);
    txt.setFont(fnt);
    txt.setCharacterSize(fontSize);
    txt.setFillColor(color);

    txt.setPosition(xPos, yPos);

    if (alignment == "center")
    {
        txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    }

    txt.setScale(xScale, yScale);

    window->draw(txt);
}
