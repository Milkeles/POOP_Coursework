/*
 * Implementation of CShape interface for a triangle shape object.
 * Dependencies:
 * - CShape.h - for the base interface.
 * - afxwin.h(from CShape.h) - for CDC and CPoint.
 *
 * Author: Hristo Hristov
 * 06.12.2025
 */

#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
private:
    POINT points[3];
    COLORREF color;
public:
    CTriangle(const POINT[3], COLORREF color = RGB(0, 0, 0));

    void setColor(COLORREF color) { this->color = color; }
    COLORREF getColor() { return color; }
    POINT* getPoints() { return points; }

    void Draw(CDC* pDC) const override;
    /**
     * Tests whether the triangle is considered hit by a mouse click.
     *
     * @param pos       Click position in device coordinates (pixels).
     * @param threshold Maximum distance (pixels) from a vertex that counts as a hit.
     * @return          true  – click is inside or within \a threshold px of a vertex
     *                  false – click is outside the tolerance area.
     */
    bool IsColliding(POINT pos, int threshold) const override;

    CRect GetBounds() const override;
};