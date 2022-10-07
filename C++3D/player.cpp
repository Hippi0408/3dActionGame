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
#include "shadow.h"
#include "texture.h"

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
	ModelPattern modelPattern;

	ZeroMemory(&modelPattern,sizeof(modelPattern));

	cRead.ReadXFile("data/MODEL/���l02.x", &modelPattern);
	SetModel(&modelPattern);

	m_pShadow = new CShadow;

	if (FAILED(m_pShadow->Init()))
	{
		return -1;
	}
	int nIndex = CTexture::LoadTexture("data/TEXTURE/effect.jpg");
	m_pShadow->SetPos(D3DXVECTOR3(0.0f, 3.0f, 0.0f));
	m_pShadow->SetRot(D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0)));
	m_pShadow->SetTextIndex(nIndex);
	m_pShadow->SetDiagonalLine(25.0f, 25.0f);
	m_pShadow->SetPolygon();



	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPlayer::Uninit()
{
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		delete m_pShadow;
		m_pShadow = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPlayer::Update()
{


	CInput *pInput = CInput::GetKey();

	if (pInput->Press(DIK_W))
	{
		AddPos(D3DXVECTOR3(0.0f,0.0f,10.0f));
	}
	else if (pInput->Press(DIK_S))
	{
		AddPos(D3DXVECTOR3(0.0f, 0.0f, -10.0f));
	}

	if (pInput->Press(DIK_A))
	{
		AddPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(DIK_D))
	{
		AddPos(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
	}

	D3DXVECTOR3 pos = GetPos();

	pos.y = 3.0f;

	m_pShadow->SetPos(pos);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPlayer::Draw()
{
	m_pShadow->Draw();

	C3DObject::Draw();
}
