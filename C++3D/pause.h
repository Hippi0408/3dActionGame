//=============================================================================
//
// pause.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PAUSE_H_			//このマクロ定義がされなかったら
#define _PAUSE_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class C2DPolygon;
class CUI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPause : public CObject
{
private:
	static const int MAX_PAUSE = 4;
	static const float SIZE_PAUSE_UI; 
	static const float SIZE_PAUSE_UI_HALF;

public:
	CPause();
	~CPause() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetPause(bool bUse) { m_bPause = bUse; }
	bool GetPause() { return m_bPause; }
	
private:
	bool m_bPause;
	int m_nMood;

	C2DPolygon *m_pUi;
	CUI *m_pBg;
};

#endif