#ifndef ZIGZAGENEMY_HPP_
    #define ZIGZAGENEMY_HPP_
    #include "Enemy.hpp"
    #include <cmath>

    class ZigZagEnemy : public Enemy {
    private:
        float speed;
        float amplitude;
        float frequency;
        float elapsedTime;

    public:
        ZigZagEnemy(float x, float y, const sf::Texture& tex);

        void update(sf::Time dt) override;
    };
#endif /* !ZIGZAGENEMY_HPP_ */
