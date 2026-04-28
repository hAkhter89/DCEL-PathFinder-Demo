#include "Headers/DCELBuilder.h"
#include <iostream> 

// DCEL from 2D array
DCEL* DCELBuilder::buildFromGrid(const std::vector<std::vector<int>>& grid) {
    DCEL* mesh = new DCEL();
    int height = grid.size();
    int width = grid[0].size();
    float tileSize = 30.0f; // Scale for math/rendering

    // Temporary grid to hold pointers to Faces to be stitched later
    std::vector<std::vector<Face*>> faceGrid(height, std::vector<Face*>(width, nullptr));

    // Build Faces, Vertices, and Half-Edges for every '0' tile (no walls)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == 0) {
                Face* f = new Face();
                f->gridX = x;
                f->gridY = y;
                f->centroid = sf::Vector2f((x + 0.5f) * tileSize, (y + 0.5f) * tileSize);
                mesh->faces.push_back(f);
                faceGrid[y][x] = f;

                // 4 corners of the tile/face
                Vertex* tl = new Vertex(); tl->position = sf::Vector2f(x * tileSize, y * tileSize);
                Vertex* bl = new Vertex(); bl->position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);
                Vertex* br = new Vertex(); br->position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
                Vertex* tr = new Vertex(); tr->position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
                
                mesh->vertices.push_back(tl); mesh->vertices.push_back(bl);
                mesh->vertices.push_back(br); mesh->vertices.push_back(tr);

                // 4 Half-Edges (Counter-Clockwise) of the tile/face
                HalfEdge* eLeft = new HalfEdge();   // TopLeft -> BottomLeft
                HalfEdge* eBottom = new HalfEdge(); // BottomLeft -> BottomRight
                HalfEdge* eRight = new HalfEdge();  // BottomRight -> TopRight
                HalfEdge* eTop = new HalfEdge();    // TopRight -> TopLeft

                mesh->halfEdges.push_back(eLeft); mesh->halfEdges.push_back(eBottom);
                mesh->halfEdges.push_back(eRight); mesh->halfEdges.push_back(eTop);

                // Origins
                eLeft->origin = tl; eBottom->origin = bl; 
                eRight->origin = br; eTop->origin = tr;

                // Faces
                f->outerComponent = eLeft;
                eLeft->incidentFace = f; eBottom->incidentFace = f;
                eRight->incidentFace = f; eTop->incidentFace = f;

                // counter-clockwise half-edge linking
                eLeft->next = eBottom; eLeft->prev = eTop;
                eBottom->next = eRight; eBottom->prev = eLeft;
                eRight->next = eTop; eRight->prev = eBottom;
                eTop->next = eLeft; eTop->prev = eRight;
            }
        }
    }

    //  Stitching: link twins of neighbouring tiles (portals)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Face* f1 = faceGrid[y][x];
            if (!f1) continue;

            // Stitch Right (connect right edge to neighbor's left edge)
            if (x + 1 < width && faceGrid[y][x + 1] != nullptr) {
                Face* f2 = faceGrid[y][x + 1];
                HalfEdge* myRight = f1->outerComponent->next->next; // Left -> Bottom -> Right
                HalfEdge* neighborLeft = f2->outerComponent;        // Starts at Left
                
                myRight->twin = neighborLeft;
                neighborLeft->twin = myRight;
            }

            // Stitch Down (connect Bottom edge to neighbor's top edge)
            if (y + 1 < height && faceGrid[y + 1][x] != nullptr) {
                Face* f2 = faceGrid[y + 1][x];
                HalfEdge* myBottom = f1->outerComponent->next;      // Left -> Bottom
                HalfEdge* neighborTop = f2->outerComponent->next->next->next; // L -> B -> R -> Top
                
                myBottom->twin = neighborTop;
                neighborTop->twin = myBottom;
            }
        }
    }

    std::cout << "[DCELBuilder] built: " << mesh->faces.size() << " Faces, " 
              << mesh->halfEdges.size() << " Edges." << std::endl;
              
    return mesh;
}