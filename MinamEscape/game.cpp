#include "Game.h"
#include "ResourceManager.h"

using namespace sf;
using namespace std;

Game::Game()
    : currentBackground(0), //초기 배경은 0
    girlSpeed(12), //소녀의 속도 12
    isStartButtonClicked(false) //초기 버튼의 상태 false
    {
    window.create(VideoMode(1280, 720), "MinamEscape");
    window.setFramerateLimit(60); //60프레임
    start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start0.png"));
    girl_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/minseo1.png"));
    startbtn_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/startbtn.png"));

    startbtn_sprite.setPosition(323, 430); //시작버튼의 포지션


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
                if (currentBackground < 17) { //배경이 17 미만이라면
                    currentBackground = (currentBackground + 1) % 18; // +1
                    start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start" + to_string(currentBackground) + ".png"));


                    switch (currentBackground) { //배경에 번호 case

                    case 2:
                        Bgm.play(); //bgm을 플레이하고 알람소리를 멈춘다.
                        Alarm_sound.stop();
                        break;
                    case 4:
                        Bgm.stop(); //bgm을 멈추고 boom을 플레이한다.
                        boom.play();
                        break;
                    case 5:
                        boom.stop(); //boom을 멈추고 serious를 플레이한다.
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
    if (currentBackground == 3) { //배경이 3일때 소녀가 왼쪽으로 이동함.
        float newPositionX = girl_sprite.getPosition().x - girlSpeed;
        girl_sprite.setPosition(newPositionX, girl_sprite.getPosition().y);
    }
}

void Game::render() {
    window.clear(Color::White); //기본 하얀 화면
    window.draw(start_bg_sprite); //시작 배경화면을 draw
    if (currentBackground == 0 && !isStartButtonClicked) { //배경이 0이고, 시작버튼이 클릭되지 않았다면 버튼을 draw
        window.draw(startbtn_sprite);
    }
    if (currentBackground == 3) { //배경이 3일때 소녀이미지를 draw
        window.draw(girl_sprite);
    }
    window.display();
}
