#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

struct Textures {
    Texture bg;  // 배경 이미지
};

// 전역 변수
const int W_WIDTH = 1280, W_HEIGHT = 720;   //창의 크기

int main() {
    struct Textures t;
    // 경로 바꿔줄것
    t.bg.loadFromFile("C:/Users/User/source/repos/de-quei/MinamEscape/MinamEscape/resources/images/start.png");

    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
    window.setFramerateLimit(60);

    Sprite start_bg_sprite;
    start_bg_sprite.setTexture(t.bg);
    start_bg_sprite.setPosition(0, 0);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White);

        window.draw(start_bg_sprite);

        window.display();
    }

    return 0;
}