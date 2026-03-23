#include "../include/Game.hpp"


Game::Game() 
    : window(sf::VideoMode(1920, 1080), "Space Shooter - GTECH2"), 
      currentState(GameState::MENU), audiomanager(), player(audiomanager)
{
    window.setFramerateLimit(60);
    initMenu();
    initUI();
    initBackground();
    initGameOverUI();
}

void Game::run()
{
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (currentState == GameState::MENU) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMenuClick(sf::Mouse::getPosition(window));
                }
            }
        }
    }
}

void Game::render()
{
    window.clear();

    if (currentState == GameState::MENU) {
        window.draw(backgroundSprite);
        window.draw(playButton);
        window.draw(buttonText);
        window.draw(titleText);
    } if (currentState == GameState::PLAYING) {
        window.draw(bgSprite1);
        window.draw(bgSprite2);
        window.draw(player);
        enemyManager.draw(window);
        window.draw(scoreText);
        window.draw(healthText);

        for (const auto& e : explosions) {
            window.draw(e);
        }
    } if (currentState == GameState::GAME_OVER) {
        sf::RectangleShape overlay(sf::Vector2f(1920, 1080));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        window.draw(gameOverText);
        window.draw(retryInfoText);
    }

    window.display();
}

#pragma region Menu

void Game::initMenu()
{
    if (!font.loadFromFile("assets/fonts/ARCADECLASSIC.TTF")) {
        std::cerr << "Error Loading assets/fonts/ARCADECLASSIC.TTF" << std::endl;
        return; 
    }
    if (!explosionTexture.loadFromFile("assets/sprites/explosions/explosions.png")) {
        std::cerr << "Error Loading assets/sprites/explosions/explosions.png" << std::endl;
        return; 
    }

    // Configuration du rectangle du bouton
    playButton.setSize(sf::Vector2f(200.f, 60.f));
    sf::Vector2f buttonSize = playButton.getSize();
    playButton.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
    playButton.setFillColor(sf::Color::Blue);
    playButton.setOutlineThickness(2);
    playButton.setOutlineColor(sf::Color::White);
    
    // Centrer le bouton
    playButton.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f); 

    // Configuration du texte "PLAY"
    buttonText.setFont(font);
    buttonText.setString("PLAY");
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::White);

    // Centrer le texte dans le bouton
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, 
                     textRect.top + textRect.height / 2.0f);

    // Le placer exactement sur la même position que le bouton
    buttonText.setPosition(playButton.getPosition());
    loadBackgroundAnimation();

    titleText.setFont(font);
    titleText.setString("MY SPACE SHOOTER");
    titleText.setCharacterSize(80); 
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 
                        titleBounds.top + titleBounds.height / 2.0f);
    
    titleText.setPosition(window.getSize().x / 2.0f, window.getSize().y * 0.25f);
}

void Game::handleMenuClick(sf::Vector2i mousePos)
{

    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));


    if (playButton.getGlobalBounds().contains(mousePosF)) {
        currentState = GameState::PLAYING;
    }
}

void Game::loadBackgroundAnimation()
{
    for (int i = 1; i <= 23; ++i)
    {
        sf::Texture tex;
        std::string filename = "assets/animations/menu_bg_anim/frame" + std::to_string(i) + ".jpg";
        
        if (tex.loadFromFile(filename)) {
            backgroundFrames.push_back(tex);
        }
    }

    if (!backgroundFrames.empty()) {
        backgroundSprite.setTexture(backgroundFrames[0]);
        
        // Redimensionner le background pour qu'il remplisse le 1920x1080
        float scaleX = 1920.f / backgroundSprite.getLocalBounds().width;
        float scaleY = 1080.f / backgroundSprite.getLocalBounds().height;
        backgroundSprite.setScale(scaleX, scaleY);
    }
}

#pragma endregion Menu

void Game::update(sf::Time deltaTime)
{
    if (currentState == GameState::PLAYING) {
        player.update(deltaTime);
        updateScrolling(deltaTime);
        enemyManager.update(deltaTime);
        updateCollisions();
    }
    if (currentState == GameState::MENU) {
        bgTimer += deltaTime.asSeconds();
        
        if (bgTimer >= bgFrameDuration) {
            bgTimer = 0.f;
            currentBgFrame = (currentBgFrame + 1) % backgroundFrames.size();

            backgroundSprite.setTexture(backgroundFrames[currentBgFrame]);
        }
    }
    if (currentState == GameState::GAME_OVER) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        return;
    }

    if (player.getHp() <= 0) {
        currentState = GameState::GAME_OVER;
    }
    for (size_t i = 0; i < explosions.size(); ) {
        explosions[i].update(deltaTime);
        if (explosions[i].isFinished()) {
            explosions.erase(explosions.begin() + i);
        } else {
            i++;
        }
    }
}

