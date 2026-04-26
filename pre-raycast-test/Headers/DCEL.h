#ifndef DCEL_H
#define DCEL_H

#include <SFML/Graphics.hpp>
#include <vector>

// Forward declarations 
class HalfEdge;
class Face;

// A physical point in 2D space
class Vertex {
public:
    sf::Vector2f position;
    HalfEdge* incidentEdge = nullptr; 
};

// A walkable room/polygon
class Face {
public:
    int id = 0;
    int gridX = 0; // Needed for the Grid Builder to keep track of tiles
    int gridY = 0; // Needed for the Grid Builder to keep track of tiles
    sf::Vector2f centroid; // The exact center of the tile (crucial for AI pathfinding!)
    HalfEdge* outerComponent = nullptr; 
};

// The core of the NavMesh.
class HalfEdge {
public:
    Vertex* origin = nullptr;         
    HalfEdge* twin = nullptr;         
    Face* incidentFace = nullptr;     
    HalfEdge* next = nullptr;         
    HalfEdge* prev = nullptr;         
};

// The wrapper class to hold and manage the memory of the mesh
class DCEL {
public:
    std::vector<Vertex*> vertices;
    std::vector<HalfEdge*> halfEdges;
    std::vector<Face*> faces;

    ~DCEL() {
        for (auto v : vertices) delete v;
        for (auto e : halfEdges) delete e;
        for (auto f : faces) delete f;
    }
};

#endif