#include "Player.h"
#include <iostream>

Player::Player(float startX, float startY) {
    if (!texture.loadFromFile("ship.png")) {
        std::cout << "Error loading ship.png\n";
    }

    sprite.setTexture(texture);
    sprite.setPosition(startX, startY);
    sprite.setScale(0.2f, 0.2f);

    speed = 4.f;
    hpMax = 10;
    hp = hpMax;

    damageTimerMax = 10.f;
    damageTimer = 0.f;
}

void Player::update(const sf::RenderWindow& window) {
    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) sprite.move(-speed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) sprite.move(speed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) sprite.move(0.f, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) sprite.move(0.f, speed);

    // Boundaries
    if (sprite.getPosition().x < 0)
        sprite.setPosition(0.f, sprite.getPosition().y);

    if (sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x)
        sprite.setPosition(window.getSize().x - sprite.getGlobalBounds().width, sprite.getPosition().y);

    if (sprite.getPosition().y < 0)
        sprite.setPosition(sprite.getPosition().x, 0.f);

    if (sprite.getPosition().y + sprite.getGlobalBounds().height > window.getSize().y)
        sprite.setPosition(sprite.getPosition().x, window.getSize().y - sprite.getGlobalBounds().height);

    // Damage flash effect
    if (damageTimer > 0.f) {
        damageTimer -= 1.f;
        sprite.setColor(sf::Color::Red);
    } else {
        sprite.setColor(sf::Color::White);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getCenter() const {
    return sf::Vector2f(
        sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f,
        sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f
    );
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

int Player::getHp() const {
    return hp;
}

void Player::takeDamage() {
    hp--;
    damageTimer = damageTimerMax; // trigger red flash
}

void Player::resetHp() {
    hp = hpMax;
}