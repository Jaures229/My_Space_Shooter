#ifndef PROJECTILE_HPP_
    #define PROJECTILE_HPP_
    #include <iostream>
    #include <SFML/Graphics.hpp>

    class Projectile : public sf::Sprite
    {
        private:
            float speed;

        public:
            Projectile(sf::Vector2f startPos, const sf::Texture& tex);
            void update(sf::Time dt);
            void setSpeed(float newspeed);
        };
#endif /* !PROJECTILE_HPP_ */
