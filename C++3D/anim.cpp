//=============================================================================
//
// anim.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "anim.h"

// ポリゴンの幅
const float CAnim::SIZE_ANIM = 64.0f;
CAnim *CAnim::m_pAnim[ANIM_MAX] = {};
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CAnim::CAnim()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CAnim::~CAnim()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CAnim::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	m_nAnimCnt = 0;
	m_nAnimNumX = 0;
	m_nAnimNumY = 0;
	m_nAnimTime = 0;
	m_nAnimXNumber = 1;
	m_nAnimYNumber = 1;
	
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CAnim::Uninit()
{
	C2DPolygon::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CAnim::Update()
{
	C2DPolygon::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CAnim::Draw()
{
	C2DPolygon::Draw();
}

void CAnim::CreateAnim(D3DXVECTOR3 pos,int nAnimCnt, int nAnimXNumber, int nAnimYNumber, int nTextIndex)
{
	for (int nCnt = 0; nCnt < ANIM_MAX; nCnt++)
	{
		if (m_pAnim[nCnt] != nullptr)
		{
			continue;
		}

		m_pAnim[nCnt] = new CAnim;

		if (FAILED(m_pAnim[nCnt]->Init()))
		{
			return;
		}

		D3DXVECTOR2 posUV = D3DXVECTOR2(1.0f / nAnimXNumber * 0.5f, 1.0f / nAnimYNumber * 0.5f);
		D3DXVECTOR2 size = D3DXVECTOR2(1.0f / nAnimXNumber, 1.0f / nAnimYNumber);

		m_pAnim[nCnt]->SetPos(pos);
		m_pAnim[nCnt]->m_moveUV = size;
		m_pAnim[nCnt]->SetAnim(nAnimCnt, nAnimXNumber, nAnimYNumber);
		m_pAnim[nCnt]->SetDiagonalLine(SIZE_ANIM, SIZE_ANIM);
		m_pAnim[nCnt]->SetUV(posUV);
		m_pAnim[nCnt]->SetUVSize(size * 0.5f);
		m_pAnim[nCnt]->SetTextIndex(nTextIndex);
		m_pAnim[nCnt]->SetPolygon();

		break;
	}


}

bool CAnim::IsUnused()
{
	m_nAnimTime++;

	if (m_nAnimTime >= m_nAnimCnt)
	{
		m_nAnimTime = 0;
		m_nAnimNumX++;
		D3DXVECTOR2 move = D3DXVECTOR2(m_moveUV.x, 0.0f);

		if (m_nAnimNumX >= m_nAnimXNumber)
		{
			move.x = -m_moveUV.x * (m_nAnimNumX - 1);
			m_nAnimNumX = 0;
			m_nAnimNumY++;
			move.y = m_moveUV.y;
			AddUVPos(move);
			if (m_nAnimNumY >= m_nAnimYNumber)
			{
				return true;
			}
		}
		else
		{
			AddUVPos(move);
		}
	}

	return false;
}

//*****************************************************************************
// ALL初期化
//*****************************************************************************
void CAnim::ALLInit()
{
	ZeroMemory(m_pAnim, sizeof(m_pAnim));
}

//*****************************************************************************
// ALL終了処理
//*****************************************************************************
void CAnim::ALLUninit()
{
	for (int nCnt = 0; nCnt < ANIM_MAX; nCnt++)
	{
		if (m_pAnim[nCnt] != nullptr)
		{
			// 終了処理
			m_pAnim[nCnt]->Uninit();
			delete m_pAnim[nCnt];
			m_pAnim[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// ALL更新処理
//*****************************************************************************
void CAnim::ALLUpdate()
{
	for (int nCnt = 0; nCnt < ANIM_MAX; nCnt++)
	{
		if (m_pAnim[nCnt] == nullptr)
		{
			continue;
		}
		// 更新処理
		m_pAnim[nCnt]->Update();
		if (m_pAnim[nCnt]->IsUnused())
		{
			// 終了処理
			m_pAnim[nCnt]->Uninit();
			delete m_pAnim[nCnt];
			m_pAnim[nCnt] = nullptr;
		}

	}
}

//*****************************************************************************
// ALL描画処理
//*****************************************************************************
void CAnim::ALLDraw()
{
	for (int nCnt = 0; nCnt < ANIM_MAX; nCnt++)
	{
		if (m_pAnim[nCnt] != nullptr)
		{
			// 描画処理
			m_pAnim[nCnt]->Draw();
		}
	}
}