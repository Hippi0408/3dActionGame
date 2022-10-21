//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "motion_parts.h"

const D3DXVECTOR3 CMotionParts::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CMotionParts *CMotionParts::m_pMotionPartsTop = nullptr;
CMotionParts *CMotionParts::m_pMotionPartsCurrent = nullptr;
int CMotionParts::m_nModelMax = 0;
int CMotionParts::m_MotionPlayMotonNum[MAX_MOTION_ALL] = {};
int CMotionParts::m_MotionPlayKeyNum[MAX_KEY] = {};
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CMotionParts::CMotionParts()
{

	m_nModelNum = m_nModelMax;
	m_nKeyNum = 0;

	m_pRarent = nullptr;

	if (m_pMotionPartsTop == nullptr)
	{
		m_pMotionPartsTop = this;
	}

	m_pNextMotionParts = nullptr;

	m_pLastTimeMotionParts = GetCurrentMotionParts();

	if (m_pLastTimeMotionParts != nullptr)
	{
		m_pLastTimeMotionParts->SetNextMotionParts(this);

	}
	SetCurrentMotionParts(this);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CMotionParts::~CMotionParts()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CMotionParts::Init()
{

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CMotionParts::Uninit()
{

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CMotionParts::Update()
{
	


}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CMotionParts::Draw()
{
	C3DObject::Draw();
}

//*****************************************************************************
//	�I����������
//*****************************************************************************
bool CMotionParts::IsUnused()
{
	return false;
}

//*****************************************************************************
//	���[�V�����ԍ��w��ŃZ�b�g����
//*****************************************************************************
void CMotionParts::SetMotion(int nMotionNum)
{
	m_MotionPlayKeyNum[m_nModelObjNum] = 0;
	D3DXVECTOR3 rot = m_MotionKey[nMotionNum].aKey[m_MotionPlayKeyNum[m_nModelObjNum]].rot;

	SetRot(rot);
}

//*****************************************************************************
// ALL�I������
//*****************************************************************************
void CMotionParts::ALLUninit()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		CMotionParts* pMotionPartsNext = pMotionParts->GetNextMotionParts();
		pMotionParts->Uninit();
		pMotionParts = pMotionPartsNext;
	}
}

//*****************************************************************************
// ALL�X�V����
//*****************************************************************************
void CMotionParts::ALLUpdate()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		pMotionParts->Update();

		if (pMotionParts->IsUnused())
		{
			CMotionParts* pMotionPartsBreak = pMotionParts;
			pMotionParts = pMotionPartsBreak->GetNextMotionParts();
			pMotionPartsBreak->Uninit();
		}
		else
		{
			pMotionParts = pMotionParts->GetNextMotionParts();
		}
	}
}

//*****************************************************************************
// ALL�`�揈��
//*****************************************************************************
void CMotionParts::ALLDraw()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		pMotionParts->Draw();
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}