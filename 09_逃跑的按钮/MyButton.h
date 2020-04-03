#pragma once


// MyButton

class MyButton : public CButton
{
	DECLARE_DYNAMIC(MyButton)

public:
	MyButton();
	virtual ~MyButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void Wh(int w, int h)
	{
		m_h = h;
		m_w = w;
	}

private :
	int m_h;
	int m_w;
};


