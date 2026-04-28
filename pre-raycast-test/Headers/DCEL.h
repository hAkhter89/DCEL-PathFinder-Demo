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
    HalfEdge* incidentEdge; 
    
    Vertex();
};

// cell in the navmesh
class Face {
public:
    int id;
    int gridX; 
    int gridY; 
    sf::Vector2f centroid; 
    HalfEdge* outerComponent; 
    
    Face();
};

// Counter-Clockwise points connecting/stiching cells in the navmesh
class HalfEdge {
public:
    Vertex* origin;         
    HalfEdge* twin;         
    Face* incidentFace;     
    HalfEdge* next;         
    HalfEdge* prev;         
    
    HalfEdge();
};

// wrapper class to hold vectors of all the DCEL components
class DCEL {
public:
    std::vector<Vertex*> vertices;
    std::vector<HalfEdge*> halfEdges;
    std::vector<Face*> faces;

    DCEL(); 
    ~DCEL(); 
};

#endif