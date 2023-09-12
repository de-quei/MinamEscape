#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

struct Textures {
    Texture bg;         // 배경 이미지
};

// 전역 변수
const int W_WIDTH = 1280, W_HEIGHT = 720;   //창의 크기

// 버튼 클래스
class Button {
public:
    Button(float x, float y, float width, float height, const string& text);
    bool isClicked(const Vector2f& mousePos);
    void draw(RenderWindow& window);

private:
    RectangleShape shape;
    Text buttonText;
};

Button::Button(float x, float y, float width, float height, const string& text) {
    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, height));
    shape.setFillColor(Color(128, 128, 128)); // 회색 배경

    // 버튼 텍스트 설정
    buttonText.setString(text);
    buttonText.setPosition(x + 10, y + 10);
    buttonText.setFillColor(Color::Black);
}

bool Button::isClicked(const Vector2f& mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::draw(RenderWindow& window) {
    window.draw(shape);
    window.draw(buttonText);
}

int main() {
    struct Textures t;
    // 왜 나는 상대경로 안돼 ㅠㅠ? 절대경로만 된다 ㅠㅠ...
    t.bg.loadFromFile("./resources/images/start.png");

    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
    window.setFramerateLimit(60);

    Sprite start_bg_sprite;
    start_bg_sprite.setTexture(t.bg);
    start_bg_sprite.setPosition(0, 0);

    // 폰트 설정
    Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // 텍스트 입력 창
    RectangleShape inputBox(Vector2f(400, 60));
    // 창 중앙에 배치
    inputBox.setPosition((W_WIDTH - 870), (W_HEIGHT - 200));
    inputBox.setFillColor(Color(255, 255, 255)); // 회색 (R=128, G=128, B=128)

    // 텍스트
    Text inputText("", font, 35);
    inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 5);
    inputText.setFillColor(Color::Black);

    string inputString;

    //player 
    //RectangleShape player;
    //player.setSize(Vector2f(40, 40));
    //player.setPosition(100, 100);
    //player.setFillColor(Color::Red);
    //int player_speed = 5;

    // 버튼 생성
    Button myButton(500, 590, 200, 50, "Click Me");
    bool isTransitioning = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            // TODO: 한글 입력 안되는 하자 고치기
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
            // 마우스 클릭 이벤트
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                if (!isTransitioning && myButton.isClicked(mousePos)) {
                    // 버튼 클릭 시 화면 전환
                    isTransitioning = true;
                    // 화면 전환 로직 추가
                    // 여기에 화면 전환 로직을 추가하세요.
                    // 예: 다른 화면으로 이동하고 isTransitioning을 false로 다시 설정
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
        window.draw(start_bg_sprite);
        window.draw(inputBox);

        // 사용자가 입력한 텍스트 표시
        inputText.setString(inputString);
        window.draw(inputText);

        // 버튼 그리기
        myButton.draw(window);

        window.display();
    }

    return 0;
}
