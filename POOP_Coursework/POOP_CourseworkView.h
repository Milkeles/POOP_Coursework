
// POOP_CourseworkView.h : interface of the CPOOPCourseworkView class
//

#pragma once


class CPOOPCourseworkView : public CView
{
protected: // create from serialization only
	CPOOPCourseworkView() noexcept;
	DECLARE_DYNCREATE(CPOOPCourseworkView)

// Attributes
public:
	CPOOPCourseworkDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CPOOPCourseworkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		void DeleteTriangleAt(CPoint pos);
	void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in POOP_CourseworkView.cpp
inline CPOOPCourseworkDoc* CPOOPCourseworkView::GetDocument() const
   { return reinterpret_cast<CPOOPCourseworkDoc*>(m_pDocument); }
#endif

