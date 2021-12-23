#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<list>

#include"AssetManager.hpp"
class Animator {
public:
    struct Animation {
        std::string m_Name;
        std::string m_TextureName;
        std::vector<sf::IntRect> m_Frames;
        sf::Time m_Duration;
        bool m_looping;

        Animation(std::string const& name, std::string const& textureName,
            sf::Time const& duration, bool looping)
            : m_Name(name), m_TextureName(textureName),
            m_Duration(duration), m_looping(looping) {}

        void AddFrames(sf::Vector2i const& startFrom,
            sf::Vector2i const& frameSize, unsigned int frames) {

            sf::Vector2i current = startFrom;
            for (unsigned int i = 0; i < frames; i++) {
                m_Frames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
                current.x += frameSize.x;
            }
        }
    };

    Animator(sf::Sprite& sprite);

    Animator::Animation& CreateAnimation(std::string const& name,
        std::string const& textureName, sf::Time const& duration, bool loop = false);

    void Update(sf::Time const& dt);

    // 是否切换成功
    bool SwitchAnimation(std::string const& name);

    std::string GetCurrentAnimationName() const;
private:
    // 通过名字查找已经添加过的动画效果 Animation
    Animator::Animation* FindAnimation(std::string const& name);

    void SwitchAnimation(Animator::Animation* animation);

    // sprite 的引用
    sf::Sprite& m_Sprite;
    sf::Time m_CurrentTime;
    std::list<Animator::Animation> m_Animations;
    Animator::Animation* m_CurrentAnimation;

};



Animator::Animator(sf::Sprite& sprite)
    : m_Sprite(sprite), m_CurrentTime(), m_CurrentAnimation(nullptr) {}
Animator::Animation& Animator::CreateAnimation(std::string const& name,
    std::string const& textureName, sf::Time const& duration, bool loop) {

    m_Animations.push_back(
        Animator::Animation(name, textureName, duration, loop));
    // 如果当前没有动画效果，则使用刚添加动画效果
    if (m_CurrentAnimation == nullptr)
        SwitchAnimation(&m_Animations.back());

    return m_Animations.back();
}
void Animator::SwitchAnimation(Animator::Animation* animation) {
    // 改变精灵的纹理
    if (animation != nullptr) {
        m_Sprite.setTexture(AssetManager::GetTexture(animation->m_TextureName));
    }
    m_CurrentAnimation = animation;
    m_CurrentTime = sf::Time::Zero; // 重置时间
}
// 是否切换成功
bool Animator::SwitchAnimation(std::string const& name) {
    auto animation = FindAnimation(name);
    if (animation != nullptr) {
        SwitchAnimation(animation);
        return true;
    }
    return false;
}
Animator::Animation* Animator::FindAnimation(std::string const& name) {
    for (auto it = m_Animations.begin(); it != m_Animations.end(); it++) {
        if (it->m_Name == name) {
            return &*it;
        }
    }
    return nullptr;
}
std::string Animator::GetCurrentAnimationName() const {
    if (m_CurrentAnimation != nullptr) {
        return m_CurrentAnimation->m_Name;
    }

    return "";
}
void Animator::Update(sf::Time const& dt) {
    if (m_CurrentAnimation == nullptr) return;

    m_CurrentTime += dt;

    // 获取当前帧
    float scaledTime = m_CurrentTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds();
    int numFrames = m_CurrentAnimation->m_Frames.size();
    int currentFrame = static_cast<int>(scaledTime * numFrames);


    // 如果动画在进行，则计算当前帧
    if (m_CurrentAnimation->m_looping) {
        currentFrame %= numFrames;
    }
    else if (currentFrame >= numFrames) { // 如果当前帧不小于总的帧数，设为最后一帧
        currentFrame = numFrames - 1;
    }

    // 设置为当前帧
    m_Sprite.setTextureRect(m_CurrentAnimation->m_Frames[currentFrame]);
}