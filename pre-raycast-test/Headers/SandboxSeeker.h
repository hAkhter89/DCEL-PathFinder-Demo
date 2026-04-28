#ifndef SANDBOX_SEEKER_H
#define SANDBOX_SEEKER_H

#include <SFML/Graphics.hpp>
#include <vector>

class SandboxSeeker {
private:
    sf::Vector2f position;
    float speed;
    std::vector<sf::Vector2f> path;
    size_t currentWaypoint; 

public:
    // Declarations
    SandboxSeeker(sf::Vector2f startPos);
    void setPath(const std::vector<sf::Vector2f>& newPath);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
};

#endif