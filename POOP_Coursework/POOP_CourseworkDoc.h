
// POOP_CourseworkDoc.h : interface of the CPOOPCourseworkDoc class
//
#include "SpatialGrid.h"
#include "CShape.h"

#pragma once


class CPOOPCourseworkDoc : public CDocument
{
protected: // create from serialization only
	CPOOPCourseworkDoc() noexcept;
	DECLARE_DYNCREATE(CPOOPCourseworkDoc)
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName) override;
	void OnFileOpen();
// Attributes
public:
	std::vector<CShape*> shapes;
	SpatialGrid grid;

// Operations
public:
	void AddShape(CShape* s);
	void RemoveShape(CShape* s);
	virtual void DeleteContents();
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPOOPCourseworkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
