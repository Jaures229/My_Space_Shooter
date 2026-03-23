#include "../include/Projectile.hpp"


Projectile::Projectile(sf::Vector2f startPos, const sf::Texture& tex)
{
    this->setTexture(tex);
    this->setOrigin(this->getLocalBounds().width / 2.f, this->getLocalBounds().height / 2.f);
    this->setPosition(startPos);
    this->setScale(1.5f, 1.5f);
    speed = 800.f;
}

void Projectile::update(sf::Time dt)
{
    this->move(speed * dt.asSeconds(), 0.f);
}
void Projectile::setSpeed(float newspeed)
{
    speed = newspeed;
}
