#include "ResourceManager.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

ResourceManager::ResourceManager() {

    // 리소스 초기화 코드
    for (int i = 0; i < 50; ++i) {
        string imagePath = "./resources/images/start" + to_string(i) + ".png";
        Texture texture;
        if (!texture.loadFromFile(imagePath)) {
            cerr << "Failed to load image: " << imagePath << endl;
        }
        textures[to_string(i)] = texture;
    }

    // 사운드 초기화 코드
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

// 정적 멤버 변수 초기화
ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

Texture& ResourceManager::getTexture(const string& filename) {
    auto it = textures.find(filename); // 텍스처 맵에서 요소 검색

    if (it != textures.end()) {
        // 요소를 찾았을 때 반환
        return it->second;
    }
    else {
        // 요소를 찾지 못했을 때 로딩 및 저장
        Texture newTexture;
        if (newTexture.loadFromFile(filename)) {
            textures[filename] = newTexture;
            return textures[filename];
        }
        else {
            // 에러 처리 로직 (예: 기본 텍스처를 반환하거나 예외 처리)
            throw runtime_error("Failed to load texture: " + filename);
        }
    }
}

SoundBuffer& ResourceManager::getSound(const string& filename) {
    auto it = sounds.find(filename); // 사운드 버퍼 맵에서 요소 검색

    if (it != sounds.end()) {
        // 요소를 찾았을 때 반환
        return it->second;
    }
    else {
        // 요소를 찾지 못했을 때 로딩 및 저장
        SoundBuffer newSoundBuffer;
        if (newSoundBuffer.loadFromFile(filename)) {
            sounds[filename] = newSoundBuffer;
            return sounds[filename];
        }
        else {
            // 에러 처리 로직 (예: 기본 사운드 버퍼를 반환하거나 예외 처리)
            throw runtime_error("Failed to load sound: " + filename);
        }
    }
}
