//=============================================================================
//
// name.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "name.h"
#include "beeline.h"
#include "texture.h"

const float CName::NAME_SIZE_ADJUSTMENT = 0.7f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CName::CName()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		m_aNameIndex[nCnt] = MAX_NAME_INDEX;
		m_pName[nCnt] = nullptr;
	}
	m_fSize = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSetNameNum = 0;
	m_nTextureIndex = 0;
	m_bFlashing = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CName::~CName()
{

}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CName::Init()
{
	m_nTextureIndex = CTexture::LoadTexture("data/TEXTURE/アルファベット.png");
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CName::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Uninit();

			delete m_pName[nCnt];
			m_pName[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CName::Update()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{
			continue;
		}

		if (m_bFlashing)
		{
			m_pName[nCnt]->SetFlashing();
		}

		m_pName[nCnt]->Update();
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CName::Draw()
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{
			continue;
		}

		m_pName[nCnt]->Draw();
	}
}

//*****************************************************************************
// ネームの一文字設定
//*****************************************************************************
void CName::SetName(const int nNameIndex)
{
	if (m_nSetNameNum >= MAX_NAME_LENGTH)
	{//設定された文字数を超えてないか
		return;
	}

	if (m_pName[m_nSetNameNum] != nullptr)
	{//ポインタがNULLかどうか
		return;
	}

	m_pName[m_nSetNameNum] = new CBeeline;

	if (FAILED(m_pName[m_nSetNameNum]->Init()))
	{//２ｄポリゴンのＩＮＩＴ
		return;
	}

	//位置の設定
	D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x + (m_fSize * NAME_SIZE_ADJUSTMENT) * (m_nSetNameNum), m_Pos.y, 0.0f);

	//一文字のセット
	m_pName[m_nSetNameNum]->SetPos(pos);
	m_pName[m_nSetNameNum]->SetSize(m_fSize);
	m_pName[m_nSetNameNum]->SetTextureIndex(m_nTextureIndex);
	m_pName[m_nSetNameNum]->SetBeeline(nNameIndex);
	m_nSetNameNum++;
}

//*****************************************************************************
// ネームの一文字の破壊
//*****************************************************************************
void CName::BreakBeeline()
{
	m_nSetNameNum--;
	if (m_nSetNameNum < 0)
	{
		m_nSetNameNum = 0;
	}

	if (m_pName[m_nSetNameNum] == nullptr)
	{
		return;
	}

	m_pName[m_nSetNameNum]->Uninit();

	delete m_pName[m_nSetNameNum];
	m_pName[m_nSetNameNum] = nullptr;
}

//*****************************************************************************
// ネームのまとめて設定
//*****************************************************************************
void CName::SetAllName(const int *pNameIndex)
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH - 1; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{//ポインタがNULLかどうか

			return;
		}

		if (pNameIndex[nCnt] < 0 || MAX_NAME_INDEX <= pNameIndex[nCnt])
		{
			continue;
		}

		m_pName[nCnt] = new CBeeline;

		if (FAILED(m_pName[nCnt]->Init()))
		{//２ｄポリゴンのＩＮＩＴ
			return;
		}

		//位置の設定
		D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x + (m_fSize * 0.7f) * (nCnt + 1), m_Pos.y, 0.0f);

		//一文字のセット
		m_pName[nCnt]->SetPos(pos);
		m_pName[nCnt]->SetSize(m_fSize);
		m_pName[nCnt]->SetTextureIndex(m_nTextureIndex);
		m_pName[nCnt]->SetBeeline(pNameIndex[nCnt]);
	}
}

//*****************************************************************************
// ネームのまとめて変更
//*****************************************************************************
void CName::ChangeName(const int *pNameIndex)
{
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{//ポインタがNULLかどうか
			return;
		}
		m_pName[nCnt]->ChangeBeeline(pNameIndex[nCnt]);
	}
}

//*****************************************************************************
// 位置の移動
//*****************************************************************************
void CName::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{//ポインタがNULLかどうか
			continue;
		}
		//位置の設定
		D3DXVECTOR3 Namepos = D3DXVECTOR3(m_Pos.x + (m_fSize * 0.7f) * (nCnt + 1), m_Pos.y, 0.0f);

		//2Dポリゴンのセット
		m_pName[nCnt]->SetPos(Namepos);
	}
}

//*****************************************************************************
// 位置の移動
//*****************************************************************************
void CName::AddPos(D3DXVECTOR3 Add)
{
	m_Pos += Add;

	for (int nCnt = 0; nCnt < MAX_NAME_LENGTH; nCnt++)
	{
		if (m_pName[nCnt] == nullptr)
		{//ポインタがNULLかどうか
			continue;
		}

		m_pName[nCnt]->AddPos(Add);
	}
}