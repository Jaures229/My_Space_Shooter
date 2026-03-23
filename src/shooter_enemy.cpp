#include "../include/ShooterEnemy.hpp"

ShooterEnemy::ShooterEnemy(float x, float y, const sf::Texture& tex, sf::Texture& bTex, std::vector<Projectile>& bVec) 
    : Enemy(x, y, 0.15f), bulletTex(bTex), enemyBullets(bVec)
{
    this->setTexture(tex);

    this->frameWidth = 102;
    this->frameHeight = 101;
    this->frameCount = 3;
    this->currentFrame = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
    this->hp = 1;
    this->setTextureRect(currentFrame);
}

void ShooterEnemy::update(sf::Time dt)
{
    this->move(-150.f * dt.asSeconds(), 0.f);


    // Tir automatique chaque "fireRate"
    if (shootClock.getElapsedTime().asSeconds() >= fireRate) {

        // On crée une balle
        Projectile p(this->getPosition(), bulletTex);
        p.setSpeed(-500.f); // Lui assigner une vitesse négative pour aller à gauche
        enemyBullets.push_back(p);
        shootClock.restart();
    }
    this->updateAnimation(dt);
}
