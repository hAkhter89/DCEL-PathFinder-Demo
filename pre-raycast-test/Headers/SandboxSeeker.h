#ifndef SANDBOX_SEEKER_H
#define SANDBOX_SEEKER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class SandboxSeeker {
private:
    sf::Vector2f position;
    float speed;
    std::vector<sf::Vector2f> path;
    size_t currentWaypoint; // Tracks which dot in the path we are walking towards

public:
    SandboxSeeker(sf::Vector2f startPos) {
        position = startPos;
        speed = 50.0f; // Pixels per second (adjust if it's too fast/slow)
        currentWaypoint = 0;
    }

    // Give the Seeker a new brain-calculated path
    void setPath(const std::vector<sf::Vector2f>& newPath) {
        path = newPath;
        currentWaypoint = 0; // Reset to the first dot
    }

    void update(float deltaTime) {
        // If we have no path, or we reached the end, stand still
        if (path.empty() || currentWaypoint >= path.size()) return;

        // Where are we trying to go?
        sf::Vector2f target = path[currentWaypoint];
        sf::Vector2f diff = target - position;
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        // If we are basically touching the waypoint (within 3 pixels), aim for the next one
        if (distance < 3.0f) {
            currentWaypoint++;
        } 
        // Otherwise, keep walking towards it
        else {
            sf::Vector2f dir = diff / distance;
            position += dir * speed * deltaTime;
        }
    }

    void render(sf::RenderWindow& window) {
        sf::CircleShape body(8.0f);
        body.setFillColor(sf::Color::Red);
        body.setOrigin(8.0f, 8.0f);
        body.setPosition(position);
        window.draw(body);
    }
    
    void setPosition(sf::Vector2f pos) { position = pos; }
};

#endif