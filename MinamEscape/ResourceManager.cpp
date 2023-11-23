#include "ResourceManager.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

ResourceManager::ResourceManager() {

    // ���ҽ� �ʱ�ȭ �ڵ�
    for (int i = 0; i < 50; ++i) {
        string imagePath = "./resources/images/start" + to_string(i) + ".png";
        Texture texture;
        if (!texture.loadFromFile(imagePath)) {
            cerr << "Failed to load image: " << imagePath << endl;
        }
        textures[to_string(i)] = texture;
    }

    // ���� �ʱ�ȭ �ڵ�
    if (!sounds["alarm"].loadFromFile("./resources/sounds/alarm.ogg")) {
        cerr << "Failed to load sound: alarm.ogg" << endl;
    }
    if (!sounds["startBgm"].loadFromFile("./resources/sounds/startBgm.wav")) {
        cerr << "Failed to load sound: startBgm.wav" << endl;
    }
    if (!sounds["Bgm2"].loadFromFile("./resources/sounds/Bgm2.ogg")) {
        cerr << "Failed to load sound: Bgm2.ogg" << endl;
    }
    if (!sounds["boom"].loadFromFile("./resources/sounds/boom.ogg")) {
        cerr << "Failed to load sound: boom.ogg" << endl;
    }
    if (!sounds["serious"].loadFromFile("./resources/sounds/serious.ogg")) {
        cerr << "Failed to load sound: serious.ogg" << endl;
    }
}

// ���� ��� ���� �ʱ�ȭ
ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

Texture& ResourceManager::getTexture(const string& filename) {
    auto it = textures.find(filename); // �ؽ�ó �ʿ��� ��� �˻�

    if (it != textures.end()) {
        // ��Ҹ� ã���� �� ��ȯ
        return it->second;
    }
    else {
        // ��Ҹ� ã�� ������ �� �ε� �� ����
        Texture newTexture;
        if (newTexture.loadFromFile(filename)) {
            textures[filename] = newTexture;
            return textures[filename];
        }
        else {
            // ���� ó�� ���� (��: �⺻ �ؽ�ó�� ��ȯ�ϰų� ���� ó��)
            throw runtime_error("Failed to load texture: " + filename);
        }
    }
}

SoundBuffer& ResourceManager::getSound(const string& filename) {
    auto it = sounds.find(filename); // ���� ���� �ʿ��� ��� �˻�

    if (it != sounds.end()) {
        // ��Ҹ� ã���� �� ��ȯ
        return it->second;
    }
    else {
        // ��Ҹ� ã�� ������ �� �ε� �� ����
        SoundBuffer newSoundBuffer;
        if (newSoundBuffer.loadFromFile(filename)) {
            sounds[filename] = newSoundBuffer;
            return sounds[filename];
        }
        else {
            // ���� ó�� ���� (��: �⺻ ���� ���۸� ��ȯ�ϰų� ���� ó��)
            throw runtime_error("Failed to load sound: " + filename);
        }
    }
}
