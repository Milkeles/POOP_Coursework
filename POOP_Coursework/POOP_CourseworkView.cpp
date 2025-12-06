
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


// CPOOPCourseworkView

IMPLEMENT_DYNCREATE(CPOOPCourseworkView, CView)

BEGIN_MESSAGE_MAP(CPOOPCourseworkView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
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
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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
#endif //_DEBUG


// CPOOPCourseworkView message handlers
