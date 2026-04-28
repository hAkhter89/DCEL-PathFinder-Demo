#ifndef DCEL_BUILDER_H
#define DCEL_BUILDER_H

#include <vector>
#include "DCEL.h" 

class DCELBuilder {
public:
    // Takes a simple 2D grid of 1s and 0s and compiles it into a DCEL navmesh.
    static DCEL* buildFromGrid(const std::vector<std::vector<int>>& grid);
};

#endif