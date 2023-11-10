#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

using namespace sf;
using namespace std;

class ResourceManager {
public:
    static ResourceManager& getInstance(); // �̱��� �ν��Ͻ� ��ȯ

    Texture& getTexture(const string& filename);
    SoundBuffer& getSound(const string& filename);

private:
    ResourceManager(); // �����ڸ� private�� �����Ͽ� �ܺο��� �ν��Ͻ� ���� ����
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    map<string, Texture> textures;
    map<string, SoundBuffer> sounds;
};
