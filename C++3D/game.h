//=============================================================================
//
// game.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME_H_			//���̃}�N����`������Ȃ�������
#define _GAME_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CCamera;
class CLight;
class C3DPolygon;
class CPlayer;
class CBillcoard;

//*****************************************************************************
// �N���X��`
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
private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	C3DPolygon* m_pBG;
	CPlayer* m_pPlayer;
	CBillcoard* m_pBillcoard;
};

#endif