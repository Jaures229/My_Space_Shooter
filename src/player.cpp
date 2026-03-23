#include "../include/Player.hpp"

Player::Player(AudioManager &_audio) : audio(_audio)
{
    width = 55;
    height = 29;
    currentFrame = sf::IntRect(0, 0, width, height);
    maxFrames = 7;
    timer = 0.f;
    animationSpeed = 0.15f;
    playerdamage = 1;
    init();
}

bool Player::init()
{
    if (!texture.loadFromFile("assets/sprites/ship/ship.png")) {
        std::cerr << "Erorr Loading : assets/sprites/ship.png" << std::endl;
        return false;
    }
    if (!bulletTexture.loadFromFile("assets/sprites/shots/shot.png")) {
        std::cerr << "Erorr Loading : assets/sprites/shots/shot.png" << std::endl;
        return false;
    }

    shipSprite.setTexture(texture);
    shipSprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    shipSprite.setPosition(400.f, 500.f);
    shipSprite.setScale(1.5, 1.5);
    speed = 300.f;
    return true;
}

void Player::update(sf::Time dt)
{
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1.f;

    shipSprite.move(movement * speed * dt.asSeconds());

    timer += dt.asSeconds();
    if (timer >= animationSpeed)
    {
        timer = 0.f;
        

        currentFrame.left += width;

        // Si on dépasse la dernière frame, on revient au début
        if (currentFrame.left >= width * maxFrames) {
            currentFrame.left = 0;
        }

        // On applique le nouveau rectangle au Sprite
        shipSprite.setTextureRect(currentFrame);
    }

    // Update des balles 
    for (size_t i = 0; i < bullets.size(); )
    {
        bullets[i].update(dt);

        // Si la balle sort de l'écran on la détruit
        if (bullets[i].getPosition().x > 1920.f) {
            bullets.erase(bullets.begin() + i);
        } else {
            i++;
        }
    }
    handleInput();
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        shootClock.getElapsedTime().asSeconds() >= fireRate) {
            audio.playShoot();
        sf::Vector2f spawnPos = shipSprite.getPosition();

        float offset = 10.f;

        spawnPos.x += offset;
            
        bullets.emplace_back(spawnPos, bulletTexture);

        shootClock.restart();
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shipSprite, states);

    for (const auto& bullet : bullets) {
        target.draw(bullet, states);
    }
}

std::vector<Projectile>& Player::getBullets()
{
    return bullets;
}
