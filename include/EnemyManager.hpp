
#ifndef ENEMYMANAGER_HPP_
    #define ENEMYMANAGER_HPP_
    #include <vector>
    #include <memory> 
    #include "Enemy.hpp"
    #include "SimpleEnemy.hpp"
    #include "ZigZagEnemy.hpp"
    #include "Projectile.hpp"
    #include "ShooterEnemy.hpp"

    enum class SpawnMode { SINGLE, WAVE };

    class EnemyManager {
    private:
        std::vector<std::unique_ptr<Enemy>> enemies;
        std::vector<Projectile> enemyBullets;
        sf::Clock spawnClock;
        float spawnRate;
        
        sf::Texture scoutTexture;
        sf::Texture zigzagTexture;
        sf::Texture shooterTexture;
        sf::Texture enemyBulletTexture;

        float nextSpawnDelay = 2.0f;
        bool isWaveActive = false;
        int remainingInWave = 0;
        float waveInterval = 0.3f;
    public:
        EnemyManager();
        void update(sf::Time dt);
        void init();
        void draw(sf::RenderWindow& window);
        void spawnSingle();
        void spawnWave();
        bool isLevelEmpty() const { return enemies.empty(); }
        std::vector<std::unique_ptr<Enemy>>& getEnemies();
        std::vector<Projectile> & getEnemyProjectiles();
    };
#endif /* !ENEMYMANAGER_HPP_ */
