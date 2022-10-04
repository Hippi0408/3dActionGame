//=============================================================================
//
// result3dbg.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RESULT_3DBG_H_			//このマクロ定義がされなかったら
#define _RESULT_3DBG_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "3dbg.h"
#include "manager.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class C3DObject;
class CRead;
class C3DPolygon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult3DBG : public C3DBG
{
private:
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL;
public:
	CResult3DBG();
	~CResult3DBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C3DObject *m_pBgModel;
	D3DXVECTOR3 m_Rotation;		//自転
	D3DXVECTOR3 m_RotationMove;		//自転速度
	CRead *m_pRead;
	C3DPolygon *m_pBG;

};

#endif