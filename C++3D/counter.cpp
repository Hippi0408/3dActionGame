//=============================================================================
//
// counter.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "counter.h"
#include "number.h"

CCounter *CCounter::m_pCCounter = {};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCounter::CCounter()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCounter::~CCounter()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CCounter::Init(D3DXVECTOR3 pos, int nDigit, float fSize, int nNumerical)
{
	m_nCounter = 0;

	m_pCounter = new CNumber;

	if (FAILED(m_pCounter->Init()))
	{
		return -1;
	}

	m_pCounter->SetNumber(pos, nDigit, fSize, nNumerical);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCounter::Uninit()
{
	if (m_pCounter != nullptr)
	{
		m_pCounter->Uninit();
		delete m_pCounter;
		m_pCounter = nullptr;
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCounter::Draw()
{
	m_pCounter->Draw();
}

//*****************************************************************************
// 数値の設定
//*****************************************************************************
void CCounter::Add(int nAdd)
{
	m_nCounter += nAdd;

	if (m_nCounter < 0)
	{
		m_nCounter = 0;
	}

	m_pCounter->SetNumerical(m_nCounter);
}

void CCounter::AllUninit()
{
	if (m_pCCounter != nullptr)
	{
		m_pCCounter->Uninit();
		delete m_pCCounter;
		m_pCCounter = nullptr;
	}
}

void CCounter::AllDraw()
{

	if (m_pCCounter != nullptr)
	{
		m_pCCounter->Draw();
	}
}

void CCounter::AddCounter(int nAdd)
{
	if (m_pCCounter != nullptr)
	{
		m_pCCounter->Add(nAdd);
	}
	return;
}

CCounter *CCounter::Create()
{
	if (m_pCCounter == nullptr)
	{
		m_pCCounter = new CCounter;
		return m_pCCounter;
	}
	return nullptr;
}