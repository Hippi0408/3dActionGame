//=============================================================================
//
// player.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PLAYER_H_			//このマクロ定義がされなかったら
#define _PLAYER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "3dobject.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CShadow;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public C3DObject
{
private:
	static const D3DXVECTOR3 INIT_POS;
public:
	CPlayer();
	~CPlayer() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLight(D3DXVECTOR3 vec) { m_Light = vec; }

private:
	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_OldPos;
	int m_nMotionNum;
	D3DXVECTOR3 m_Light;
};

#endif