#include "../include/Enemy.hpp"

void Enemy::updateAnimation(sf::Time dt)
{
    animationTimer += dt.asSeconds();

    if (animationTimer >= frameDuration) {
        animationTimer = 0.f;
        currentFrame.left += frameWidth;
        if (currentFrame.left >= frameWidth * frameCount) {
            currentFrame.left = 0;
        }
        this->setTextureRect(currentFrame);
    }
}

Enemy::Enemy(float x, float y, float animSpeed = 0.1f):
    animationTimer(0.f), frameDuration(animSpeed)
{
    this->setPosition(x, y);
}
