#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Player {
    RectangleShape sprite;
    int speed;
    int speed_max;
    int score;
    int life;
    float x, y;      // 플레이어 좌표
};

struct Boss {
    RectangleShape sprite;
};

// 총알
struct Bullet {
    RectangleShape sprite;
    int is_fired;         // 발사 여부
};

struct Enemy {
    RectangleShape sprite;
    int speed;
    int life;
};

enum item_type {
    SPEED,      // 0
    DELAY      // 1
};

struct Item {
    RectangleShape sprite;
    int delay;
    int is_presented;      // 아이템이 떳는지?
    Sound sound;
    long presented_time;
    enum item_type type;
};

struct Textures {
    Texture bg;         // 배경 이미지
    Texture enemy;      // 적 이미지
    Texture gameover;   // 게임오버 이미지
    Texture item_delay;   // 공속 아이템 이미지
    Texture item_speed;   // 이속 아이템 이미지
    Texture player;      // 플레이어 이미지
    Texture bullet;     // 플레이어의 총알 이미지
    Texture boss;      // 보스 이미지
};

struct SButters {
    SoundBuffer BGM;
    SoundBuffer item_delay;
    SoundBuffer item_speed;
    SoundBuffer rumble;
};

const int ENEMY_NUM = 5;
const int BULLET_NUM = 50;
const int ITEM_NUM = 2;
const int W_WIDTH = 1280, W_HEIGHT = 720;
const int GO_WIDTH = 320, GO_HEIGHT = 240;

class Game {
public:
    Game();
    void run();

private:
    RenderWindow window;
    Sprite start_bg_sprite;
    Sprite girl_sprite;
    Sprite girl1_sprite;
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
    // 새로운 함수들 추가
    bool is_collide(const RectangleShape& object1, const RectangleShape& object2);
    void boss1();
    void boss2();

};