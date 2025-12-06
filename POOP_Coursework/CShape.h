/*
 * Base class for the shapes.
 * Dependencies:
 * - afxwin.h - for CDC and CPoint.
 *
 * Author: Hristo Hristov
 * 06.12.2025
 */
#pragma once
#include <afxwin.h>

class CShape {
public:
	virtual void Draw(CDC* pDC) const = 0;
	virtual bool IsColliding(POINT pos, int threshold = 3) const = 0;
	virtual CRect GetBounds() const = 0;
	virtual ~CShape() = default;
};

