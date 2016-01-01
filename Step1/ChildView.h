
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"

#include <vector>


// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnGLDraw(CDC* pDC);

private:
	double m_centerx;
	double m_centery;
	double m_length;
	double m_angle;
	double m_radius = 0;

	double m_loAngle = 0;
	double m_hiAngle = 0;
	bool m_firstDraw = true;

	struct Point{double x; double y;};
	std::vector<Point> m_points;

public:
	afx_msg void OnStepstuffProperties();
};

