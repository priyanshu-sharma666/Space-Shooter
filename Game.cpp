#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(640, 480), "Game"),
               player(640 / 2 - 50.f, 480 - 100.f) {
    window.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(NULL)));

    initVariables();
    initUI();
}

void Game::initVariables() {
    score = 0;
    gameOver = false;
    shootTimer = 0;
    enemySpawnTimer = 0;

    // Bullet
    projectilePrefab.setFillColor(sf::Color::Red);
    projectilePrefab.setRadius(5.f);

    // Enemy texture
    if (!enemyTexture.loadFromFile("enemy.png")) {
        std::cout << "Error loading enemy.png\n";
    }

    enemyPrefab.setTexture(enemyTexture);
    enemyPrefab.setScale(0.2f, 0.2f);
}

void Game::initUI() {
    font.loadFromFile("TTD Compadre-Regular.otf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(500.f, 10.f);

    hpText.setFont(font);
    hpText.setCharacterSize(20);
    hpText.setPosition(10.f, 5.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(180.f, 200.f);

    hpBarBehind.setSize(sf::Vector2f(200.f, 20.f));
    hpBarBehind.setFillColor(sf::Color::White);
    hpBarBehind.setPosition(10.f, 35.f);

    hpBar.setSize(sf::Vector2f(200.f, 20.f));
    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(10.f, 35.f);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (!gameOver)
            update();
        render();
    }
}

void Game::processEvents() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            window.close();

        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::R && gameOver) {
            gameOver = false;
            player.resetHp();
            enemies.clear();
            projectiles.clear();
            score = 0;
        }
    }
}

void Game::update() {
    player.update(window);
    updateProjectiles();
    updateEnemies();
    updateCollisions();
    updateUI();
}

void Game::updateProjectiles() {
    if (shootTimer < 10) shootTimer++;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 10) {
        projectilePrefab.setPosition(player.getCenter());
        projectiles.push_back(projectilePrefab);
        shootTimer = 0;
    }

    for (size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].move(0.f, -10.f);
        if (projectiles[i].getPosition().y < 0) {
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }
}

void Game::updateEnemies() {
    if (enemySpawnTimer < 30) enemySpawnTimer++;

    if (enemySpawnTimer >= 30) {
        enemyPrefab.setPosition(
            static_cast<float>(rand() % int(window.getSize().x - enemyPrefab.getGlobalBounds().width)),
            0.f
        );
        enemies.push_back(enemyPrefab);
        enemySpawnTimer = 0;
    }

    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i].move(0.f, 3.f);

        if (enemies[i].getPosition().y > window.getSize().y) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
}

void Game::updateCollisions() {
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].getGlobalBounds().intersects(player.getBounds())) {
            player.takeDamage();
            enemies.erase(enemies.begin() + i);
            i--;

            if (player.getHp() <= 0)
                gameOver = true;
        }
    }

    for (size_t i = 0; i < projectiles.size(); i++) {
        bool removed = false;

        for (size_t j = 0; j < enemies.size(); j++) {
            if (projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                score += 10;
                projectiles.erase(projectiles.begin() + i);
                enemies.erase(enemies.begin() + j);
                removed = true;
                break;
            }
        }

        if (removed) i--;
    }
}

void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
    hpText.setString("HP: " + std::to_string(player.getHp() * 10));
    hpBar.setSize(sf::Vector2f(player.getHp() * 20.f, 20.f));
}

void Game::render() {
    window.clear();

    if (gameOver) {
        window.draw(gameOverText);
    } else {
        player.draw(window);

        for (auto& e : enemies)
            window.draw(e);

        for (auto& p : projectiles)
            window.draw(p);

        window.draw(hpBarBehind);
        window.draw(hpBar);
        window.draw(hpText);
        window.draw(scoreText);
    }

    window.display();
}