/**
 * @file SpatialGrid.h
 * @brief Spatial hash grid for fast 2D point queries on shapes.
 *
 * The class maintains a uniform hash grid for efficient lookup
 * of shapes near a given point. Shapes are inserted into one or
 * more cells based on their bounding boxes, and reverse indexing
 * allows fast removal.
 *
 * Author: Hristo Hristov
 * 07.12.2025
 */

#pragma once
#include <unordered_map>
#include <vector>
#include "CShape.h"

 /**
  * @class SpatialGrid
  * @brief Uniform spatial hash grid for accelerating point queries.
  */
class SpatialGrid
{
public:
    /**
     * @brief Creates a grid with the given cell size.
     * @param cell Cell size in pixels.
     */
    SpatialGrid(int cell = 64) : cellSize(cell) {}

    /**
     * @brief Inserts a shape into all cells it occupies.
     * @param s Shape to insert.
     */
    void Add(CShape* s);

    /**
     * @brief Removes a shape from all cells it occupies.
     * @param s Shape to remove.
     */
    void Remove(CShape* s);

    /**
     * @brief Returns shapes located in the cell containing the point.
     * @param pt Query point.
     * @return Vector of shapes in the same cell.
     */
    std::vector<CShape*> Query(CPoint pt) const;

private:
    int cellSize;

    struct Cell {
        int x, y;
        bool operator==(const Cell& o) const { return x == o.x && y == o.y; }
    };

    struct Hash {
        size_t operator()(const Cell& c) const noexcept {
            return ((size_t)c.x << 32) ^ (size_t)c.y;
        }
    };

    std::unordered_map<Cell, std::vector<CShape*>, Hash> grid;
    std::unordered_map<CShape*, std::vector<Cell>> reverseIndex;

    /**
     * @brief Converts a screen point into a grid cell.
     */
    Cell ToCell(CPoint p) const { return { p.x / cellSize, p.y / cellSize }; }
};