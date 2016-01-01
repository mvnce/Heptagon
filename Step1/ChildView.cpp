
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Step1.h"
#include "ChildView.h"
#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const double DegToRad = 57.295779513082320;

// CChildView

CChildView::CChildView()
{
	m_centerx = 0.5;
	m_centery = 0.5;
	m_length = 0.3;
	m_angle = 0;
	
	Point p0, p1, p2, p3, p4, p5, p6,
		r1 ,r2, r3, r4;

	// put points of heptagon in points list
	m_points.push_back(p0);
	m_points.push_back(p1);
	m_points.push_back(p2);
	m_points.push_back(p3); 
	m_points.push_back(p4); 
	m_points.push_back(p5); 
	m_points.push_back(p6);

	// put points of rectangle in points list
	m_points.push_back(r1);
	m_points.push_back(r2);
	m_points.push_back(r3);
	m_points.push_back(r4);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_STEPSTUFF_PROPERTIES, &CChildView::OnStepstuffProperties)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}


void CChildView::OnGLDraw(CDC* pDC)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int width, height;
	GetSize(width, height);

	// Simple rectangle example
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,   // left
		1.0,   // right
		0.0,   // bottom
		1.0,   // top
		-1.0,  // near
		1.0);  // far
	// glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_radius = (1 / sin(180 / DegToRad / 7))*0.5*m_length; /// Get the radius from original circle

	// get the initial point
	m_points[0].x = m_centerx - sin((180 / DegToRad / 7) - m_angle / DegToRad) * m_radius;
	m_points[0].y = m_centery - cos((180 / DegToRad / 7) - m_angle / DegToRad) * m_radius;

	// Get the following 6 points
	for (int i = 1; i <= 6; i++)
	{
		m_points[i].x = m_centerx - sin((180 / DegToRad / 7) - m_angle / DegToRad - i * (360 / 7 / DegToRad)) * m_radius;
		m_points[i].y = m_centery - cos((180 / DegToRad / 7) - m_angle / DegToRad - i * (360 / 7 / DegToRad)) * m_radius;
	}

	// Get the low angle and high angle
	if (m_firstDraw)
	{
		m_loAngle = 46.532 / DegToRad;
		//m_loAngle = 90 / DegToRad - atan(((m_points[2].x - m_points[6].x) / 2) / (tan((90-360 / 14) / DegToRad) * (m_length / 2)));
		m_hiAngle = 90 / DegToRad - atan( m_radius / ((m_points[2].x - m_points[6].x) / 2));
		m_firstDraw = false;
	}

	double lenlo = 1 / cos(m_loAngle) * (tan((90-360 / 14) / DegToRad) * (m_length / 2));
	double lenhi = 1 / cos(m_hiAngle) * m_radius;

	m_points[7].x = m_centerx - sin(m_loAngle - m_angle / DegToRad) * lenlo;
	m_points[7].y = m_centery - cos(m_loAngle - m_angle / DegToRad) * lenlo + 0.008;

	m_points[8].x = m_centerx - sin(-m_loAngle - m_angle / DegToRad) * lenlo;
	m_points[8].y = m_centery - cos(-m_loAngle - m_angle / DegToRad) * lenlo + 0.008;

	m_points[9].x = m_centerx + sin(m_hiAngle - m_angle / DegToRad) * lenhi;
	m_points[9].y = m_centery + cos(m_hiAngle - m_angle / DegToRad) * lenhi;

	m_points[10].x = m_centerx + sin(-m_hiAngle - m_angle / DegToRad) * lenhi;
	m_points[10].y = m_centery + cos(-m_hiAngle - m_angle / DegToRad) * lenhi;

	glColor3d(0.0, 0.0, 1.0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2d(m_points[7].x, m_points[7].y);
	glVertex2d(m_points[8].x, m_points[8].y);
	glVertex2d(m_points[9].x, m_points[9].y);
	glVertex2d(m_points[10].x, m_points[10].y);
	glEnd();

	// Draw the heptagon
	glColor3d(1., 0., 0.);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 6; i++)
	{
		glVertex2d(m_points[i].x, m_points[i].y);
	}
	glVertex2d(m_points[0].x, m_points[0].y);
	glEnd();

	glColor3d(0., 1., 0.);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for (int j = 7; j <= 10; j++)
	{
		glVertex2d(m_points[j].x, m_points[j].y);
	}
	glVertex2d(m_points[7].x, m_points[7].y);
	glEnd();
}


void CChildView::OnStepstuffProperties()
{
	CPropDlg dlg;

	dlg.m_centerx = m_centerx;
	dlg.m_centery = m_centery;
	dlg.m_length = m_length;
	dlg.m_angle = m_angle;

	if (dlg.DoModal() == IDOK)
	{
		m_centerx = dlg.m_centerx;
		m_centery = dlg.m_centery;
		m_length = dlg.m_length;
		m_angle += dlg.m_angle;

		Invalidate();
	}
}
