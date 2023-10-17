#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

struct Textures {
    Texture bg[6];  // 여섯 개의 배경 이미지
    Texture minseo;
};

struct SBuffer {
    SoundBuffer Alarm;
    SoundBuffer StartBgm;
};

const int W_WIDTH = 1280, W_HEIGHT = 720;

int main() {
    struct Textures t;
    t.minseo.loadFromFile("./resources/images/minseo1.png");

    struct SBuffer sb;
    sb.Alarm.loadFromFile("./resources/sounds/alarm.ogg");
    sb.StartBgm.loadFromFile("./resources/sounds/startBgm.wav");

    // 경로 바꿔줄 것
    for (int i = 0; i < 6; ++i) {
        string imagePath = "./resources/images/start" + to_string(i) + ".png";
        if (!t.bg[i].loadFromFile(imagePath)) {
            cerr << "Failed to load image: " << imagePath << endl;
            return 1;
        }
    }

    // BGM
    Sound Alarm_sound;
    Alarm_sound.setBuffer(sb.Alarm);
    Alarm_sound.setVolume(90);
    Alarm_sound.setLoop(1);  // BGM 무한반복

    Sound startBgm;
    startBgm.setBuffer(sb.StartBgm);
    startBgm.setVolume(90);
    startBgm.setLoop(1);

    startBgm.play();

    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
    window.setFramerateLimit(60);

    Sprite start_bg_sprite;
    start_bg_sprite.setTexture(t.bg[0]);  // 처음 실행 시 start0.png 설정

    int currentBackground = 0; // 현재 배경 인덱스

    // 민서 이미지 스프라이트 설정
    Sprite minseo_sprite;
    minseo_sprite.setTexture(t.minseo);
    minseo_sprite.setOrigin(t.minseo.getSize().x / 2, t.minseo.getSize().y / 2);  // 이미지 중심을 기준으로 설정
    minseo_sprite.setPosition(W_WIDTH - 100, W_HEIGHT / 2);  // 화면 중앙에 배치

    int minseoSpeed = 12;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                // 엔터 키를 누를 때마다 배경 변경
                if (currentBackground < 5) { // 이미지 인덱스가 0부터 5까지
                    currentBackground = (currentBackground + 1) % 6;
                    start_bg_sprite.setTexture(t.bg[currentBackground]);
                }

                // 페이지 전환시 BGM 상태 변경
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

        window.clear(Color::White);
        window.draw(start_bg_sprite);

        if (currentBackground == 3) {
            // 네번째 이미지일 때만 민서 이미지를 그립니다.
            window.draw(minseo_sprite);

            // 민서 이미지를 왼쪽으로 움직이게 합니다.
            float newPositionX = minseo_sprite.getPosition().x - minseoSpeed;
            minseo_sprite.setPosition(newPositionX, minseo_sprite.getPosition().y);
        }

        window.display();
    }

    return 0;
}
