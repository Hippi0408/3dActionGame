//=============================================================================
//
// [shadow.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "shadow.h"
#include "manager.h"
#include "texture.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CShadow::CShadow()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CShadow::~CShadow()
{
}

//*****************************************************************************
// �`��
//*****************************************************************************
void CShadow::Draw()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//���u�����f�B���O�����Z�����ɐݒ�
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	C3DPolygon::Draw();

	//���u�����f�B���O�����̖߂�
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}