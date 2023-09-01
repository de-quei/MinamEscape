#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;


// ���� ����
const int W_WIDTH = 1280, W_HEIGHT = 720;   //â�� ũ��

int main() {
	//������â ����
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "MinamEscape");
	window.setFramerateLimit(60);

    //player 
    RectangleShape player;
    player.setSize(Vector2f(40, 40));
    player.setPosition(100, 100);
    player.setFillColor(Color::Red);
    int player_speed = 5;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(Color::Black);
        window.draw(player);
        window.display();
    }
	return 0;
}