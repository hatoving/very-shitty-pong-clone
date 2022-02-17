#include "game.h"


MainGame::MainGame(int framerate) {
    //Set the framerate limit cuz why not
    std::cout << "INFO: Setting framerate to " << framerate << "..." << std::endl;
    window.setFramerateLimit(framerate);

    //Set the game state too
    std::cout << "INFO: Setting background color... " << std::endl;
    _cs = _CurrentState::TITLE;
    std::cout << "INFO: _CurrentState is " << std::to_string(_cs) << std::endl;

    srand(120);
};
MainGame::~MainGame() {};

void MainGame::run()
{
    std::cout << "INFO: Creating window..." << std::endl;
    std::cout << "INFO: Window size is " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;

    //Create the window lmao
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "very shitty pong clone", sf::Style::Close);
    gameLoop();
}

void MainGame::gameLoop()
{
    while(window.isOpen())
    {
        //We wanna keep track of how much time has passed + handle events
        handleEvents();
        updateDT();

        window.clear(sf::Color(20, 20, 20, 255));
        // -- NOTE TO SELF: -- EVERYTHING THAT NEEDS TO BE DRAWN NEEDS TO HAPPEN IN BETWEEN THESE LINES!!

        switch (_cs)
        {
            //If it we are at the title...
            case _CurrentState::TITLE:
                //Then draw handle the menu...
                _mainMenu.initStuff(&window, _dt);
                _mainMenu.handleOptions(&window, event);

                loadHighscore();
                rendering_drawText("Your best: " + std::to_string(highscore), "assets/font.otf", 13.333 * 2, sf::Color(40, 40, 40, 255), 960/2, 455, "center");

                //And check if we selected "PLAY!!"...
                if (_mainMenu.triggerGame)
                {
                    _cs = _CurrentState::GAME;
                    std::cout << "INFO: _CurrentState is " << std::to_string(_cs) << std::endl;
                }
            break;

            //If we're at the actual game itself...
            case _CurrentState::GAME:
                //Then draw the line in the middle and its objects, such as the two paddles, the ball, etc.
                if (!actualGame.moveToGameOverScreen) actualGame.drawAndUpdateStuff(&window, dtClock, _dt, _mainMenu.option_selected_endless, event);
                else
                {
                    //loadHighscore();
                    actualGame.score_plyr1 = 0;
                    actualGame.score_plyr2 = 0;
                    actualGame.moveToGameOverScreen = false;
                    _mainMenu.triggerGame = false;
                    _cs = _CurrentState::TITLE;
                }
            break;
        }

            //set a fade animation at the start

    sf::RectangleShape rect;

    if (fadeAlpha < 0) rect.setFillColor(sf::Color(0, 0, 0, 0));
    else
    {
        fadeAlpha -= 2;
        rect.setFillColor(sf::Color(0, 0, 0, fadeAlpha));
    }

    sf::Vector2f rect_size(960, 544);
    rect.setSize(rect_size);

    rect.setPosition(0, 0);
    window.draw(rect);

        window.display();
    }
}

void MainGame::handleEvents()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void MainGame::updateDT()
{
    _dt = dtClock.getElapsedTime().asSeconds();
    //std::cout << _dt << std::endl;
}

void MainGame::loadHighscore()
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
}

// --------------------- RENDRIN' SHIT --------------------- //

// draw text lmao
void MainGame::rendering_drawText(const std::string textToDraw, const std::string pathToFont, float fontSize, sf::Color color, float xPos, float yPos, std::string alignment)
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

    window.draw(txt);
}
