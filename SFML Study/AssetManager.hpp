#pragma once
#include<SFML/Graphics.hpp>
#include<map>
#include<cassert>
class AssetManager
{
public:
    AssetManager();
    static sf::Texture& GetTexture(std::string const& filename);
private:
    std::map<std::string, sf::Texture> m_Textures;
    //AssetManager��һ��singleton�����һ��ֻ�ܴ���һ��ʵ��
   //sInstacne  ָ��һ��ÿ�� manage instance ����ľ�ָ̬��
    static AssetManager* sInstance;
};


AssetManager* AssetManager::sInstance = nullptr;
AssetManager::AssetManager()
{
    //ֻ�������һ��AssetManager ʵ��
    //�����׳��쳣
    assert(sInstance == nullptr);
    sInstance = this;
}
sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
    auto& texMap = sInstance->m_Textures;

    //�鿴Textures�Ƿ��Ѽ���
    auto pairFound = texMap.find(filename);

    //����ǣ����� texture
    if (pairFound != texMap.end())
    {
        return pairFound->second;
    }
    else //���򣬼���texture��������
    {
        //��texture��ͼ�д���һ��Ԫ��
        auto& texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}