/* Implementation of the triangle class.
* Author: Hristo Hristov
* 07.12.2025
*/
#include "pch.h"
#include "CTriangle.h"
#include <iostream>

CTriangle::CTriangle(const POINT points[3], COLORREF color) {
    if (color == RGB(0, 0, 0))
        this->color = RGB(rand() % 256, rand() % 256, rand() % 256);
    else
        this->color = color;

	for (int i = 0; i < 3; ++i)
		this->points[i] = points[i];
}

void CTriangle::Draw(CDC* pDC) const {
	CBrush* oldBrush = pDC->GetCurrentBrush();
	CBrush newBrush(color);
   

	pDC->SelectObject(&newBrush);

	pDC->Polygon(points, sizeof(points) / sizeof(POINT));

	pDC->SelectObject(oldBrush);
}

bool CTriangle::IsColliding(POINT clickPos, int threshold) const
{
    long th2 = (long)(threshold * threshold);
    for (int i = 0; i < 3; ++i)
    {
        long dx = points[i].x - clickPos.x;
        long dy = points[i].y - clickPos.y;
        if (dx * dx + dy * dy <= th2)
            return true;
    }

    return false;
}

CRect CTriangle::GetBounds() const
{
    LONG minX = points[0].x, maxX = minX;
    LONG minY = points[0].y, maxY = minY;
    for (int i = 1; i < 3; ++i)
    {
        if (minX > points[i].x) minX = points[i].x;
        if (maxX < points[i].x) maxX = points[i].x;
        if (minY > points[i].y) minY = points[i].y;
        if (maxY < points[i].y) maxY = points[i].y;
    }
    return CRect(CPoint(minX, minY), CPoint(maxX, maxY));
}