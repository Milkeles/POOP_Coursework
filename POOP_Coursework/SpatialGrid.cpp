#include "pch.h"
#include "SpatialGrid.h"

void SpatialGrid::Add(CShape* s)
{
    CRect rc = s->GetBounds();

    Cell cMin = ToCell(rc.TopLeft());
    Cell cMax = ToCell(rc.BottomRight());

    std::vector<Cell> cells;
    for (int y = cMin.y; y <= cMax.y; ++y)
        for (int x = cMin.x; x <= cMax.x; ++x)
            cells.push_back({ x, y });

    for (const Cell& c : cells) grid[c].push_back(s);
    reverseIndex[s] = cells;
}

void SpatialGrid::Remove(CShape* s) {
    auto it = reverseIndex.find(s);
    if (it == reverseIndex.end()) return;

    for (auto& c : it->second) {
        auto& v = grid[c];
        v.erase(std::remove(v.begin(), v.end(), s), v.end());
    }

    reverseIndex.erase(s);
}

std::vector<CShape*> SpatialGrid::Query(CPoint pt) const {
    Cell c = ToCell(pt);

    std::vector<CShape*> out;

    auto it = grid.find(c);
    if (it != grid.end())
        out = it->second;

    return out;
}
