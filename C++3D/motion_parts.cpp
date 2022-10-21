//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "motion_parts.h"

const D3DXVECTOR3 CMotionParts::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CMotionParts *CMotionParts::m_pMotionPartsTop = nullptr;
CMotionParts *CMotionParts::m_pMotionPartsCurrent = nullptr;
int CMotionParts::m_nModelMax = 0;
int CMotionParts::m_MotionPlayMotonNum[MAX_MOTION_ALL] = {};
int CMotionParts::m_MotionPlayKeyNum[MAX_KEY] = {};
//*****************************************************************************
// コンストラクタ
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
// デストラクタ
//*****************************************************************************
CMotionParts::~CMotionParts()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CMotionParts::Init()
{

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CMotionParts::Uninit()
{

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CMotionParts::Update()
{
	


}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CMotionParts::Draw()
{
	C3DObject::Draw();
}

//*****************************************************************************
//	終了条件処理
//*****************************************************************************
bool CMotionParts::IsUnused()
{
	return false;
}

//*****************************************************************************
//	モーション番号指定でセットする
//*****************************************************************************
void CMotionParts::SetMotion(int nMotionNum)
{
	m_MotionPlayKeyNum[m_nModelObjNum] = 0;
	D3DXVECTOR3 rot = m_MotionKey[nMotionNum].aKey[m_MotionPlayKeyNum[m_nModelObjNum]].rot;

	SetRot(rot);
}

//*****************************************************************************
// ALL終了処理
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
// ALL更新処理
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
// ALL描画処理
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