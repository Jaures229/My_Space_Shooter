#ifndef SHOOTERENEMY_HPP_
    #define SHOOTERENEMY_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include "Enemy.hpp"
    #include "Projectile.hpp"

    class ShooterEnemy : public Enemy {
        private:
            sf::Clock shootClock;
            float fireRate = 3.5f;
            sf::Texture& bulletTex;
            std::vector<Projectile>& enemyBullets;

        public:
            ShooterEnemy(float x, float y, const sf::Texture& tex, sf::Texture& bTex, std::vector<Projectile>& bVec);

            void update(sf::Time dt) override;
        };
#endif /* !SHOOTERENEMY_HPP_ */
