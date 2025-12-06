
// POOP_CourseworkView.cpp : implementation of the CPOOPCourseworkView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "POOP_Coursework.h"
#endif

#include "POOP_CourseworkDoc.h"
#include "POOP_CourseworkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CTriangle.h"
#include "Commands.h"

// CPOOPCourseworkView

IMPLEMENT_DYNCREATE(CPOOPCourseworkView, CView)

BEGIN_MESSAGE_MAP(CPOOPCourseworkView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CPOOPCourseworkView construction/destruction

CPOOPCourseworkView::CPOOPCourseworkView() noexcept
{
	// TODO: add construction code here

}

CPOOPCourseworkView::~CPOOPCourseworkView()
{
}

BOOL CPOOPCourseworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPOOPCourseworkView drawing

void CPOOPCourseworkView::OnDraw(CDC* pDC)
{
    CPOOPCourseworkDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    for (CShape* sh : pDoc->shapes)
        sh->Draw(pDC);
}
void CPOOPCourseworkView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPOOPCourseworkView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPOOPCourseworkView diagnostics

#ifdef _DEBUG
void CPOOPCourseworkView::AssertValid() const
{
	CView::AssertValid();
}

void CPOOPCourseworkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPOOPCourseworkDoc* CPOOPCourseworkView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPOOPCourseworkDoc)));
	return (CPOOPCourseworkDoc*)m_pDocument;
}

void CPOOPCourseworkView::DeleteTriangleAt(CPoint pos) {
    CPOOPCourseworkDoc* pDoc = GetDocument();

    SpatialGrid& grid = pDoc->grid;
    for (CShape* shape : grid.Query(pos)) {
        if (shape->IsColliding(pos))
        {
            RemoveTriangleCommand cmd(GetDocument(), shape);
            cmd.Execute();
            return;
        }
    }
}

#endif


// CPOOPCourseworkView message handlers
void CPOOPCourseworkView::OnRButtonDown(UINT nFlags, CPoint point)
{
    DeleteTriangleAt(point);
    CView::OnRButtonDown(nFlags, point);
}

void CPOOPCourseworkView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (nFlags & MK_CONTROL) // CTRL + LMB
    {
        DeleteTriangleAt(point);
    }
    else
    {
        static struct { int n; POINT p[3]; } buf = { 0 };
        buf.p[buf.n++] = point;
        if (buf.n == 3)
        {
            AddTriangleCommand add(GetDocument(), buf.p);
            add.Execute();
            buf.n = 0;
        }
    }

    CView::OnLButtonDown(nFlags, point);
}