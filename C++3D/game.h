//=============================================================================
//
// game.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME_H_			//このマクロ定義がされなかったら
#define _GAME_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CCamera;
class CLight;
class C3DPolygon;
class CMeshfield;
class CPlayer;
class CBillcoard;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame : public CObject
{
private:
	
public:
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	CCamera* GetCamera() { return m_pCamera; }
	CMeshfield* GetMeshfield() { return m_pMeshfieldBG; }
private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	C3DPolygon* m_pBG;
	CMeshfield* m_pMeshfieldBG;
	CPlayer* m_pPlayer;
	CBillcoard* m_pBillcoard;
};

#endif