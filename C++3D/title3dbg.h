//=============================================================================
//
// title3dbg.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TITLE3DBG_H_			//このマクロ定義がされなかったら
#define _TITLE3DBG_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "3dbg.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class C3DObject;
class CRead;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle3DBG : public C3DBG
{
private:
	static const int MAX_3DBG_MODEL = 6;
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL_POS;
	static const D3DXVECTOR3 STANDARD_3DBG_MODEL_ROT;

	static const float DISTANCE;

public:
	CTitle3DBG();
	~CTitle3DBG() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C3DObject *m_pBgModel[MAX_3DBG_MODEL];
	D3DXVECTOR3 m_Rotation[MAX_3DBG_MODEL];		//自転
	D3DXVECTOR3 m_RotationMove[MAX_3DBG_MODEL];		//自転速度
	D3DXVECTOR3 m_Revolution[MAX_3DBG_MODEL];	//公転
	D3DXVECTOR3 m_RevolutionMove[MAX_3DBG_MODEL];	//公転速度
	float m_fScal[MAX_3DBG_MODEL];//惑星サイズ

	C3DObject *m_pBgGalaxy;

	CRead *m_pRead;
};

#endif