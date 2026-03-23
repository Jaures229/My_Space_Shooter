#ifndef GAME_HPP_
    #define GAME_HPP_
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <vector>
    #include "Player.hpp"
    #include "Enemy.hpp"
    #include "EnemyManager.hpp"
    #include "Explosion.hpp"
    #include "AudioManager.hpp"

    enum class GameState {
        MENU,
        PLAYING,
        GAME_OVER
    };

    class Game {
    private:
        sf::RenderWindow window;
        GameState currentState;

        #pragma region Menu_text_variable
        // Pour le Menu
        sf::RectangleShape playButton;
        sf::Font font;
        sf::Text menuText;
        sf::Text buttonText;
        sf::Text titleText;

        sf::Text gameOverText;
        sf::Text retryInfoText;

        #pragma endregion Menu_text_variable

        #pragma region GameEntity
        Player player;
        EnemyManager enemyManager;
        AudioManager audiomanager;
        #pragma endregion GameEntity

        #pragma region Menu_animation_variable

        std::vector<sf::Texture> backgroundFrames;
        sf::Sprite backgroundSprite;

        int currentBgFrame = 0;
        float bgTimer = 0.f;
        float bgFrameDuration = 0.05f;

        #pragma endregion Menu_variable
    
        #pragma region Scrolling_bg
        sf::Texture spaceTexture;
        sf::Sprite bgSprite1;
        sf::Sprite bgSprite2;
        float scrollSpeed = 200.f;
        #pragma endregion Scrolling_bg
        int score;
        sf::Text scoreText;
        sf::Text healthText;
        std::vector<Explosion> explosions;
        sf::Texture explosionTexture;

    public:
        Game();
        void run();
        void initMenu();
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handleMenuClick(sf::Vector2i mousePos);
        void loadBackgroundAnimation();
        void initBackground();
        void updateCollisions();
        void updateScrolling(sf::Time dt);
        void initUI();
        void updateUI();
        void initGameOverUI();
        ~Game();
    };
#endif /* !GAME_HPP_ */


