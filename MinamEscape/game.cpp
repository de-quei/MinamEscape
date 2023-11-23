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
    girl_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/girl1.png"));
    girl1_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/girl2.png"));
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

        if (currentBackground == 17) {
            boss1();
        }
        if (currentBackground == 31) {
            boss2();
        }
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
                    case 17:
                        serious.stop();
                        break;
                    default:
                        break;
                    }
                }
                if (currentBackground >= 18) {
                    
                    currentBackground += 1; // +1
                    start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start" + to_string(currentBackground) + ".png"));
                    switch (currentBackground) { //��濡 ��ȣ case
                    
                    case 18:
                        serious.play();
                        break;
                    case 31:
                        serious.stop();
                        break;
                    default:
                        break;
                    }
                }
                if (currentBackground >= 32) {
                    currentBackground += 1;
                    start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start" + to_string(currentBackground) + ".png"));
                    switch (currentBackground) { //��濡 ��ȣ case

                    case 32:
                        serious.play();
                        break;
                    case 34:
                        serious.stop();
                        Bgm.play();
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

bool Game::is_collide(const RectangleShape& object1, const RectangleShape& object2) {
    return object1.getGlobalBounds().intersects(object2.getGlobalBounds());
}

void Game::boss1() {
    struct Textures t;
    t.bg.loadFromFile("./resources/images/background_1.png");
    t.enemy.loadFromFile("./resources/images/enemy_1.png");
    t.bullet.loadFromFile("./resources/images/playerbullet.png");
    t.gameover.loadFromFile("./resources/images/gameover.png");
    t.item_delay.loadFromFile("./resources/images/item1.png");
    t.item_speed.loadFromFile("./resources/images/item2.png");
    t.player.loadFromFile("./resources/images/player.png");
    t.boss.loadFromFile("./resources/images/boss1.png");

    struct SButters sb;
    sb.BGM.loadFromFile("./resources/sounds/TownTheme.ogg");

    // BGM
    Sound BGM_sound;
    BGM_sound.setBuffer(sb.BGM);
    BGM_sound.setVolume(55);
    BGM_sound.setLoop(1);      // BGM ���ѹݺ�
    BGM_sound.play();

    // text
    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(30);      // ����ũ�� ����
    text.setFillColor(Color(255, 255, 255));
    text.setPosition(0, 0);
    char info[40];

    // ���
    Sprite bg_sprite;
    bg_sprite.setTexture(t.bg);
    bg_sprite.setPosition(0, 0);

    // gameover
    Sprite gameover_sprite;
    gameover_sprite.setTexture(t.gameover);
    gameover_sprite.setPosition(0, 0);

    // �÷��̾�
    struct Player player;
    player.sprite.setTexture(&t.player);
    player.sprite.setPosition(100, 100);
    player.sprite.setSize(Vector2f(178, 540));
    player.x = player.sprite.getPosition().x;
    player.y = player.sprite.getPosition().y;
    player.speed = 6;
    player.speed_max = 15;
    player.score = 0;
    player.life = 5;


    // ��(enemy)
    struct Enemy enemy[ENEMY_NUM];
    Sound enemy_explosion_sound;
    int enemy_score = 100;
    int enemy_respawn_time = 5;
    // enemy �ʱ�ȭ
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].sprite.setTexture(&t.enemy);
        enemy[i].sprite.setSize(Vector2f(120, 120));
        enemy[i].sprite.setScale(-1, 1);      // �¿��Ī
        enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
        enemy[i].life = 1;
        enemy[i].speed = -(rand() % 10 + 1);
    }


    // ����
    struct Boss boss;
    boss.sprite.setTexture(&t.boss);
    boss.sprite.setSize(Vector2f(483, 538));
    boss.sprite.setPosition(900, 100);

    // �Ѿ�
    int bullet_speed = 25;
    int bullet_idx = 0;
    int bullet_delay = 400;      // ������ 0.5��
    int bullet_delay_max = 100;
    Sound bullet_sound;
    bullet_sound.setBuffer(sb.rumble);

    struct Bullet bullet[BULLET_NUM];
    for (int i = 0; i < BULLET_NUM; i++)
    {
        bullet[i].is_fired = 0;
        bullet[i].sprite.setTexture(&t.bullet);
        bullet[i].sprite.setSize(Vector2f(90, 90));
        bullet[i].sprite.setPosition(player.x + 50, player.y - 200);
    }

    // item
    struct Item item[ITEM_NUM];
    item[0].sprite.setTexture(&t.item_speed);
    item[0].delay = 25000;   // 25��
    item[0].type = SPEED;
    item[1].sprite.setTexture(&t.item_delay);
    item[1].delay = 20000;
    item[1].type = DELAY;

    for (int i = 0; i < ITEM_NUM; i++)
    {
        item[i].sprite.setSize(Vector2f(50, 50));
        item[i].is_presented = 0;
        item[i].presented_time = 0;
    }

    srand(time(0));

    long start_time = clock();   // ���� ���۽ð�
    long spent_time;         // ���� ����ð�
    long fired_time = 0;      // �ֱٿ� �߻��� �ð�
    int is_gameover = 0;


    // ������ �������� ������ �ݺ�
    while (window.isOpen())
    {
        spent_time = clock() - start_time;
        player.x = player.sprite.getPosition().x;
        player.y = player.sprite.getPosition().y;

        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // ����(x) ��ư�� ������ Event::Closed(0)
            case Event::Closed:
                window.close();      // ������ �ݴ´�
                break;
                // Ű���带 ������ ��(���� �������� ����)
            case Event::KeyPressed:
            {
                break;
            }
            }
        }


        /* game���� update */
        if ((player.life <= 0))
        {
            is_gameover = 1;
        }

        /* Player update */
        // ����Ű start
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player.sprite.move(-player.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player.sprite.move(player.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player.sprite.move(0, -player.speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player.sprite.move(0, player.speed);
        }   // ����Ű end

        // Player �̵����� ����
        if (player.x < 0)
            player.sprite.setPosition(0, player.y);
        else if (player.x > W_WIDTH - 175)   // 175(�׸��� �ʺ�)
            player.sprite.setPosition(W_WIDTH - 175, player.y);

        if (player.y < 0)
            player.sprite.setPosition(player.x, 0);
        else if (player.y > W_HEIGHT - 105)   // 105(�׸��� ����)
            player.sprite.setPosition(player.x, W_HEIGHT - 105);


        /* Bullet update */
        // �Ѿ� �߻�
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            // �����ð� üũ
            if (spent_time - fired_time > bullet_delay)
            {
                // �Ѿ��� �߻�Ǿ� ���� �ʴٸ�
                if (!bullet[bullet_idx].is_fired)
                {
                    bullet[bullet_idx].sprite.setPosition(player.x + 50, player.y + 15);
                    bullet[bullet_idx].is_fired = 1;
                    bullet_idx++;   // �����Ѿ��� �߻��� �� �ֵ���
                    bullet_idx = bullet_idx % BULLET_NUM;
                    fired_time = spent_time;   // �Ѿ� ����
                }
            }
        }
        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].is_fired)
            {
                bullet[i].sprite.move(bullet_speed, 0);
                if (bullet[i].sprite.getPosition().x > W_WIDTH)
                    bullet[i].is_fired = 0;
            }
        }


        /* Enemy update */
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            // 10�ʸ��� enemy�� ������
            if (spent_time % (1000 * enemy_respawn_time) < 1000 / 60 + 1)
            {
                // ������ �������� ���� ���� ������ ��Ű�ڴ�.
                if (!is_gameover)
                {
                    enemy[i].sprite.setSize(Vector2f(70, 70));
                    enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
                    enemy[i].life = 1;
                    // 10�ʸ��� enemy�� �ӵ�+1
                    enemy[i].speed = -(rand() % 10 + 1 + (spent_time / 1000 / enemy_respawn_time));
                }
            }

            if (enemy[i].life > 0)
            {
                // player, enemy �浹
                if (is_collide(player.sprite, enemy[i].sprite))
                {
                    enemy[i].life -= 1;
                    player.life -= 1;;

                }
                // ���� ���� ���� �����Ϸ��� ����
                else if (enemy[i].sprite.getPosition().x < 0)
                {
                    player.life -= 1;
                    enemy[i].life = 0;
                }

                // �Ѿ˰� enemy�� �浹
                for (int j = 0; j < BULLET_NUM; j++)
                {
                    if (is_collide(bullet[j].sprite, enemy[i].sprite))
                    {
                        if (bullet[j].is_fired)
                        {
                            enemy[i].life -= 1;
                            player.score += enemy_score;

                            bullet[j].is_fired = 0;
                        }
                    }
                }

                enemy[i].sprite.move(enemy[i].speed, 0);
            }
        }



        for (int i = 0; i < ITEM_NUM; i++)
        {
            if (!item[i].is_presented)
            {
                if (spent_time - item[i].presented_time > item[i].delay)
                {
                    item[i].sprite.setPosition((rand() % W_WIDTH) * 0.8, (rand() % W_HEIGHT) * 0.8);
                    item[i].is_presented = 1;
                }
            }

            if (item[i].is_presented)
            {
                // ������ ȹ��� ȿ���� ��� �������� �������
                if (is_collide(player.sprite, item[i].sprite))
                {
                    switch (item[i].type)
                    {
                    case SPEED:   // player �̵��ӵ�
                        player.speed += 2;

                        if (player.speed > player.speed_max)
                            player.speed = player.speed_max;
                        break;
                    case DELAY:   // player ���ݼӵ�
                        bullet_delay -= 100;

                        if (bullet_delay < bullet_delay_max)
                            bullet_delay = bullet_delay_max;
                        break;
                    }
                    item[i].is_presented = 0;
                    item[i].presented_time = spent_time;
                }
            }
        }


        sprintf(info, "life:%d score:%d time:%d"
            , player.life, player.score, spent_time / 1000);
        text.setString(info);

        window.clear(Color::Black);
        window.draw(bg_sprite);

        // draw�� ���߿� ȣ���Ҽ��� �켱������ ������
        for (int i = 0; i < ENEMY_NUM; i++)
            if (enemy[i].life > 0)
                window.draw(enemy[i].sprite);
        for (int i = 0; i < ITEM_NUM; i++)
            if (item[i].is_presented)
                window.draw(item[i].sprite);

        window.draw(player.sprite);
        window.draw(boss.sprite);
        window.draw(text);
        for (int i = 0; i < BULLET_NUM; i++)
            if (bullet[i].is_fired)
                window.draw(bullet[i].sprite);

        if (is_gameover)
        {
            window.draw(gameover_sprite);
        }

        // ������ ������� �ʾҰ�, Ư�� ������ �����ϸ� ����� ����
        if (!is_gameover && player.score >= 2500) {
            currentBackground = 18;
            start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start18.png"));
            window.draw(start_bg_sprite);
            break;
        }
        window.display();

    }
}

