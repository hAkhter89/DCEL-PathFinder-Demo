#include "Headers/SandboxSeeker.h"
#include <cmath> 

// Constructor
SandboxSeeker::SandboxSeeker(sf::Vector2f startPos) 
    : position(startPos), speed(50.0f), currentWaypoint(0) {
}

// set seeker on the pathfinded line
void SandboxSeeker::setPath(const std::vector<sf::Vector2f>& newPath) {
    path = newPath;
    currentWaypoint = 0; // Reset to the first dot
}

// Movement
void SandboxSeeker::update(float deltaTime) {
    // no path =  stand still
    if (path.empty() || currentWaypoint >= path.size()) return;

    // Move towards the current waypoint
    sf::Vector2f target = path[currentWaypoint];
    sf::Vector2f diff = target - position;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    // append waypoint if close to current one
    if (distance < 3.0f) {
        currentWaypoint++;
    } 
    // keep walking to the current waypoint
    else {
        sf::Vector2f dir = diff / distance;
        position += dir * speed * deltaTime;
    }
}

// Render
void SandboxSeeker::render(sf::RenderWindow& window) {
    sf::CircleShape body(8.0f); // radius 8 circle
    body.setFillColor(sf::Color::Red);
    body.setOrigin(body.getRadius(), body.getRadius()); // centered
    body.setPosition(position);
    window.draw(body);
}

// teleport logic
void SandboxSeeker::setPosition(sf::Vector2f pos) { 
    position = pos; 
}

// get position
sf::Vector2f SandboxSeeker::getPosition() const { 
    return position; 
}