#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

using namespace sf;
using namespace std;

class ResourceManager {
public:
    static ResourceManager& getInstance(); // 싱글톤 인스턴스 반환

    Texture& getTexture(const string& filename);
    SoundBuffer& getSound(const string& filename);

private:
    ResourceManager(); // 생성자를 private로 설정하여 외부에서 인스턴스 생성 방지
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    map<string, Texture> textures;
    map<string, SoundBuffer> sounds;
};