#pragma region Scrolling_bg


void Game::initBackground()
{
    if (!spaceTexture.loadFromFile("assets/sprites/bg/Yellow_Nebular.png")) {
        std::cerr << "Error loading  assets/sprites/bg/Purple_Nebular.png" << std::endl;
        return;
    }

    bgSprite1.setTexture(spaceTexture);
    bgSprite2.setTexture(spaceTexture);


    bgSprite1.setPosition(0, 0);
    bgSprite2.setPosition(1920.f, 0); 
}

void Game::updateScrolling(sf::Time dt)
{
    float movement = scrollSpeed * dt.asSeconds();

    bgSprite1.move(-movement, 0);
    bgSprite2.move(-movement, 0);

    // Si le sprite 1 est complètement sorti par la gauche (X < -1920)
    if (bgSprite1.getPosition().x <= -1920.f) {
        // On le replace à droite du sprite 2
        bgSprite1.setPosition(bgSprite2.getPosition().x + 1920.f, 0.f);
    }

    // Idem pour le sprite 2
    if (bgSprite2.getPosition().x <= -1920.f) {
        bgSprite2.setPosition(bgSprite1.getPosition().x + 1920.f, 0.f);
    }
}

#pragma endregion Scrolling_bg

#pragma region Collisions

void Game::updateCollisions()
{
    auto& bullets = player.getBullets();
    auto& enemies = enemyManager.getEnemies();

    // On parcourt les projectiles
    for (size_t i = 0; i < bullets.size(); ) {
        bool bulletHit = false;

        // On parcourt les ennemis
        for (size_t j = 0; j < enemies.size(); ) {
            
            // Collision par "AABB" 
            if (bullets[i].getGlobalBounds().intersects(enemies[j]->getGlobalBounds())) {

                audiomanager.playExplosion();
                // Créer l'explosion à la position de l'ennemi

                explosions.emplace_back(enemies[j]->getPosition(), explosionTexture);
                // Suppresion de l'enemi

                enemies.erase(enemies.begin() + j);
                // On marque la balle pour la supprimer
                bulletHit = true;
                score += 100;
                updateUI();

                break;
            } else {
                j++;
            }
        }

        if (bulletHit) {
            bullets.erase(bullets.begin() + i);
        } else {
            i++;
        }
    }

    // Collision Joueur -> Vaisseaux Ennemis
    for (size_t i = 0; i < enemies.size(); ) {
        if (player.getGlobalBounds().intersects(enemies[i]->getGlobalBounds())) {
            player.takeDamage(1);
            explosions.emplace_back(enemies[i]->getPosition(), explosionTexture);
            enemies.erase(enemies.begin() + i);
            updateUI();
        } else {
            i++;
        }
    }

    //  Collision Joueur -> Balles Ennies
    auto& eBullets = enemyManager.getEnemyProjectiles();
    for (size_t i = 0; i < eBullets.size(); ) {
        if (player.getGlobalBounds().intersects(eBullets[i].getGlobalBounds())) {
            player.takeDamage(1);
            eBullets.erase(eBullets.begin() + i);
            updateUI();
        } else {
            i++;
        }
    }

    // Vérification de la mort du joueur
    if (player.isDead()) {
        std::cout << "GAME OVER" << std::endl;
    }
}
#pragma endregion Collisions


#pragma region UI

void Game::initUI()
{
    score = 0;
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("SCORE 0");

    healthText.setFont(font);
    healthText.setCharacterSize(30);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(20.f, 60.f);
    healthText.setString("HEALTH " + std::to_string(player.getHp()));
}

void Game::updateUI()
{
    scoreText.setString("SCORE " + std::to_string(score));
    healthText.setString("HEALTH " + std::to_string(player.getHp()));
}
#pragma endregion UI

#pragma region GameOver

void Game::initGameOverUI()
{
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    
    // Centrage du texte "GAME OVER"
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    gameOverText.setPosition(960.f, 450.f);

    retryInfoText.setFont(font);
    retryInfoText.setString("Appuyez sur ECHAP pour quitter");
    retryInfoText.setCharacterSize(30);
    retryInfoText.setFillColor(sf::Color::White);
    
    sf::FloatRect infoBounds = retryInfoText.getLocalBounds();
    retryInfoText.setOrigin(infoBounds.width / 2.f, infoBounds.height / 2.f);
    retryInfoText.setPosition(960.f, 600.f);
}

#pragma endregion GameOver

Game::~Game()
{
}