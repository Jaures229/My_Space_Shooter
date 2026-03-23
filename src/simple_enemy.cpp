#include "../include/SimpleEnemy.hpp"

ScoutEnemy::ScoutEnemy(float x, float y, const sf::Texture& tex) : Enemy(x, y, 0.15f)
{
    this->setTexture(tex);
    this->frameWidth = 66;
    this->frameHeight = 34;
    this->frameCount = 6;
    this->currentFrame = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
    this->hp = 1;
    this->setScale(1.5f, 1.5f);
    this->setTextureRect(currentFrame);
}

void ScoutEnemy::update(sf::Time dt)
{
    this->move(-speed * dt.asSeconds(), 0.f);
    this->updateAnimation(dt);
}
