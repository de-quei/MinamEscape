#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

// 전역 변수
const int W_WIDTH = 1280, W_HEIGHT = 720;   //창의 크기

int main() {
    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
    window.setFramerateLimit(60);

    // 폰트 설정
    Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // 텍스트 입력 창
    RectangleShape inputBox(Vector2f(400, 60));
    // 창 중앙에 배치
    inputBox.setPosition((W_WIDTH - inputBox.getSize().x) / 2, (W_HEIGHT - inputBox.getSize().y) / 1.5);
    inputBox.setFillColor(Color(128, 128, 128)); // 회색 (R=128, G=128, B=128)

    // 텍스트
    Text inputText("", font, 35);
    inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 5);
    inputText.setFillColor(Color::Black);

    string inputString;

    //player 
    RectangleShape player;
    player.setSize(Vector2f(40, 40));
    player.setPosition(100, 100);
    player.setFillColor(Color::Red);
    int player_speed = 5;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            // TODO : 한글 입력 안되는 하자 고치기
            else if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !inputString.empty()) {
                        // 백스페이스 처리
                        inputString.pop_back();
                    }
                    else if (event.text.unicode == '\n' || event.text.unicode == '\r') {
                        // 엔터 키 처리 (입력 완료)
                        inputString.clear();
                    }
                    else if (event.text.unicode >= ' ') {
                        // 유효한 문자 입력
                        inputString += static_cast<char>(event.text.unicode);
                    }
                }

            }
        }
        // player move
        /* if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            player.move(-player_speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            player.move(player_speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player.move(0, -player_speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player.move(0, player_speed);
        } */

        window.clear(Color::White);

        // 텍스트 입력 상자 그리기
        window.draw(inputBox);

        // 사용자가 입력한 텍스트 표시
        inputText.setString(inputString);
        window.draw(inputText);

        window.display();
    }

    return 0;
}
