cmake_minimum_required(VERSION 3.10)
project(MySFMLProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2 COMPONENTS graphics window system  audio REQUIRED)


add_executable(SpaceShooter
    src/game.cpp
    src/main.cpp
    src/enemy.cpp
    src/projectile.cpp
    src/simple_enemy.cpp
    src/zigzagenemy.cpp
    src/enemy_manager.cpp
    src/explosion.cpp
    src/shooter_enemy.cpp
    src/audio_manager.cpp
    src/player.cpp
)

target_link_libraries(SpaceShooter PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
