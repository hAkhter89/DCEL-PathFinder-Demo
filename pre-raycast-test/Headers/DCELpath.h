#ifndef DCEL_PATH_H
#define DCEL_PATH_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "DCEL.h" 

class DCELpath {
public:
    // Declarations
    static float heuristic(Face* a, Face* b);
    static std::vector<sf::Vector2f> getPath(Face* startFace, Face* targetFace);
};

#endif