#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Player {
    RectangleShape sprite;
    int speed //�÷��̾��� ���ǵ�
    int speed_max; //���ǵ� �ƽø�
    int score; //����
    int life; //������
    float x, y;      // �÷��̾� ��ǥ
};

struct Boss {
    RectangleShape sprite; //���� �̹��� 
};

// �Ѿ�
struct Bullet {
    RectangleShape sprite;
    int is_fired;         // �߻� ����
};

struct Enemy {
    RectangleShape sprite;
    int speed; //���� �ӵ�
    int life; //���� ������
};

//type�� ���� enum Ȱ��
enum item_type {
    SPEED,      // 0
    DELAY      // 1
};

struct Item {
    RectangleShape sprite;
    int delay;
    int is_presented;      // �������� ������?
    Sound sound;
    long presented_time;
    enum item_type type;
};

struct Textures {
    Texture bg;         // ��� �̹���
    Texture enemy;      // �� �̹���
    Texture gameover;   // ���ӿ��� �̹���
    Texture item_delay;   // ���� ������ �̹���
    Texture item_speed;   // �̼� ������ �̹���
    Texture player;      // �÷��̾� �̹���
    Texture bullet;     // �÷��̾��� �Ѿ� �̹���
    Texture boss;      // ���� �̹���
};

struct SButters {
    SoundBuffer BGM;
    SoundBuffer item_delay;
    SoundBuffer item_speed;
    SoundBuffer rumble;
};

const int ENEMY_NUM = 5; //���� ��
const int BULLET_NUM = 50; //�Ѿ� ����
const int ITEM_NUM = 2; //������ ����
const int W_WIDTH = 1280, W_HEIGHT = 720; //â ũ��
const int GO_WIDTH = 320, GO_HEIGHT = 240;

class Game {
public:
    Game();
    void run();

private:
    //���丮�� ������ �� �ʿ��� �͵�
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
    // ���ο� �Լ��� �߰�
    bool is_collide(const RectangleShape& object1, const RectangleShape& object2);
    void boss1();
    void boss2();

};