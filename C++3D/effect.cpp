//=============================================================================
//
// effect.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "effect.h"
#include "main.h"
#include "manager.h"
#include "texture.h"

CEffect *CEffect::m_pEffect[EFFECT_MAX] = {};
int CEffect::m_nEffectTextIndex = 0;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEffect::CEffect()
{
	m_fAttenuation = 0.0f;
	m_fScaleDown = 0.0f;
	m_nLife = 0;
	m_bAddColor = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEffect::~CEffect()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEffect::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEffect::Uninit()
{
	C2DPolygon::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEffect::Update()
{
	AddDiagonalLine(m_fScaleDown, m_fScaleDown);
	AddColor(D3DXCOLOR(0.0f,0.0f,0.0,m_fAttenuation));
	m_nLife--;

	D3DXCOLOR color = GetColor();

	if (color.a < 0.0f)
	{
		SetColor(D3DXCOLOR(color.r, color.g, color.b, 0.0f));
	}
	else if (color.a > 1.0f)
	{
		SetColor(D3DXCOLOR(color.r, color.g, color.b, 1.0f));
	}

	float fsize = GetActualRadius();

	if (fsize < 0.0f)
	{
		SetDiagonalLine(0.0f, 0.0f);
	}

	C2DPolygon::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEffect::Draw()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	if (m_bAddColor)
	{
		//αブレンディングを加算合成に設定
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	C2DPolygon::Draw();

	if (m_bAddColor)
	{
		//αブレンディングを元の戻す
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//*****************************************************************************
// 終了条件
//*****************************************************************************
bool CEffect::IsUnused()
{
	if (m_nLife < 0)
	{
		return true;
	}

	D3DXCOLOR color = GetColor();

	if (color.a <= 0.0f)
	{
		return true;
	}

	float fsize = GetActualRadius();

	if (fsize <= 0.0f)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// エフェクトの設定
//*****************************************************************************
void CEffect::SetEffect(const Effect effect)
{
	m_fAttenuation = effect.fAttenuation;
	m_fScaleDown = effect.fScaleDown;
	m_nLife = effect.nLife;
	m_bAddColor = effect.bAddColor;
	SetDiagonalLine(effect.fSizeX, effect.fSizeY);

	if (effect.nTextIndex == 0)
	{
		SetTextIndex(m_nEffectTextIndex);
	}
	else
	{
		SetTextIndex(effect.nTextIndex);
	}
	SetUp(effect.pos, effect.rot, effect.move);
	SetColor(effect.Color);
	SetPolygon();
}

//*****************************************************************************
// エフェクトの生成
//*****************************************************************************
void CEffect::CreateEffect(const Effect effect)
{
	for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			continue;
		}

		m_pEffect[nCnt] = new CEffect;

		if (FAILED(m_pEffect[nCnt]->Init()))
		{
			return;
		}

		m_pEffect[nCnt]->SetEffect(effect);

		break;
	}


}

//*****************************************************************************
// ALL初期化
//*****************************************************************************
void CEffect::ALLInit()
{
	m_nEffectTextIndex = CTexture::LoadTexture("data/TEXTURE/effect.jpg");
	ZeroMemory(m_pEffect, sizeof(m_pEffect));
}

//*****************************************************************************
// ALL終了処理
//*****************************************************************************
void CEffect::ALLUninit()
{
	for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			// 終了処理
			m_pEffect[nCnt]->Uninit();
			delete m_pEffect[nCnt];
			m_pEffect[nCnt] = nullptr;
		}
	}
}

//*****************************************************************************
// ALL更新処理
//*****************************************************************************
void CEffect::ALLUpdate()
{
	for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
	{
		if (m_pEffect[nCnt] == nullptr)
		{
			continue;
		}
		// 更新処理
		m_pEffect[nCnt]->Update();
		if (m_pEffect[nCnt]->IsUnused())
		{
			// 終了処理
			m_pEffect[nCnt]->Uninit();
			delete m_pEffect[nCnt];
			m_pEffect[nCnt] = nullptr;
		}

	}
}

//*****************************************************************************
// ALL描画処理
//*****************************************************************************
void CEffect::ALLDraw()
{
	for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			// 描画処理
			m_pEffect[nCnt]->Draw();
		}
	}
}