void Game::boss2() {
    struct Textures t;
    t.bg.loadFromFile("./resources/images/background.png");
    t.enemy.loadFromFile("./resources/images/enemy.png");
    t.bullet.loadFromFile("./resources/images/playerbullet.png");
    t.item_delay.loadFromFile("./resources/images/item1.png");
    t.item_speed.loadFromFile("./resources/images/item2.png");
    t.player.loadFromFile("./resources/images/player.png");
    t.boss.loadFromFile("./resources/images/boss.png");

    struct SButters sb;
    sb.BGM.loadFromFile("./resources/sounds/TownTheme.ogg");

    // BGM
    Sound BGM_sound;
    BGM_sound.setBuffer(sb.BGM);
    BGM_sound.setVolume(55);
    BGM_sound.setLoop(1);      // BGM ���ѹݺ�
    BGM_sound.play();

    // text
    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(30);      // ����ũ�� ����
    text.setFillColor(Color(255, 255, 255));
    text.setPosition(0, 0);
    char info[40];

    // ���
    Sprite bg_sprite;
    bg_sprite.setTexture(t.bg);
    bg_sprite.setPosition(0, 0);

    // gameover
    Sprite gameover_sprite;
    gameover_sprite.setTexture(t.gameover);
    gameover_sprite.setPosition(0, 0);

    // �÷��̾�
    struct Player player;
    player.sprite.setTexture(&t.player);
    player.sprite.setPosition(100, 100);
    player.sprite.setSize(Vector2f(178, 540));
    player.x = player.sprite.getPosition().x;
    player.y = player.sprite.getPosition().y;
    player.speed = 6;
    player.speed_max = 15;
    player.score = 0;
    player.life = 8;


    // ��(enemy)
    struct Enemy enemy[ENEMY_NUM];
    Sound enemy_explosion_sound;
    enemy_explosion_sound.setBuffer(sb.rumble);
    int enemy_score = 100;
    int enemy_respawn_time = 5;
    // enemy �ʱ�ȭ
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].sprite.setTexture(&t.enemy);
        enemy[i].sprite.setSize(Vector2f(120, 120));
        enemy[i].sprite.setScale(-1, 1);      // �¿��Ī
        enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
        enemy[i].life = 1;
        enemy[i].speed = -(rand() % 10 + 4);
    }


    // ����
    struct Boss boss;
    boss.sprite.setTexture(&t.boss);
    boss.sprite.setSize(Vector2f(678, 368));
    boss.sprite.setPosition(670, 100);

    // �Ѿ�
    int bullet_speed = 25;
    int bullet_idx = 0;
    int bullet_delay = 400;      // ������ 0.5��
    int bullet_delay_max = 100;
    Sound bullet_sound;

    struct Bullet bullet[BULLET_NUM];
    for (int i = 0; i < BULLET_NUM; i++)
    {
        bullet[i].is_fired = 0;
        bullet[i].sprite.setTexture(&t.bullet);
        bullet[i].sprite.setSize(Vector2f(90, 90));
        bullet[i].sprite.setPosition(player.x + 50, player.y - 200);
    }

    // item
    struct Item item[ITEM_NUM];
    item[0].sprite.setTexture(&t.item_speed);
    item[0].delay = 25000;   // 25��
    item[0].type = SPEED;
    item[1].sprite.setTexture(&t.item_delay);
    item[1].delay = 20000;
    item[1].type = DELAY;

    for (int i = 0; i < ITEM_NUM; i++)
    {
        item[i].sprite.setSize(Vector2f(50, 50));
        item[i].is_presented = 0;
        item[i].presented_time = 0;
    }

    srand(time(0));

    long start_time = clock();   // ���� ���۽ð�
    long spent_time;         // ���� ����ð�
    long fired_time = 0;      // �ֱٿ� �߻��� �ð�
    int is_gameover = 0;


    // ������ �������� ������ �ݺ�
    while (window.isOpen())
    {
        spent_time = clock() - start_time;
        player.x = player.sprite.getPosition().x;
        player.y = player.sprite.getPosition().y;

        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // ����(x) ��ư�� ������ Event::Closed(0)
            case Event::Closed:
                window.close();      // ������ �ݴ´�
                break;
                // Ű���带 ������ ��(���� �������� ����)
            case Event::KeyPressed:
            {
                break;
            }
            }
        }

        /* game���� update */
        if ((player.life <= 0))
        {
            is_gameover = 1;
        }

        /* Player update */
        // ����Ű start
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        {
            player.sprite.move(-player.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        {
            player.sprite.move(player.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
        {
            player.sprite.move(0, -player.speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
        {
            player.sprite.move(0, player.speed);
        }   // ����Ű end

        // Player �̵����� ����
        if (player.x < 0)
            player.sprite.setPosition(0, player.y);
        else if (player.x > W_WIDTH - 175)   // 175(�׸��� �ʺ�)
            player.sprite.setPosition(W_WIDTH - 175, player.y);

        if (player.y < 0)
            player.sprite.setPosition(player.x, 0);
        else if (player.y > W_HEIGHT - 105)   // 105(�׸��� ����)
            player.sprite.setPosition(player.x, W_HEIGHT - 105);


        /* Bullet update */
        // �Ѿ� �߻�
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            // �����ð� üũ
            if (spent_time - fired_time > bullet_delay)
            {
                // �Ѿ��� �߻�Ǿ� ���� �ʴٸ�
                if (!bullet[bullet_idx].is_fired)
                {
                    bullet[bullet_idx].sprite.setPosition(player.x + 50, player.y + 15);
                    bullet[bullet_idx].is_fired = 1;
                    bullet_idx++;   // �����Ѿ��� �߻��� �� �ֵ���
                    bullet_idx = bullet_idx % BULLET_NUM;
                    fired_time = spent_time;   // �Ѿ� ����
                }
            }
        }
        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].is_fired)
            {
                bullet[i].sprite.move(bullet_speed, 0);
                if (bullet[i].sprite.getPosition().x > W_WIDTH)
                    bullet[i].is_fired = 0;
            }
        }


        /* Enemy update */
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            // 10�ʸ��� enemy�� ������
            if (spent_time % (1000 * enemy_respawn_time) < 1000 / 60 + 1)
            {
                // ������ �������� ���� ���� ������ ��Ű�ڴ�.
                if (!is_gameover)
                {
                    enemy[i].sprite.setSize(Vector2f(70, 70));
                    enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
                    enemy[i].life = 1;
                    // 10�ʸ��� enemy�� �ӵ�+1
                    enemy[i].speed = -(rand() % 10 + 1 + (spent_time / 1000 / enemy_respawn_time));
                }
            }

            if (enemy[i].life > 0)
            {
                // player, enemy �浹
                if (is_collide(player.sprite, enemy[i].sprite))
                {
                    enemy[i].life -= 1;
                    player.life -= 1;;

                }
                // ���� ���� ���� �����Ϸ��� ����
                else if (enemy[i].sprite.getPosition().x < 0)
                {
                    player.life -= 1;
                    enemy[i].life = 0;
                }

                // �Ѿ˰� enemy�� �浹
                for (int j = 0; j < BULLET_NUM; j++)
                {
                    if (is_collide(bullet[j].sprite, enemy[i].sprite))
                    {
                        if (bullet[j].is_fired)
                        {
                            enemy[i].life -= 1;
                            player.score += enemy_score;

                            bullet[j].is_fired = 0;
                        }
                    }
                }

                enemy[i].sprite.move(enemy[i].speed, 0);
            }
        }



        for (int i = 0; i < ITEM_NUM; i++)
        {
            if (!item[i].is_presented)
            {
                if (spent_time - item[i].presented_time > item[i].delay)
                {
                    item[i].sprite.setPosition((rand() % W_WIDTH) * 0.8, (rand() % W_HEIGHT) * 0.8);
                    item[i].is_presented = 1;
                }
            }

            if (item[i].is_presented)
            {
                // ������ ȹ��� ȿ���� ��� �������� �������
                if (is_collide(player.sprite, item[i].sprite))
                {
                    switch (item[i].type)
                    {
                    case SPEED:   // player �̵��ӵ�
                        player.speed += 2;

                        if (player.speed > player.speed_max)
                            player.speed = player.speed_max;
                        break;
                    case DELAY:   // player ���ݼӵ�
                        bullet_delay -= 100;

                        if (bullet_delay < bullet_delay_max)
                            bullet_delay = bullet_delay_max;
                        break;
                    }
                    item[i].is_presented = 0;
                    item[i].presented_time = spent_time;
                    item[i].sound.play();
                }
            }
        }


        sprintf(info, "life:%d score:%d time:%d"
            , player.life, player.score, spent_time / 1000);
        text.setString(info);

        window.clear(Color::Black);
        window.draw(bg_sprite);

        // draw�� ���߿� ȣ���Ҽ��� �켱������ ������
        for (int i = 0; i < ENEMY_NUM; i++)
            if (enemy[i].life > 0)
                window.draw(enemy[i].sprite);
        for (int i = 0; i < ITEM_NUM; i++)
            if (item[i].is_presented)
                window.draw(item[i].sprite);

        window.draw(player.sprite);
        window.draw(boss.sprite);
        window.draw(text);
        for (int i = 0; i < BULLET_NUM; i++)
            if (bullet[i].is_fired)
                window.draw(bullet[i].sprite);

        if (is_gameover)
        {
            window.draw(gameover_sprite);
        }

        // ������ ������� �ʾҰ�, Ư�� ������ �����ϸ� ����� ����
        if (!is_gameover && player.score >= 4000) {
            currentBackground = 32;
            start_bg_sprite.setTexture(ResourceManager::getInstance().getTexture("./resources/images/start32.png"));
            window.draw(start_bg_sprite);
            break;
        }
        window.display();

    }
}

void Game::update() {
    if (currentBackground == 3) { //����� 3�϶� �ҳడ �������� �̵���.
        float newPositionX = girl_sprite.getPosition().x - girlSpeed;
        girl_sprite.setPosition(newPositionX, girl_sprite.getPosition().y);
    }
    if (currentBackground == 44) { //����� 3�϶� �ҳడ �������� �̵���.
        float newPositionX = girl1_sprite.getPosition().x - girlSpeed;
        girl1_sprite.setPosition(newPositionX, girl1_sprite.getPosition().y);
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
    if (currentBackground == 44) { //����� 3�϶� �ҳ��̹����� draw
        window.draw(girl1_sprite);
    }
    window.display();
}
