#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

class Object {
public:
    int width_;
    int height_;
    RectangleShape sprite_;
    Texture texture;

    Texture* setImage(string path) {
        if (texture.loadFromFile(path)) return &texture;
    }

    void setPosition(float x, float y) {
        sprite_.setPosition(x, y);
    }

    void setSize(Vector2f size) {
        sprite_.setSize(size);
    }

    void setTexture(Texture* tex) {
        sprite_.setTexture(tex);
    }

    bool contains(int x, int y) {
        return sprite_.getGlobalBounds().contains(x, y);
    }
};

struct Textures {
    Texture bg[15];
    Texture minseo;
    Texture startbtn;
};

struct SBuffer {
    SoundBuffer Alarm;
    SoundBuffer StartBgm;
};

const int W_WIDTH = 1280, W_HEIGHT = 720;

int main() {
    struct Textures t;
    t.minseo.loadFromFile("./resources/images/minseo1.png");
    t.startbtn.loadFromFile("./resources/images/startbtn.png");

    struct SBuffer sb;
    sb.Alarm.loadFromFile("./resources/sounds/alarm.ogg");
    sb.StartBgm.loadFromFile("./resources/sounds/startBgm.wav");

    for (int i = 0; i < 15; ++i) {
        string imagePath = "./resources/images/start" + to_string(i) + ".png";
        if (!t.bg[i].loadFromFile(imagePath)) {
            cerr << "Failed to load image: " << imagePath << endl;
            return 1;
        }
    }

    Sound Alarm_sound;
    Alarm_sound.setBuffer(sb.Alarm);
    Alarm_sound.setVolume(90);
    Alarm_sound.setLoop(1);

    Sound startBgm;
    startBgm.setBuffer(sb.StartBgm);
    startBgm.setVolume(90);
    startBgm.setLoop(1);

    startBgm.play();

    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
    window.setFramerateLimit(60);

    Sprite start_bg_sprite;
    start_bg_sprite.setTexture(t.bg[0]);

    int currentBackground = 0;

    Sprite minseo_sprite;
    minseo_sprite.setTexture(t.minseo);
    minseo_sprite.setOrigin(t.minseo.getSize().x / 2, t.minseo.getSize().y / 2);
    minseo_sprite.setPosition(W_WIDTH - 100, W_HEIGHT / 2);

    int minseoSpeed = 12;

    Sprite startbtn_sprite;
    startbtn_sprite.setTexture(t.startbtn);
    startbtn_sprite.setPosition(322, 447);

    Object startBtn;
    startBtn.setSize(Vector2f(581, 208));
    startBtn.setTexture(&t.startbtn);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                if (currentBackground < 14) {
                    currentBackground = (currentBackground + 1) % 15;
                    start_bg_sprite.setTexture(t.bg[currentBackground]);

                    switch (currentBackground) {
                    case 1:
                        startBgm.stop();
                        Alarm_sound.play();
                        break;
                    case 2:
                        Alarm_sound.stop();
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        window.clear(Color::White);
        window.draw(start_bg_sprite);

        if (currentBackground == 0) 
            window.draw(startbtn_sprite);

        if (currentBackground == 3) {
            window.draw(minseo_sprite);

            float newPositionX = minseo_sprite.getPosition().x - minseoSpeed;
            minseo_sprite.setPosition(newPositionX, minseo_sprite.getPosition().y);
        }

        window.display();
    }

    return 0;
}
