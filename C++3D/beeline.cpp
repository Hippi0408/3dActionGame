//=============================================================================
//
// beeline.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "beeline.h"
#include "2dpolygon.h"
#include "texture.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBeeline::CBeeline()
{
	m_pBeeline = nullptr;
	m_nTextureIndex = 0;
	m_nBeelineIndex = 0;
	m_fSize = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBeeline::~CBeeline()
{

}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CBeeline::Init()
{
	m_pBeeline = new C2DPolygon;

	if (FAILED(m_pBeeline->Init()))
	{//２ｄポリゴンのＩＮＩＴ
		return -1;
	}

	m_nTextureIndex = 0;
	m_nBeelineIndex = 0;
	m_fSize = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBeeline::Uninit()
{

	if (m_pBeeline == nullptr)
	{
		return;
	}

	m_pBeeline->Uninit();

	delete m_pBeeline;
	m_pBeeline = nullptr;

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBeeline::Update()
{
	if (m_bFlashing)
	{
		m_pBeeline->SetFlashing(120);
	}
	m_pBeeline->Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBeeline::Draw()
{

	if (m_pBeeline == nullptr)
	{
		return;
	}

	m_pBeeline->Draw();

}

//*****************************************************************************
// ネームの一文字設定
//*****************************************************************************
void CBeeline::SetBeeline(const int nNameIndex)
{
	if (m_pBeeline == nullptr)
	{//ポインタがNULLかどうか
		return;
	}

	
	//ＸＹの番号の計算
	int nNumX = nNameIndex % MAX_NAME_X;
	int nNumY = nNameIndex / MAX_NAME_X;

	//ＸＹのサイズの設定
	float fUVSizeX = 1.0f / MAX_NAME_X;
	float fUVSizeY = 1.0f / MAX_NAME_Y;

	//ＵＶの位置の設定
	D3DXVECTOR2 posUV;
	//ＵＶのサイズの設定
	D3DXVECTOR2 sizeUV;
	if (nNameIndex >= MAX_NAME_INDEX || nNameIndex < 0)
	{
		posUV = D3DXVECTOR2(0.0f, 0.0f);
		sizeUV = D3DXVECTOR2(0.0f, 0.0f);
	}
	else
	{
		posUV = D3DXVECTOR2(fUVSizeX * nNumX + fUVSizeX * 0.5f, fUVSizeY * nNumY + fUVSizeY * 0.5f);
		sizeUV = D3DXVECTOR2(1.0f / MAX_NAME_X * 0.5f, 1.0f / MAX_NAME_Y * 0.5f);
	}

	//2Dポリゴンのセット
	m_pBeeline->SetPos(m_Pos);
	m_pBeeline->SetDiagonalLine(m_fSize, m_fSize);
	m_pBeeline->SetUV(posUV);
	m_pBeeline->SetUVSize(sizeUV);
	m_pBeeline->SetTextIndex(m_nTextureIndex);
	m_pBeeline->SetPolygon();
}

//*****************************************************************************
// ネームの一文字の変更
//*****************************************************************************
void CBeeline::ChangeBeeline(const int nNameIndex)
{
	if (m_pBeeline != nullptr)
	{//ポインタがNULLかどうか
		return;
	}

	//ＸＹの番号の計算
	int nNumX = nNameIndex % MAX_NAME_X;
	int nNumY = nNameIndex / MAX_NAME_X;

	//ＸＹのサイズの設定
	float fUVSizeX = 1.0f / MAX_NAME_X;
	float fUVSizeY = 1.0f / MAX_NAME_Y;

	//ＵＶの位置の設定
	D3DXVECTOR2 posUV;
	//ＵＶのサイズの設定
	D3DXVECTOR2 sizeUV;
	if (nNameIndex >= MAX_NAME_INDEX || nNameIndex < 0)
	{
		posUV = D3DXVECTOR2(0.0f, 0.0f);
		sizeUV = D3DXVECTOR2(0.0f, 0.0f);
	}
	else
	{
		posUV = D3DXVECTOR2(fUVSizeX * nNumX + fUVSizeX * 0.5f, fUVSizeY * nNumY + fUVSizeY * 0.5f);
		sizeUV = D3DXVECTOR2(1.0f / MAX_NAME_X * 0.5f, 1.0f / MAX_NAME_Y * 0.5f);
	}

	//2Dポリゴンのセット
	m_pBeeline->SetUV(posUV);
	m_pBeeline->SetUVSize(sizeUV);
	m_pBeeline->SetPolygon();
}

//*****************************************************************************
// 位置の移動
//*****************************************************************************
void CBeeline::AddPos(D3DXVECTOR3 Add)
{
	if (m_pBeeline == nullptr)
	{//ポインタがNULLかどうか
		return;
	}

	m_Pos += Add;

	//2Dポリゴンのセット
	m_pBeeline->SetPos(m_Pos);
	m_pBeeline->SetDiagonalLine(m_fSize, m_fSize);
	m_pBeeline->SetPolygon();

}

void CBeeline::SetPos(D3DXVECTOR3 pos)
{
	if (m_pBeeline == nullptr)
	{//ポインタがNULLかどうか
		return;
	}

	m_Pos = pos;

	//2Dポリゴンのセット
	m_pBeeline->SetPos(m_Pos);
	m_pBeeline->SetDiagonalLine(m_fSize, m_fSize);
	m_pBeeline->SetPolygon();
}