#pragma once
#include "CTriangle.h"
#include "Command.h"
#include "POOP_CourseworkDoc.h"

class AddTriangleCommand : public Command {
private:
    CPOOPCourseworkDoc* doc;
    POINT               pts[3];
    COLORREF            color;

public:
    AddTriangleCommand(CPOOPCourseworkDoc* pDoc,
                       const POINT pts2[3],
                       COLORREF col = RGB(0, 0, 0))
                       : doc(pDoc), color(col) {
        for (int i = 0; i < 3; ++i) pts[i] = pts2[i];
    }

    void Execute() override {
        doc->AddShape(new CTriangle(pts, color));
    }
};

class RemoveTriangleCommand : public Command {
private:
    CPOOPCourseworkDoc* doc;
    CShape* shape;
public:
    RemoveTriangleCommand(CPOOPCourseworkDoc* pDoc, CShape* sh) : doc(pDoc), shape(sh) {}

    void Execute() override {
        doc->RemoveShape(shape);
    }
};