//=============================================================================
//
// title.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TITLE_H_			//このマクロ定義がされなかったら
#define _TITLE_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;
class C3DPolygon;
class CCamera;
class CLight;
class CRead;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle : public CObject
{
private:

public:
	CTitle();
	~CTitle() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CUI *m_pUi;
	CCamera *m_pCamera;
	CLight *m_pLight;
	CRead *m_pRead;
	C3DPolygon *m_pBG;
};

#endif