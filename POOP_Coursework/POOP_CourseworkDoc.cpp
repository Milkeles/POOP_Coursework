
// POOP_CourseworkDoc.cpp : implementation of the CPOOPCourseworkDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "POOP_Coursework.h"
#endif

#include "POOP_CourseworkDoc.h"
#include "CTriangle.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPOOPCourseworkDoc

IMPLEMENT_DYNCREATE(CPOOPCourseworkDoc, CDocument)

BEGIN_MESSAGE_MAP(CPOOPCourseworkDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CPOOPCourseworkDoc::OnFileOpen)
END_MESSAGE_MAP()


// CPOOPCourseworkDoc construction/destruction

CPOOPCourseworkDoc::CPOOPCourseworkDoc() noexcept
{
	// TODO: add one-time construction code here

}

CPOOPCourseworkDoc::~CPOOPCourseworkDoc()
{
}

BOOL CPOOPCourseworkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// Add shape
void CPOOPCourseworkDoc::AddShape(CShape* s)
{
	shapes.push_back(s);
	grid.Add(s);
	SetModifiedFlag(1);
	UpdateAllViews(NULL);
}

// Remove Shape
void CPOOPCourseworkDoc::RemoveShape(CShape* s)
{
	grid.Remove(s);
	auto it = std::find(shapes.begin(), shapes.end(), s);
	if (it != shapes.end())
	{
		delete* it;
		shapes.erase(it);
		SetModifiedFlag(1);
		UpdateAllViews(NULL);
	}
}

// Delete everyting
void CPOOPCourseworkDoc::DeleteContents()
{
	for (CShape* p : shapes) delete p;
	shapes.clear();
	grid = SpatialGrid(64);
	CDocument::DeleteContents();
}


// CPOOPCourseworkDoc serialization

void CPOOPCourseworkDoc::Serialize(CArchive& ar)
{
	UINT count = (UINT)shapes.size();

	if (ar.IsStoring())
	{
		ar << count;
		for (CShape* sh : shapes)
		{
			CTriangle* triangle = (CTriangle*)sh;

			COLORREF col = triangle->getColor();
			POINT * points = triangle->getPoints();
			ar << col;

			for (int i = 0; i < 3; ++i)
			{
				ar << points[i].x;
				ar << points[i].y;
			}
		}
	}
	else
	{
		DeleteContents();
		ar >> count;
		shapes.reserve(count);
		for (UINT i = 0; i < count; ++i)
		{
			COLORREF col;
			ar >> col;

			POINT pts[3];
			for (int j = 0; j < 3; ++j)
			{
				ar >> pts[j].x;
				ar >> pts[j].y;
			}

			shapes.push_back(new CTriangle(pts, col));
			grid.Add(shapes.back());
		}
	}
	SetModifiedFlag(FALSE);
	UpdateAllViews(NULL);
}

BOOL CPOOPCourseworkDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return CDocument::OnOpenDocument(lpszPathName);
}

void CPOOPCourseworkDoc::OnFileOpen()
{
	CDocument::OnOpenDocument(NULL);
}
#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPOOPCourseworkDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPOOPCourseworkDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPOOPCourseworkDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS


// CPOOPCourseworkDoc diagnostics

#ifdef _DEBUG
void CPOOPCourseworkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPOOPCourseworkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPOOPCourseworkDoc commands
