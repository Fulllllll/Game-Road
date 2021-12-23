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
    //AssetManager是一个singleton，因此一次只能存在一个实例
   //sInstacne  指向一个每个 manage instance 对象的静态指针
    static AssetManager* sInstance;
};


AssetManager* AssetManager::sInstance = nullptr;
AssetManager::AssetManager()
{
    //只允许存在一个AssetManager 实例
    //否则抛出异常
    assert(sInstance == nullptr);
    sInstance = this;
}
sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
    auto& texMap = sInstance->m_Textures;

    //查看Textures是否已加载
    auto pairFound = texMap.find(filename);

    //如果是，返回 texture
    if (pairFound != texMap.end())
    {
        return pairFound->second;
    }
    else //否则，加载texture并返回它
    {
        //在texture贴图中创建一个元素
        auto& texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}