
#ifndef SIMPLEENEMY_HPP_
    #define SIMPLEENEMY_HPP_
    #include <SFML/Graphics.hpp>
    #include "Enemy.hpp"
    #include <iostream>

    class ScoutEnemy : public Enemy {
        private:
            float speed = 250.f;

        public:
            ScoutEnemy(float x, float y, const sf::Texture& tex);
            void update(sf::Time dt) override;
        };
#endif /* !SIMPLEENEMY_HPP_ */
