#include "../game.h"
#include "main_menu.h"

MainMenu::MainMenu() {
};

MainMenu::~MainMenu() {};

void MainMenu::initStuff(sf::RenderWindow* window, float _dt)
{
    // draw logo and add cool lil animation using cosine
    logo_tex.loadFromFile("assets/sprites/spr_logo.png");
    logo_spr.setTexture(logo_tex);

    float value = (cos(_dt * 10) * 1.25);
    float intensity = 4.5;

    logo_spr.setPosition(490 - 245, 75 + (value * intensity));
    //logo_spr.setOrigin(logo_spr.getGlobalBounds().width / 2, logo_spr.getGlobalBounds().height / 2);
    logo_spr.setScale(2, 2);

    window->draw(logo_spr);

    //handle text anims (using the same cosine value divided by 6)

    switch (option_selected)
    {
        case 0:
            text_scale_value_play = 1 + (value / 6);
            text_scale_value_quit = 1;
        break;

        case 1:
            text_scale_value_play = 1;
            text_scale_value_quit = 1 + (value / 6);
        break;
    }

    //handle text rendering

    rendering_drawText("PLAY!!", "assets/font.otf", 13.333 * 3, txtColorPlay, WINDOW_WIDTH / 2, 320, text_scale_value_play, text_scale_value_play, "center", window);

    if (option_selected_endless == 0) rendering_drawText("ENDLESS: OFF", "assets/font.otf", 13.333 * 2, sf::Color(40, 40, 40, 255), WINDOW_WIDTH / 2, 280, 1, 1, "center", window);
    else if (option_selected_endless == 1) rendering_drawText("ENDLESS: ON", "assets/font.otf", 13.333 * 2, sf::Color(40, 40, 40, 255), WINDOW_WIDTH / 2, 280, 1, 1, "center", window);

    rendering_drawText("QUIT!!", "assets/font.otf", 13.333 * 2, txtColorQuit, WINDOW_WIDTH / 2, 375, text_scale_value_quit, text_scale_value_quit, "center", window);

    rendering_drawText("made by hatoving lmao", "assets/font.otf", 13.333 * 1.5, sf::Color(40, 40, 40, 255), 10, 515, 1, 1, "", window);
    rendering_drawText("v0.1", "assets/font.otf", 13.333 * 1.5, sf::Color(40, 40, 40, 255), 10, 10, 1, 1, "", window);
}

void MainMenu::handleOptions(sf::RenderWindow* window, sf::Event evnt)
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            option_selected--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            option_selected++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            option_selected_endless--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            option_selected_endless++;
        }

    if (window->pollEvent(evnt))
    {
        if (evnt.type == evnt.KeyPressed && evnt.key.code == sf::Keyboard::Enter && option_selected == 0)
            triggerGame = true;
        else if (evnt.type == evnt.KeyPressed && evnt.key.code == sf::Keyboard::Enter && option_selected == 1)
            window->close();
    }

    if (option_selected < 0) option_selected = 0;
    else if (option_selected > 1) option_selected = 1;

    if (option_selected_endless < 0) option_selected_endless = 0;
    else if (option_selected_endless > 1) option_selected_endless = 1;

    switch (option_selected)
    {
        case 0:
            txtColorPlay = sf::Color::Red;
            txtColorQuit = sf::Color::White;
        break;

        case 1:
            txtColorPlay = sf::Color::White;
            txtColorQuit = sf::Color::Red;
        break;
    }

    //std::cout << std::to_string(option_selected) << std::endl;
}

// --------------------- RENDRIN' SHIT --------------------- //

// draw text lmao
void MainMenu::rendering_drawText(const std::string textToDraw, const std::string pathToFont, float fontSize, sf::Color color, float xPos, float yPos, float xScale, float yScale, std::string alignment, sf::RenderWindow* window)
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
