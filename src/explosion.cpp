#include "../include/Explosion.hpp"

Explosion::Explosion(sf::Vector2f pos, const sf::Texture& tex)
{
    this->setTexture(tex);
    this->setOrigin(frameWidth / 2.f, frameWidth / 2.f);
    this->setPosition(pos);
    this->currentFrame = sf::IntRect(0, 0, frameWidth, frameWidth);
    this->setTextureRect(currentFrame);
}

void Explosion::update(sf::Time dt)
{
    timer += dt;
    if (timer >= frameTime) {
        currentFrameIdx++;
        if (currentFrameIdx < frameCount) {
            currentFrame.left = currentFrameIdx * frameWidth;
            this->setTextureRect(currentFrame);
            timer = sf::Time::Zero;
        } else {
            finished = true;
        }
    }
}
