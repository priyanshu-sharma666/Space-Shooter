#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.h"

class Game {
private:
    sf::RenderWindow window;
    Player player;

    // Projectiles
    sf::CircleShape projectilePrefab;
    std::vector<sf::CircleShape> projectiles;

    // Enemies (SPRITES NOW)
    sf::Texture enemyTexture;
    sf::Sprite enemyPrefab;
    std::vector<sf::Sprite> enemies;

    // UI
    sf::Font font;
    sf::Text scoreText;
    sf::Text hpText;
    sf::Text gameOverText;
    sf::RectangleShape hpBarBehind;
    sf::RectangleShape hpBar;

    // Game logic
    int score;
    bool gameOver;
    int shootTimer;
    int enemySpawnTimer;

    void initVariables();
    void initUI();
    void processEvents();
    void update();
    void updateProjectiles();
    void updateEnemies();
    void updateCollisions();
    void updateUI();
    void render();

public:
    Game();
    void run();
};