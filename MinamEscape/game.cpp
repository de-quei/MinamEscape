#include <SFML/Graphics.hpp> // SFML 라이브러리의 그래픽 모듈 헤더 파일을 포함합니다.
#include <stdlib.h>
#include <time.h>

using namespace sf; // SFML의 네임스페이스를 사용합니다.

int main(void) {
    //window 창
    RenderWindow window(VideoMode(1280, 720), "게임화면");
    window.setFramerateLimit(60);

    srand(time(0));

    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color(255, 255, 255));
    text.setPosition(0, 0);
    text.setString("score");

    //player
    RectangleShape player;
    player.setSize(Vector2f(40, 40));
    player.setPosition(100, 100);
    int player_speed = 5;
    int player_score = 0;

    //enemy
    RectangleShape enemy[5];
    int enemy_life[5];
    int enemy_score = 100;

    for (int i = 0; i < 5; i++) {
        enemy[i].setSize(Vector2f(60, 60));
        enemy[i].setFillColor(Color::Yellow);
        enemy_life[i] = 1;
        enemy[i].setPosition(rand() % 600 + 600, rand() % 720);
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed: { //space 한 번 눌렀을때만 감지
                if (event.key.code == Keyboard::Space)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        enemy[i].setSize(Vector2f(70, 70));
                        enemy[i].setFillColor(Color::Yellow);
                        enemy_life[i] = 1;
                        enemy[i].setPosition(rand() % 300 + 300, rand() % 480);
                    }
                }
                break;
            }
            }
        }

        //키보드 동작
        if (Keyboard::isKeyPressed(Keyboard::Left))
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
        }

        //player와 enemy가 충돌하면 life를 -1 한다.
        for (int i = 0; i < 5; i++) {
            if (enemy_life[i] > 0) {
                if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
                {
                    printf("enemy[%d]와 충돌!\n", i);
                    enemy_life[i] -= 1;
                    player_score += enemy_score;
                }
            }
        }

        text.setString("score: " + std::to_string(player_score));

        window.clear(Color::Black);

        //enemy_life가 0보다 클때만 enemy를 그린다.
        for (int i = 0; i < 5; i++) {
            if (enemy_life[i] > 0) {
                window.draw(enemy[i]);
            }
        }
        window.draw(player);
        window.draw(text);

        window.display();
    }

    return 0;
}