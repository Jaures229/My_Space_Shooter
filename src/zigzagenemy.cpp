#include "../include/ZigZagEnemy.hpp"

ZigZagEnemy::ZigZagEnemy(float x, float y, const sf::Texture& tex) 
            : Enemy(x, y, 0.15f), speed(200.f), amplitude(150.f), frequency(4.f), elapsedTime(0.f) 
{
            this->setTexture(tex);
            
            this->frameWidth = 32;
            this->frameHeight = 30;
            this->frameCount = 8;
            this->currentFrame = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
            this->setTextureRect(currentFrame);
            this->setScale(1.5f, 1.5f);
}

void ZigZagEnemy::update(sf::Time dt)
{
    elapsedTime += dt.asSeconds();
    
    float vx = -speed * dt.asSeconds();
    
    // Y : calcul de la vitesse verticale basée sur la dérivée de sin(t)

    float nextY = std::sin((elapsedTime + dt.asSeconds()) * frequency) * amplitude;

    float currentY = std::sin(elapsedTime * frequency) * amplitude;
    float vy = nextY - currentY;

    this->move(vx, vy);
    this->updateAnimation(dt);
}
