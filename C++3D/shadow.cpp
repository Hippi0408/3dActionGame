//=============================================================================
//
// [shadow.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "shadow.h"
#include "manager.h"
#include "texture.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CShadow::CShadow()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CShadow::~CShadow()
{
}

//*****************************************************************************
// 描画
//*****************************************************************************
void CShadow::Draw()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//αブレンディングを減算合成に設定
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	C3DPolygon::Draw();

	//αブレンディングを元の戻す
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}