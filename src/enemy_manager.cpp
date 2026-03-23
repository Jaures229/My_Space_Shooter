#include "../include/EnemyManager.hpp"

EnemyManager::EnemyManager()
{
    init();
}

void EnemyManager::update(sf::Time dt)
{
    // Mise à jour des ennemis existants
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        (*it)->update(dt);
        if ((*it)->getPosition().x < -100.f) it = enemies.erase(it);
        else ++it;
    }

    // On ne spawn QUE si l'écran est vide
    if (enemies.empty()) {
        if (spawnClock.getElapsedTime().asSeconds() >= nextSpawnDelay) {
            
            // 30% de chance pour une vague)
            if (rand() % 100 < 30) {
                spawnWave();
            } else {
                spawnSingle();
            }
            spawnClock.restart();
        }
    }

    for (size_t i = 0; i < enemyBullets.size(); ) {
        enemyBullets[i].update(dt);
        
        // Suppression si elles sortent de l'écran à gauche
        if (enemyBullets[i].getPosition().x < -50.f) {
            enemyBullets.erase(enemyBullets.begin() + i);
        } else {
            i++;
        }
    }
}

void EnemyManager::spawnSingle()
{
    float ry = static_cast<float>(rand() % 800 + 100);

    int roll = rand() % 100;

    if (roll < 50) {
        // 50% de chance : Scout
        enemies.push_back(std::make_unique<ScoutEnemy>(2000.f, ry, scoutTexture));
    }
    else if (roll < 80) {
        // 30% de chance : ZigZag
        enemies.push_back(std::make_unique<ZigZagEnemy>(2000.f, ry, zigzagTexture));
    } 
    else {
        // 20% de chance : Shooter
        enemies.push_back(std::make_unique<ShooterEnemy>(
            2000.f, ry, shooterTexture, enemyBulletTexture, enemyBullets
        ));
    }
}

void EnemyManager::spawnWave()
{
    int waveSize = 4;
    float ry = static_cast<float>(rand() % 600 + 200);
    int type = rand() % 2;

    for (int i = 0; i < waveSize; ++i) {
        float posX = 2000.f + (i * 200.f);
        
        if (type == 0) {
            enemies.push_back(std::make_unique<ZigZagEnemy>(posX, ry, zigzagTexture));
        } else {
            enemies.push_back(std::make_unique<ShooterEnemy>(
                posX, ry, shooterTexture, enemyBulletTexture, enemyBullets
            ));
        }
    }
}

std::vector<std::unique_ptr<Enemy>>& EnemyManager::getEnemies()
{
    return enemies;
}

void EnemyManager::draw(sf::RenderWindow& window)
{
    for (auto &&enemy : enemies)
    {
        window.draw(*enemy);
    }
    for (auto& b : enemyBullets) {
        window.draw(b);
    }
}

void EnemyManager::init()
{
    if (!scoutTexture.loadFromFile("assets/sprites/enemies/simple_ship.png")) {
        std::cerr << "Erorr Loading : assets/sprites/enemies/simple_ship.png " << std::endl;
        return;
    }
    if (!zigzagTexture.loadFromFile("assets/sprites/enemies/FastShip.png")) {
        std::cerr << "Erorr Loading : assets/sprites/enemies/FastShip.png" << std::endl;
        return;
    }
    if (!shooterTexture.loadFromFile("assets/sprites/enemies/DragonHead.png")) {
        std::cerr << "assets/sprites/enemies/DragonHead.png" << std::endl;
        return;
    }
    if (!enemyBulletTexture.loadFromFile("assets/sprites/shots/fire_ball-shot.png")) {
        std::cerr << "Erorr Loading : assets/sprites/shots/fire_ball-shot.png" << std::endl;
        return;
    }
}

std::vector<Projectile> &  EnemyManager::getEnemyProjectiles()
{
    return enemyBullets;
}
