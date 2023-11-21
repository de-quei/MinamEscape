#include "Game.h"
#include "ResourceManager.h"

using namespace sf;
using namespace std;

Game::Game()
    : currentBackground(0), //�ʱ� ����� 0
    girlSpeed(12), //�ҳ��� �ӵ� 12
    isStartButtonClicked(false) //�ʱ� ��ư�� ���� false
    {
    window.create(VideoMode(1280, 720), "MinamEscape");
    window.setFramerateLimit(60); //60������
    start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start0.png"));
    girl_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/minseo1.png"));
    startbtn_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/startbtn.png"));

    startbtn_sprite.setPosition(323, 430); //���۹�ư�� ������


    Alarm_sound.setBuffer(ResourceManager::getInstance().getSound("./resources/sounds/alarm.ogg"));
    Alarm_sound.setVolume(90);
    Alarm_sound.setLoop(true);

    startBgm.setBuffer(ResourceManager::getInstance().getSound("./resources/sounds/startBgm.wav"));
    startBgm.setVolume(90);
    startBgm.setLoop(true);

    startBgm.play();


    Bgm.setBuffer(ResourceManager::getInstance().getSound("./resources/sounds/Bgm2.ogg"));
    Bgm.setVolume(90);
    Bgm.setLoop(true);

    boom.setBuffer(ResourceManager::getInstance().getSound("./resources/sounds/boom.ogg"));
    boom.setVolume(90);
    
    serious.setBuffer(ResourceManager::getInstance().getSound("./resources/sounds/serious.ogg"));
    serious.setVolume(90);
    serious.setLoop(true);
}

void Game::run() {
    while (window.isOpen()) {
        handleInput();
        update();
        render();

    }
}

void Game::handleInput() {
    Event event;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
            if (currentBackground > 0) {
                if (currentBackground < 17) { //����� 17 �̸��̶��
                    currentBackground = (currentBackground + 1) % 18; // +1
                    start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start" + to_string(currentBackground) + ".png"));


                    switch (currentBackground) { //��濡 ��ȣ case

                    case 2:
                        Bgm.play(); //bgm�� �÷����ϰ� �˶��Ҹ��� �����.
                        Alarm_sound.stop();
                        break;
                    case 4:
                        Bgm.stop(); //bgm�� ���߰� boom�� �÷����Ѵ�.
                        boom.play();
                        break;
                    case 5:
                        boom.stop(); //boom�� ���߰� serious�� �÷����Ѵ�.
                        serious.play();
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;
            if (startbtn_sprite.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY)) && !isStartButtonClicked) {
                start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start1.png"));
                currentBackground = 1;
                startBgm.stop();
                Alarm_sound.play();
            }
        }
    }
}

void Game::update() {
    if (currentBackground == 3) { //����� 3�϶� �ҳడ �������� �̵���.
        float newPositionX = girl_sprite.getPosition().x - girlSpeed;
        girl_sprite.setPosition(newPositionX, girl_sprite.getPosition().y);
    }
}

void Game::render() {
    window.clear(Color::White); //�⺻ �Ͼ� ȭ��
    window.draw(start_bg_sprite); //���� ���ȭ���� draw
    if (currentBackground == 0 && !isStartButtonClicked) { //����� 0�̰�, ���۹�ư�� Ŭ������ �ʾҴٸ� ��ư�� draw
        window.draw(startbtn_sprite);
    }
    if (currentBackground == 3) { //����� 3�϶� �ҳ��̹����� draw
        window.draw(girl_sprite);
    }
    window.display();
}
