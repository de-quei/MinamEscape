#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

struct Textures {
    Texture bg[6];  // 여섯 개의 배경 이미지
};

const int W_WIDTH = 1280, W_HEIGHT = 720;

int main() {
    struct Textures t;
    // 경로 바꿔줄 것
    for (int i = 0; i < 6; ++i) {
        string imagePath = "./resources/images/start" + to_string(i) + ".png";
        if (!t.bg[i].loadFromFile(imagePath)) {
            cerr << "Failed to load image: " << imagePath << endl;
            return 1;
        }
    }

    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
    window.setFramerateLimit(60);

    Sprite start_bg_sprite;
    start_bg_sprite.setTexture(t.bg[0]); // 처음 실행 시 start0.png 설정

    int currentBackground = 0; // 현재 배경 인덱스

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
            }
        }

        window.clear(Color::White);
        window.draw(start_bg_sprite);
        window.display();
    }

    return 0;
}
