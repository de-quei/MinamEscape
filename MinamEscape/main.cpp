#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

struct Textures {
    Texture bg[18];
    Texture minseo;
    Texture startbtn;
};

struct SBuffer {
    SoundBuffer Alarm;
    SoundBuffer StartBgm;
    SoundBuffer Bgm2;
    SoundBuffer boom;
    SoundBuffer serious;
};

const int W_WIDTH = 1280, W_HEIGHT = 720;

int main() {
    struct Textures t;
    t.minseo.loadFromFile("./resources/images/minseo1.png");
    t.startbtn.loadFromFile("./resources/images/startbtn.png");

    struct SBuffer sb;
    sb.Alarm.loadFromFile("./resources/sounds/alarm.ogg");
    sb.StartBgm.loadFromFile("./resources/sounds/startBgm.wav");
    sb.Bgm2.loadFromFile("./resources/sounds/Bgm2.ogg");
    sb.boom.loadFromFile("./resources/sounds/boom.ogg");
    sb.serious.loadFromFile("./resources/sounds/serious.ogg");

    for (int i = 0; i < 18; ++i) {
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

    Sound Bgm;
    Bgm.setBuffer(sb.Bgm2);
    Bgm.setVolume(90);
    Bgm.setLoop(1);

    Sound boom;
    boom.setBuffer(sb.boom);
    boom.setVolume(90);

    Sound serious;
    serious.setBuffer(sb.serious);
    serious.setVolume(90);
    serious.setLoop(1);

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

    bool isStartButtonClicked = false; // 시작 버튼이 클릭되었는지 여부를 저장하는 변수

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                if (currentBackground > 0) {
                    if (currentBackground < 17) {
                        currentBackground = (currentBackground + 1) % 18;
                        start_bg_sprite.setTexture(t.bg[currentBackground]);

                        switch (currentBackground) {
                        case 2:
                            Bgm.play();
                            Alarm_sound.stop();
                            break;
                        case 4:
                            Bgm.stop();
                            boom.play();
                            break;
                        case 5 : 
                            boom.stop();
                            serious.play();
                        default:
                            break;
                        }
                    }
                }
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                if (startbtn_sprite.getGlobalBounds().contains(mouseX, mouseY) && !isStartButtonClicked) {
                    start_bg_sprite.setTexture(t.bg[1]);
                    currentBackground = 1; 
                    startBgm.stop();
                    Alarm_sound.play();
                }
            }

        }

        window.clear(Color::White);
        window.draw(start_bg_sprite);

        if (currentBackground == 0 && !isStartButtonClicked)
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
