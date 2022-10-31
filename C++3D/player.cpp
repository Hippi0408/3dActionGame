//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "player.h"
#include "input.h"
#include "read.h"
#include "texture.h"
#include "game.h"
#include "camera.h"
#include "meshfield.h"
#include "motion_parts.h"

const D3DXVECTOR3 CPlayer::INIT_POS = D3DXVECTOR3(0.0f,0.0f,0.0f);
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPlayer::CPlayer()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CPlayer::Init()
{
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}

	SetPos(INIT_POS);

	CRead cRead;
	
	cRead.ReadXFile("data/MODEL/箱人02.x");
	
	m_nMotionNum = cRead.ReadMotion("data/MOTION/motionplayer.txt");

	CMotionParts::SetLight(m_Light, m_nMotionNum);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPlayer::Uninit()
{
	
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPlayer::Update()
{
	CInput *pInput = CInput::GetKey();
	CManager *pManager = GetManager();

	CGame* pGame = (CGame*)pManager->GetGameObject();

	float rotY = pGame->GetCamera()->GetRot();

	D3DXVECTOR3 add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点移動
	if (pInput->Press(DIK_W))
	{//上キーが押された
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.75f);
			add.z -= cosf(rotY + D3DX_PI * 0.75f);
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.75f);
			add.z -= cosf(rotY + D3DX_PI * -0.75f);
		}
		else
		{
			add.x += sinf(rotY);
			add.z += cosf(rotY);
		}
	}
	else if (pInput->Press(DIK_S))
	{//下キーが押された
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.25f);
			add.z -= cosf(rotY + D3DX_PI * 0.25f);
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.25f);
			add.z -= cosf(rotY + D3DX_PI * -0.25f);
		}
		else
		{
			add.x += sinf(rotY + D3DX_PI);
			add.z += cosf(rotY + D3DX_PI);
		}
	}
	else if (pInput->Press(DIK_A))
	{//左キーが押された
		add.x += sinf(rotY + D3DX_PI * -0.5f);
		add.z += cosf(rotY + D3DX_PI * -0.5f);
	}
	else if (pInput->Press(DIK_D))
	{//右キーが押された
		add.x += sinf(rotY + D3DX_PI * 0.5f);
		add.z += cosf(rotY + D3DX_PI * 0.5f);
	}

	if (pInput->Trigger(DIK_SPACE))
	{
		AddPos(D3DXVECTOR3(0.0f,100.0f,0.0f));
	}

	if (pInput->Press(DIK_Z))
	{
		AddRot(D3DXVECTOR3(0.0f, D3DXToRadian(-10), 0.0f));
	}
	else if (pInput->Press(DIK_X))
	{
		AddRot(D3DXVECTOR3(0.0f, D3DXToRadian(10), 0.0f));
	}

	AddPos(add * 5.0f);

	add.y = -4.0f;

	AddPos(add);

	D3DXVECTOR3 pos, groundpos;

	pos = GetPos();

	groundpos = pGame->GetMeshfield()->Collision(pos);

	if (pos.y < groundpos.y)
	{
		if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			SetPos(groundpos);
		}
	}

	if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		CMotionParts::AllSetShadowPos(groundpos, m_nMotionNum);
	}

	if (pInput->Press(KEY_MOVE) || pInput->Press(DIK_0))
	{
		CMotionParts::MoveMotionModel(GetPos(), GetRot(), m_nMotionNum,1);
	}
	else
	{
		CMotionParts::MoveMotionModel(GetPos(), GetRot(), m_nMotionNum,0);
	}
	
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPlayer::Draw()
{

	//C3DObject::Draw();
}
