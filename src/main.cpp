#include "game.h"
#include <experimental/random>
#include <time.h>

int main()
{
    //Init the music
    sf::Music music;

    //play the theme song!!
    if(music.getStatus() != sf::Music::Playing)
    {
        music.openFromFile("assets/audio/theme.wav");

        music.setVolume(25);
        music.setLoop(true);

        music.play();
    }


    //Init game and its states
    MainGame mainGame(60);
    mainGame.run();

    return 0;
}
