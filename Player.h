#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float speed;
    int hp;
    int hpMax;

    // damage effect
    float damageTimer;
    float damageTimerMax;

public:
    Player(float startX, float startY);

    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    // Getters
    sf::Vector2f getCenter() const;
    sf::FloatRect getBounds() const;
    int getHp() const;

    // Damage
    void takeDamage();
    void resetHp();
};