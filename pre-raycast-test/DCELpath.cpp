#include "Headers/DCELpath.h"
#include <unordered_map>
#include <cmath>
#include <algorithm> // std::reverse and std::find

// Heuristic
float DCELpath::heuristic(Face* a, Face* b) {
    // distance in tiles (1 step = 1 distance unit)
    return std::abs(a->gridX - b->gridX) + std::abs(a->gridY - b->gridY);
}
// A* Pathfinding
std::vector<sf::Vector2f> DCELpath::getPath(Face* startFace, Face* targetFace) {
    std::vector<sf::Vector2f> path;
    if (!startFace || !targetFace) return path;

    // represents all the faces in an array
    std::vector<Face*> openSet;
    openSet.push_back(startFace);

    std::unordered_map<Face*, Face*> cameFrom;  
    std::unordered_map<Face*, float> gScore; // steps taken from Start
    std::unordered_map<Face*, float> fScore; // estimate total cost (gScore + heuristic)

    gScore[startFace] = 0.0f;
    fScore[startFace] = heuristic(startFace, targetFace);

    bool found = false;

    while (!openSet.empty()) {
        // find the Face in the openSet with the lowest fScore by looping through the list of faces
        auto currentIt = openSet.begin();
        float lowestF = fScore[*currentIt];
        
        for (auto it = openSet.begin(); it != openSet.end(); ++it) {
            if (fScore[*it] < lowestF) {
                lowestF = fScore[*it];
                currentIt = it;
            }
        }

        Face* current = *currentIt;

        // check if at target
        if (current == targetFace) {
            found = true;
            break;
        }

        //  remove the current face from the openSet so we don't check it again
        openSet.erase(currentIt);

        // check all neighbors (portals)
        HalfEdge* startEdge = current->outerComponent;
        HalfEdge* edge = startEdge;
        do {
            if (edge->twin) { // if this edge has a portal to another face
                Face* neighbor = edge->twin->incidentFace; // the face on the other side of the portal
                float tentative_gScore = gScore[current] + 1.0f; // increment the gscore for each portal step

                // If this path to the neighbor is better than any previous one, record it
                if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentative_gScore;
                    fScore[neighbor] = tentative_gScore + heuristic(neighbor, targetFace);

                    // Add neighbor to openSet
                    if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
                        openSet.push_back(neighbor);
                    }
                }
            }
            edge = edge->next; 
        } while (edge != startEdge);
    }

    // build the line from start to target
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