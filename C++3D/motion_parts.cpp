//=============================================================================
//
// motion_parts.cpp
// Author : kozuna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "motion_parts.h"
#include "manager.h"
#include <assert.h>

const D3DXVECTOR3 CMotionParts::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CMotionParts *CMotionParts::m_pMotionPartsTop = nullptr;
CMotionParts *CMotionParts::m_pMotionPartsCurrent = nullptr;
int CMotionParts::m_nModelMax = 0;
int CMotionParts::m_MotionPlayMotonNum[MAX_MOTION_ALL] = {};
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CMotionParts::CMotionParts()
{
	m_nFrame = 0;
	m_nKey = 0;
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

	m_nModelObjNum = m_nModelMax;
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
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}

	SetPos(INIT_POS);
	SetMotion(0);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CMotionParts::Uninit()
{
	if (m_pMotionPartsTop == this)
	{
		m_pMotionPartsTop = m_pNextMotionParts;
	}

	if (m_pMotionPartsCurrent == this)
	{
		m_pMotionPartsCurrent = m_pLastTimeMotionParts;
	}

	if (m_pLastTimeMotionParts != nullptr)
	{
		m_pLastTimeMotionParts->SetNextMotionParts(m_pNextMotionParts);
	}

	if (m_pNextMotionParts != nullptr)
	{
		m_pNextMotionParts->SetLastTimeMotionParts(m_pLastTimeMotionParts);
	}

	C3DObject::Uninit();

	delete this;
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CMotionParts::Update()
{
	// �ړI�̃t���[��
	int nObjectiveFrame = m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].nFrame[m_nKey];

	// �ړI�̃t���[���@���@���݂̃t���[��
	if (nObjectiveFrame < m_nFrame)
	{
		// ���̈ʒu�܂ł̌v�Z
		NextMotionPosition();
	}

	// rot�̉��Z
	AddRot(m_RotMove);
	// �t���[���̉��Z
	m_nFrame++;
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CMotionParts::Draw()
{
	D3DXMATRIX mtxRarent;
	D3DXMATRIX mtx;
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();
	// �e�����݂���ꍇ
	if (m_pRarent != nullptr)
	{
		mtxRarent = m_pRarent->GetMatrix();
		SetPos(m_pRarent->GetWorldPos());
		SetRot(m_pRarent->GetRot());
	}
	else
	{
		pD3DDevice->GetTransform(D3DTS_WORLD, &mtxRarent);
	}

	mtx = GetMatrix();

	//���f���̃}�g���b�N�X�@���@�e�̃��[���h�}�g���b�N�X
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRarent);

	SetMatrix(mtx);

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
	m_nFrame = 0;
	m_nKey = 0;
	D3DXVECTOR3 rot = m_MotionKey[nMotionNum].aKey[m_nKey].rot;
	SetRot(rot);
}

//*****************************************************************************
// ���̈ʒu�܂ł̌v�Z
//*****************************************************************************
void CMotionParts::NextMotionPosition()
{
	//���݂�KEY���ړI�𒴂�����
	if (m_nKey > m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].nKeyMax)
	{
		m_nKey = 0;
	}

	//���̌���
	D3DXVECTOR3 nowRot = GetRot();
	//���̌���
	D3DXVECTOR3 nextRot = m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].aKey[m_nKey + 1].rot;
	//�S�̃t���[�����ɑ΂��Ă̊���
	float fFrameRatio = (float)100.0f / m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].nFrame[m_nKey + 1];

	//1�t���[��������̓�����
	D3DXVECTOR3 rotMove;
	rotMove = (nextRot - nowRot) / fFrameRatio;
	m_RotMove = rotMove;
	m_nKey++;
}

//*****************************************************************************
// �����Ƃ̈�v�����邩�ǂ���
//*****************************************************************************
bool CMotionParts::GetMotionParts(int nMotionNum, int nPartsNum)
{
	if (m_nModelObjNum == nMotionNum
		&& m_nPartsNum == nPartsNum)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// �����Ƃ̈�v�����邩�ǂ���
//*****************************************************************************
bool CMotionParts::GetMotionParts(int nMotionNum)
{
	if (m_nModelObjNum == nMotionNum)
	{
		return true;
	}

	return false;
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

//*****************************************************************************
// ����OBJ�̐���
//*****************************************************************************
int CMotionParts::CreateMotionObj(MotionData* pMotionData, int nPartsMax)
{

	for (int nCnt = 0; nCnt < nPartsMax; nCnt++)
	{
		CMotionParts* pMotionParts = new CMotionParts;

		if (FAILED(pMotionParts->Init()))
		{
			assert(false);
		}

		pMotionParts->SetPartsNum(nCnt);//��̃��[�V�����̒��̔ԍ�
		pMotionParts->SetModelPattnNum(pMotionData[nCnt].nModelPattern);//�g�p���郂�f���̃C���f�b�N�X
		pMotionParts->SetChildrenPos(pMotionData[nCnt].pos);//���f���̈ʒu
		pMotionParts->SetRot(pMotionData[nCnt].rot);//���f���̌���
		
		if (pMotionData[nCnt].nParentNum >= 0)
		{
			//�e�̐ݒ�
			pMotionParts->SetMotionRarent(GetMotionPartsPointer(m_nModelMax, pMotionData[nCnt].nParentNum));
		}
		
	}

	int nModelNum = m_nModelMax;

	//�������̂̓o�^����
	SettingCompletion();

	return nModelNum;

}

//*****************************************************************************
// �����ɍ����|�C���^��Ԃ�
//*****************************************************************************
CMotionParts * CMotionParts::GetMotionPartsPointer(int nMotionNum, int nPartsNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum, nPartsNum))
		{
			return pMotionParts;
		}

		pMotionParts = pMotionParts->GetNextMotionParts();
	}


	assert(false);
	return nullptr;
}

//*****************************************************************************
//���[�V�������f���̈ړ�
//*****************************************************************************
void CMotionParts::MoveMotionModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nMotionNum)
{
	GetMotionPartsPointer(nMotionNum, 0)->SetPos(pos);
	GetMotionPartsPointer(nMotionNum, 0)->SetRot(rot);
}

//*****************************************************************************
//���[�V�������f���̃��C�g�x�N�g��
//*****************************************************************************
void CMotionParts::SetLight(D3DXVECTOR3 vec, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			pMotionParts->SetLightVec(vec);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
//�e�̐ݒ�
//*****************************************************************************
void CMotionParts::AllSetShadowPos(D3DXVECTOR3 pos, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			D3DXVECTOR3 ShadowPos = pMotionParts->GetWorldPos();
			ShadowPos.y = pos.y;
			pMotionParts->SetShadowPos(ShadowPos);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}
