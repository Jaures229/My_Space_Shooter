
#ifndef EXPLOSION_HPP_
    #define EXPLOSION_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>

    class Explosion : public sf::Sprite {
        private:
            sf::IntRect currentFrame;
            int frameWidth = 66;
            int frameCount = 8;
            int currentFrameIdx = 0;
            sf::Time timer;
            sf::Time frameTime = sf::seconds(0.08f);
            bool finished = false;

        public:
            Explosion(sf::Vector2f pos, const sf::Texture& tex);

            void update(sf::Time dt);

            bool isFinished() const { return finished; }
        };
#endif /* !EXPLOSION_HPP_ */
