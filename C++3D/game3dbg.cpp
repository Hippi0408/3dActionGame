//=============================================================================
//
// 処理 [game3dbg.cpp]
// Author : KOZUNA HIROHITO

//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "game3dbg.h"
#include "3dobject.h"

const D3DXVECTOR3 CGame3DBG::STANDARD_3DBG_MODEL = D3DXVECTOR3(0.0f,0.0f,0.0f);

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame3DBG::CGame3DBG()
{
	for (int nCntX = 0; nCntX < X_MAX_3DBG_MODEL; nCntX++)
	{
		for (int nCntZ = 0; nCntZ < Z_MAX_3DBG_MODEL; nCntZ++)
		{
			m_pBgModel[nCntX][nCntZ] = nullptr;
		}
	}
	m_BgObjSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, -0.2f);
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGame3DBG::~CGame3DBG()
{
}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CGame3DBG::Init(void)
{
	for (int nCntX = 0; nCntX < X_MAX_3DBG_MODEL; nCntX++)
	{
		D3DXVECTOR3 NestPos = STANDARD_3DBG_MODEL;

		for (int nCntZ = 0; nCntZ < Z_MAX_3DBG_MODEL; nCntZ++)
		{
			m_pBgModel[nCntX][nCntZ] = new C3DObject;

			if (FAILED(m_pBgModel[nCntX][nCntZ]->Init()))
			{
				return -1;
			}

			m_pBgModel[nCntX][nCntZ]->Set3DObject(0, NestPos);
			m_BgObjSize.x = (int)m_pBgModel[nCntX][nCntZ]->GetSize().x;
			m_BgObjSize.y = (int)m_pBgModel[nCntX][nCntZ]->GetSize().y;
			m_BgObjSize.z = (int)m_pBgModel[nCntX][nCntZ]->GetSize().z;
			NestPos.z += m_pBgModel[nCntX][nCntZ]->GetSize().z;

			m_pBgModel[nCntX][nCntZ]->AddPos(D3DXVECTOR3(m_BgObjSize.x * (-1 + nCntX),0.0f,0.0f));
		}


	}

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame3DBG::Uninit(void)
{
	for (int nCntX = 0; nCntX < X_MAX_3DBG_MODEL; nCntX++)
	{
		for (int nCntZ = 0; nCntZ < Z_MAX_3DBG_MODEL; nCntZ++)
		{
			if (m_pBgModel[nCntX][nCntZ] != nullptr)
			{
				m_pBgModel[nCntX][nCntZ]->Uninit();
				delete m_pBgModel[nCntX][nCntZ];
				m_pBgModel[nCntX][nCntZ] = nullptr;
			}
		}
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGame3DBG::Update(void)
{
	for (int nCntX = 0; nCntX < X_MAX_3DBG_MODEL; nCntX++)
	{
		for (int nCntZ = 0; nCntZ < Z_MAX_3DBG_MODEL; nCntZ++)
		{
			if (m_pBgModel[nCntX][nCntZ] == nullptr)
			{
				continue;
			}

			D3DXVECTOR3 pos = m_pBgModel[nCntX][nCntZ]->GetPos();

			if (pos.z < -m_BgObjSize.z * 2.0f)
			{
				m_pBgModel[nCntX][nCntZ]->AddPos(D3DXVECTOR3(0.0f, 0.0f, m_BgObjSize.z * (Z_MAX_3DBG_MODEL - 1)));
			}

			m_pBgModel[nCntX][nCntZ]->AddPos(m_Move);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGame3DBG::Draw()
{
	for (int nCntX = 0; nCntX < X_MAX_3DBG_MODEL; nCntX++)
	{
		for (int nCntZ = 0; nCntZ < Z_MAX_3DBG_MODEL; nCntZ++)
		{
			if (m_pBgModel[nCntX][nCntZ] != nullptr)
			{
				m_pBgModel[nCntX][nCntZ]->Draw();
			}
		}
	}
}
