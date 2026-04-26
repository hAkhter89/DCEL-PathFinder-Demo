#ifndef DCEL_PATH_H
#define DCEL_PATH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm> // For std::reverse and std::find

#include "DCEL.h" 

class DCELpath {
public:
    static float heuristic(Face* a, Face* b) {
        return std::abs(a->centroid.x - b->centroid.x) + std::abs(a->centroid.y - b->centroid.y);
    }

    static std::vector<sf::Vector2f> getPath(Face* startFace, Face* targetFace) {
        std::vector<sf::Vector2f> path;
        if (!startFace || !targetFace) return path;

        // Using a simple vector list of rooms to check (Queue-Free A*)
        std::vector<Face*> openSet;
        openSet.push_back(startFace);

        std::unordered_map<Face*, Face*> cameFrom;  
        std::unordered_map<Face*, float> gScore; // Exact steps taken from Start
        std::unordered_map<Face*, float> fScore; // Estimated total cost (gScore + heuristic)

        gScore[startFace] = 0.0f;
        fScore[startFace] = heuristic(startFace, targetFace);

        bool found = false;

        while (!openSet.empty()) {
            // 1. Manually find the Face in the openSet with the lowest fScore
            auto currentIt = openSet.begin();
            float lowestF = fScore[*currentIt];
            
            for (auto it = openSet.begin(); it != openSet.end(); ++it) {
                if (fScore[*it] < lowestF) {
                    lowestF = fScore[*it];
                    currentIt = it;
                }
            }

            Face* current = *currentIt;

            // 2. Did we reach the target?
            if (current == targetFace) {
                found = true;
                break;
            }

            // 3. Remove the current face from the openSet so we don't check it again
            openSet.erase(currentIt);

            // 4. Check all neighbors (portals)
            HalfEdge* startEdge = current->outerComponent;
            HalfEdge* edge = startEdge;
            do {
                if (edge->twin) {
                    Face* neighbor = edge->twin->incidentFace;
                    float tentative_gScore = gScore[current] + 1.0f;

                    // If this is a new room, or we found a shorter path to an old room
                    if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
                        cameFrom[neighbor] = current;
                        gScore[neighbor] = tentative_gScore;
                        fScore[neighbor] = tentative_gScore + heuristic(neighbor, targetFace);

                        // Add neighbor to openSet if it isn't already in there
                        if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
                            openSet.push_back(neighbor);
                        }
                    }
                }
                edge = edge->next; 
            } while (edge != startEdge);
        }

        // 5. Backtrack to build the exact coordinate line
        if (found) {
            Face* current = targetFace;
            while (current != startFace) {
                path.push_back(current->centroid);
                current = cameFrom[current];
            }
            path.push_back(startFace->centroid);
            
            std::reverse(path.begin(), path.end()); 
        }

        return path;
    }
};

#endif