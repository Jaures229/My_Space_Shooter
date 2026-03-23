#ifndef ENEMY_HPP_
    #define ENEMY_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>
    class Enemy : public sf::Sprite
    {
        protected:
            sf::IntRect currentFrame;
            float animationTimer;
            float frameDuration;
            int frameCount;
            int frameWidth;
            int frameHeight;
            int hp;
        public:
            Enemy(float x, float y, float animSpeed);
            void updateAnimation(sf::Time dt);
            virtual ~Enemy() {}
            virtual void update(sf::Time dt) = 0;
            void takeDamage(int amount) { hp -= amount; }
            bool isDead() const { return hp <= 0; }
        };
#endif /* !ENEMY_HPP_ */
