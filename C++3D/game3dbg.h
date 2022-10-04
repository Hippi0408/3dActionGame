//=============================================================================
//
// game3dbg.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME3DBG_H_			//このマクロ定義がされなかったら
#define _GAME3DBG_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "3dbg.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class C3DObject;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame3DBG : public C3DBG
{
private:
	static const int Z_MAX_3DBG_MODEL = 6;
	static const int X_MAX_3DBG_MODEL = 3;
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL;

public:
	CGame3DBG();
	~CGame3DBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C3DObject *m_pBgModel[X_MAX_3DBG_MODEL][Z_MAX_3DBG_MODEL];
	D3DXVECTOR3 m_BgObjSize;
	D3DXVECTOR3 m_Move;
};

#endif