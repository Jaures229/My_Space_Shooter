#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include "Projectile.hpp"
    #include "AudioManager.hpp"

    class Player : public sf::Drawable
    {
        private:
            float speed;
            sf::Texture texture;
            sf::Sprite shipSprite;

            sf::IntRect currentFrame;
            float timer;
            float animationSpeed;
            int width, height;
            int maxFrames;
            int playerdamage;
            int hp = 3;

            #pragma region Bullets
            std::vector<Projectile> bullets;
            sf::Texture bulletTexture;
            sf::Clock shootClock;
            float fireRate = 0.2f;
            AudioManager& audio;
            #pragma endregion Bullets
        public:
            Player(AudioManager &audio);
            bool init();
            void handleInput();
            void update(sf::Time dt);
            std::vector<Projectile>& getBullets();
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            void takeDamage(int amount) { hp -= amount; }
            int getHp() const { return hp; }
            bool isDead() const { return hp <= 0; }
            sf::FloatRect getGlobalBounds() const { return shipSprite.getGlobalBounds();}
            sf::Vector2f getPosition() const  { return shipSprite.getPosition(); }

        };
#endif /* !PLAYER_HPP_ */
