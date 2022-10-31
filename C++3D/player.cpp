//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
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
// �R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CPlayer::Init()
{
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}

	SetPos(INIT_POS);

	CRead cRead;
	
	cRead.ReadXFile("data/MODEL/���l02.x");
	
	m_nMotionNum = cRead.ReadMotion("data/MOTION/motionplayer.txt");

	CMotionParts::SetLight(m_Light, m_nMotionNum);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPlayer::Uninit()
{
	
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPlayer::Update()
{
	CInput *pInput = CInput::GetKey();
	CManager *pManager = GetManager();

	CGame* pGame = (CGame*)pManager->GetGameObject();

	float rotY = pGame->GetCamera()->GetRot();

	D3DXVECTOR3 add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�ړ�
	if (pInput->Press(DIK_W))
	{//��L�[�������ꂽ
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
	{//���L�[�������ꂽ
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
	{//���L�[�������ꂽ
		add.x += sinf(rotY + D3DX_PI * -0.5f);
		add.z += cosf(rotY + D3DX_PI * -0.5f);
	}
	else if (pInput->Press(DIK_D))
	{//�E�L�[�������ꂽ
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
// �`�揈��
//*****************************************************************************
void CPlayer::Draw()
{

	//C3DObject::Draw();
}
