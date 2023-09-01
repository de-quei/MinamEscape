#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;


// 전역 변수
const int W_WIDTH = 1280, W_HEIGHT = 720;   //창의 크기

int main() {
	//윈도우창 생성
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
	window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
	return 0;
}