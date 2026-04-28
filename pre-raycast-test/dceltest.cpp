#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#include "Headers/DCELBuilder.h"
#include "Headers/DCEL.h"
#include "Headers/DCELpath.h"
#include "Headers/SandboxSeeker.h"

int main() {
    // SFML Window
    sf::RenderWindow window(sf::VideoMode(800, 800), "DCEL Sandbox Test");
    window.setFramerateLimit(60);

    // exact map grid
    // std::vector<std::vector<int>> grid = {
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    // };

    std::vector<std::vector<int>> grid = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };


    // NAVMESH
    DCEL* mesh = DCELBuilder::buildFromGrid(grid);

    // INITIAL CONDITION: SETUP PATH AND SEEKER
    Face* startFace = mesh->faces[0];             // Start at the top left
    Face* targetFace = mesh->faces.back();        // Aim for the bottom right
    std::vector<sf::Vector2f> currentPath = DCELpath::getPath(startFace, targetFace);

    SandboxSeeker seeker(startFace->centroid);
    seeker.setPath(currentPath);

    sf::Clock deltaClock; // time between frames for smooth movement

    //  Game Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // LEFT CLICK: move the target
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                
                //  Find what Face was clicked on (new target)
                for (Face* f : mesh->faces) {
                    sf::FloatRect bounds(f->gridX * 30, f->gridY * 30, 30, 30);
                    if (bounds.contains(mousePos)) {
                        targetFace = f;
                        
                        //  Find which face the seeker is inside right now
                        sf::Vector2f seekerPos = seeker.getPosition();
                        for (Face* seekerFace : mesh->faces) {
                            sf::FloatRect seekerBounds(seekerFace->gridX * 30, seekerFace->gridY * 30, 30, 30);
                            if (seekerBounds.contains(seekerPos)) {
                                startFace = seekerFace; // update the starting face = current seeker face
                                break;
                            }
                        }

                        // Recalculate path from the Seeker's current cell to the new target
                        currentPath = DCELpath::getPath(startFace, targetFace); 
                        // If the seeker is currently on a valid path, update the first point to be the seeker's current 
                        //position for smoother movement
                        if (!currentPath.empty()) {
                            currentPath[0] = seekerPos; 
                        }

                        seeker.setPath(currentPath); 
                        break;
                    }
                }
            }


            // // LEFT CLICK: Move the Target
            // if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            //     sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                
            //     for (Face* f : mesh->faces) {
            //         sf::FloatRect bounds(f->gridX * 30, f->gridY * 30, 30, 30);
            //         if (bounds.contains(mousePos)) {
            //             targetFace = f;
            //             currentPath = DCELpath::getPath(startFace, targetFace); 
            //             seeker.setPath(currentPath); // Tell the seeker to update its route
            //             break;
            //         }
            //     }
            // }

            // RIGHT CLICK: move the start Position / Teleport the Seeker
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                
                for (Face* f : mesh->faces) {
                    sf::FloatRect bounds(f->gridX * 30, f->gridY * 30, 30, 30);
                    if (bounds.contains(mousePos)) {
                        startFace = f;
                        seeker.setPosition(startFace->centroid); // Teleport seeker
                        currentPath = DCELpath::getPath(startFace, targetFace); 
                        seeker.setPath(currentPath);
                        break;
                    }
                }
            }
        }

        // UPDATE LOGIC
        float dt = deltaClock.restart().asSeconds();
        seeker.update(dt);

        window.clear(sf::Color(20, 20, 20));

        // --- RENDER THE DCEL ---
        for (Face* f : mesh->faces) {
            sf::RectangleShape rect(sf::Vector2f(28, 28)); 
            rect.setPosition(f->gridX * 30 + 1, f->gridY * 30 + 1);
            rect.setFillColor(sf::Color(30, 60, 30)); // Made slightly darker green so the path pops
            window.draw(rect);

            HalfEdge* startEdge = f->outerComponent;
            HalfEdge* currentEdge = startEdge;
            do {
                sf::Vector2f p1 = currentEdge->origin->position;
                sf::Vector2f p2 = currentEdge->next->origin->position;

                sf::Vector2f dir = p2 - p1;
                sf::Vector2f normal(-dir.y, dir.x); 
                float len = std::sqrt(normal.x * normal.x + normal.y * normal.y);
                normal = (normal / len) * 3.0f; 

                sf::Vertex line[] = {
                    sf::Vertex(p1 + normal, sf::Color(100, 100, 100)), 
                    sf::Vertex(p2 + normal, sf::Color(100, 100, 100))
                };

                if (currentEdge->twin != nullptr) {
                    line[0].color = sf::Color(150, 0, 0); // Darker red portals
                    line[1].color = sf::Color(150, 0, 0);
                }

                window.draw(line, 2, sf::Lines);
                currentEdge = currentEdge->next;

            } while (currentEdge != startEdge);
        }

        // --- RENDER THE PATH---
        if (currentPath.size() > 1) {
            std::vector<sf::Vertex> pathLines;
            for (const auto& point : currentPath) {
                pathLines.push_back(sf::Vertex(point, sf::Color::Green));
            }
            window.draw(&pathLines[0], pathLines.size(), sf::LineStrip);
        }

        // --- RENDER START AND END DOTS ---
        sf::CircleShape startDot(5.0f);
        startDot.setFillColor(sf::Color::White);
        startDot.setOrigin(5.f, 5.f);
        startDot.setPosition(startFace->centroid);
        window.draw(startDot);

        sf::CircleShape targetDot(5.0f);
        targetDot.setFillColor(sf::Color::Black);
        targetDot.setOrigin(5.f, 5.f);
        targetDot.setPosition(targetFace->centroid);
        window.draw(targetDot);

        // --- RENDER THE SEEKER ---
        seeker.render(window);

        window.display();
    }

    // Cleanup
    delete mesh;
    return 0;
}