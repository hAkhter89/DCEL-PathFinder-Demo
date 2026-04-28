#include "Headers/DCEL.h" 


// Vertex Constructor
Vertex::Vertex() : position(0.0f, 0.0f), incidentEdge(nullptr) {
}

// Face Constructor
Face::Face() : id(0), gridX(0), gridY(0), centroid(0.0f, 0.0f), outerComponent(nullptr) {
}

// HalfEdge Constructor
HalfEdge::HalfEdge() : origin(nullptr), twin(nullptr), incidentFace(nullptr), next(nullptr), prev(nullptr) {
}

// DCEL Constructor
DCEL::DCEL() {} // empty vectors

// Destructor
DCEL::~DCEL() {
    for (auto v : vertices) delete v;
    for (auto e : halfEdges) delete e;
    for (auto f : faces) delete f;
}