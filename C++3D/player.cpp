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
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);

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
	//pos = ;


	//SetPos(CMotionParts::AllCollision(m_nMotionNum, GetPos(), m_OldPos));


	

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
			add.x -= sinf(rotY + D3DX_PI * 0.75f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * 0.75f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.75f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * -0.75f) * 5.0f;
		}
		else
		{
			add.x += sinf(rotY) * 5.0f;
			add.z += cosf(rotY) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_S))
	{//���L�[�������ꂽ
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.25f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * 0.25f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.25f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * -0.25f) * 5.0f;
		}
		else
		{
			add.x += sinf(rotY + D3DX_PI) * 5.0f;
			add.z += cosf(rotY + D3DX_PI) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_A))
	{//���L�[�������ꂽ
		add.x += sinf(rotY + D3DX_PI * -0.5f) * 5.0f;
		add.z += cosf(rotY + D3DX_PI * -0.5f) * 5.0f;
	}
	else if (pInput->Press(DIK_D))
	{//�E�L�[�������ꂽ
		add.x += sinf(rotY + D3DX_PI * 0.5f) * 5.0f;
		add.z += cosf(rotY + D3DX_PI * 0.5f) * 5.0f;
	}

	if (pInput->Trigger(DIK_SPACE))
	{
		m_Move.y += 100;
	}

	if (pInput->Press(DIK_Z))
	{
		AddRot(D3DXVECTOR3(0.0f, D3DXToRadian(-10), 0.0f));
	}
	else if (pInput->Press(DIK_X))
	{
		AddRot(D3DXVECTOR3(0.0f, D3DXToRadian(10), 0.0f));
	}

	m_Move.y -= 4.0f;

	m_Move.y += (0.0f - m_Move.y) * 0.1f;

	//OldPos�̍X�V
	m_OldPos = GetPos();


	AddPos(m_Move);

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

	if (pos.y < -100.0f)
	{
		SetPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));
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
	
	

	pos = CMotionParts::AllCollision(m_nMotionNum, GetPos(), m_OldPos);

	if (pos != GetPos())
	{
		m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	SetPos(pos);
	
	
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPlayer::Draw()
{

	//C3DObject::Draw();
}
