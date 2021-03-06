
// MFC_TeamProjectView.cpp: CMFCTeamProjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_TeamProject.h"
#endif

#include "MFC_TeamProjectDoc.h"
#include "MFC_TeamProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTeamProjectView

IMPLEMENT_DYNCREATE(CMFCTeamProjectView, CView)

BEGIN_MESSAGE_MAP(CMFCTeamProjectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_LINE, &CMFCTeamProjectView::OnLine)
	ON_COMMAND(ID_ELLIPES, &CMFCTeamProjectView::OnEllipes)
	ON_COMMAND(ID_RECTANGLE, &CMFCTeamProjectView::OnRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_COMMAND(ID_TEXTBOX, &CMFCTeamProjectView::OnTextbox)
END_MESSAGE_MAP()

// CMFCTeamProjectView 생성/소멸

CMFCTeamProjectView::CMFCTeamProjectView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCTeamProjectView::~CMFCTeamProjectView()
{
}

BOOL CMFCTeamProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCTeamProjectView 그리기

void CMFCTeamProjectView::OnDraw(CDC* pDC)
{
	CMFCTeamProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	switch (m_GrapghicObj.m_kind)

	{
	case LINE:
		pDC->MoveTo(m_GrapghicObj.m_ptStart);
		pDC->LineTo(m_GrapghicObj.m_ptEnd);
		break;

	case ELLIPES:
		pDC->Ellipse(m_GrapghicObj.m_ptStart.x, m_GrapghicObj.m_ptStart.y, m_GrapghicObj.m_ptEnd.x, m_GrapghicObj.m_ptEnd.y );
		break;

	case RECTANGLE:
		pDC->Rectangle(m_GrapghicObj.m_ptStart.x, m_GrapghicObj.m_ptStart.y, m_GrapghicObj.m_ptEnd.x, m_GrapghicObj.m_ptEnd.y);
		break;

	case TEXTBOX: 
		CRect rt = CRect(m_GrapghicObj.m_ptStart, m_GrapghicObj.m_ptEnd);

		if (m_GrapghicObj.m_strText.IsEmpty())
			pDC->SelectObject(GetStockObject(LTGRAY_BRUSH));
		pDC->Rectangle(&rt);
		if (!m_GrapghicObj.m_strText.IsEmpty())
			pDC->DrawText(m_GrapghicObj.m_strText, &rt, DT_TOP | DT_LEFT);

	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCTeamProjectView 인쇄

BOOL CMFCTeamProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCTeamProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCTeamProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCTeamProjectView 진단

#ifdef _DEBUG
void CMFCTeamProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTeamProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTeamProjectDoc* CMFCTeamProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTeamProjectDoc)));
	return (CMFCTeamProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTeamProjectView 메시지 처리기


void CMFCTeamProjectView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_GrapghicObj.m_kind = LINE;

}


void CMFCTeamProjectView::OnEllipes()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_GrapghicObj.m_kind = ELLIPES;
}


void CMFCTeamProjectView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_GrapghicObj.m_kind = RECTANGLE;
}


void CMFCTeamProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_GrapghicObj.m_ptStart = point; //시작 좌표 저장

	CView::OnLButtonDown(nFlags, point);
}


void CMFCTeamProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (MK_LBUTTON & nFlags)
	{
		m_GrapghicObj.m_ptEnd = point;
		Invalidate();
		//마우스의 이동의 상태와 마우스 위치를 저장
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCTeamProjectView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_GrapghicObj.m_strText.AppendChar(nChar);
	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFCTeamProjectView::OnTextbox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_GrapghicObj.m_kind = TEXTBOX;

}
