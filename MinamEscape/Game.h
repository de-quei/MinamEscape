#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Game {
public:
    Game();
    void run();

private:
    RenderWindow window;
    Sprite start_bg_sprite;
    Sprite girl_sprite;
    Sprite startbtn_sprite;
    int currentBackground;
    int girlSpeed;
    bool isStartButtonClicked;
    Sound Alarm_sound;
    Sound startBgm;
    Sound Bgm;
    Sound boom;
    Sound serious;

    void handleInput();
    void update();
    void render();
};