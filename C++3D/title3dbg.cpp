//=============================================================================
//
// 処理 [title3dbg.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "title3dbg.h"
#include "3dobject.h"
#include "read.h"
#include <assert.h>

const D3DXVECTOR3 CTitle3DBG::STANDARD_3DBG_MODEL_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const D3DXVECTOR3 CTitle3DBG::STANDARD_3DBG_MODEL_ROT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float CTitle3DBG::DISTANCE = 50.0f;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTitle3DBG::CTitle3DBG()
{
	for (int nCnt = 0; nCnt < MAX_3DBG_MODEL; nCnt++)
	{
		m_pBgModel[nCnt] = nullptr;
		m_Revolution[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 90.0f);
		m_RevolutionMove[nCnt] = STANDARD_3DBG_MODEL_ROT;
		m_Rotation[nCnt] = STANDARD_3DBG_MODEL_ROT;
		m_RotationMove[nCnt] = STANDARD_3DBG_MODEL_ROT;
		m_fScal[nCnt] = 1.0f;
	}
	m_pRead = nullptr;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTitle3DBG::~CTitle3DBG()
{
}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CTitle3DBG::Init(void)
{
	m_RevolutionMove[0].z = 0.0f;
	m_RotationMove[0].y = -0.0025f;
	m_fScal[0] = 0.3f;

	m_RevolutionMove[1].z = 0.04f;
	m_RotationMove[1].y = 0.025f;
	m_fScal[1] = 0.05f;

	m_RevolutionMove[2].z = 0.05f;
	m_RotationMove[2].y = 0.0125f;
	m_fScal[2] = 0.1f;

	m_RevolutionMove[3].z = 0.06f;
	m_RotationMove[3].y = 0.0125f;
	m_fScal[3] = 0.15f;

	m_RevolutionMove[4].z = 0.08f;
	m_RotationMove[4].y = 0.025f;
	m_fScal[4] = 0.1f;

	m_RevolutionMove[5].z = 0.06f;
	m_RotationMove[5].y = 0.025f;
	m_fScal[5] = 0.2f;


	m_pRead = new CRead;
	m_pRead->ReadModel(TitleModel);

	D3DXVECTOR3 NestPos = STANDARD_3DBG_MODEL_POS;

	for (int nCnt = 0; nCnt < MAX_3DBG_MODEL; nCnt++)
	{
		m_pBgModel[nCnt] = new C3DObject;

		if (FAILED(m_pBgModel[nCnt]->Init()))
		{
			return -1;
		}
		NestPos.x = cosf(D3DXToRadian(m_Revolution[nCnt].z)) * (DISTANCE * nCnt);
		NestPos.z = sinf(D3DXToRadian(m_Revolution[nCnt].z)) * (DISTANCE * nCnt);
		NestPos.y = 0.0f;

		m_pBgModel[nCnt]->SetSize(m_fScal[nCnt]);
		m_pBgModel[nCnt]->SetRot(m_Rotation[nCnt]);
		m_pBgModel[nCnt]->Set3DObject(nCnt, NestPos);
	}

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTitle3DBG::Uninit(void)
{

	for (int nCnt = 0; nCnt < MAX_3DBG_MODEL; nCnt++)
	{
		if (m_pBgModel[nCnt] != nullptr)
		{
			m_pBgModel[nCnt]->Uninit();
			delete m_pBgModel[nCnt];
			m_pBgModel[nCnt] = nullptr;
		}
	}

	//外部ファイル
	if (m_pRead != nullptr)
	{
		delete m_pRead;
		m_pRead = nullptr;
	}

}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTitle3DBG::Update(void)
{
	D3DXVECTOR3 NestPos = STANDARD_3DBG_MODEL_POS;
	D3DXVECTOR3 RevolutionAddRot = STANDARD_3DBG_MODEL_POS;
	RevolutionAddRot.z = 0.1f;
	D3DXVECTOR3 RotationAddRot = STANDARD_3DBG_MODEL_POS;
	RotationAddRot.y = 0.05f;

	for (int nCnt = 0; nCnt < MAX_3DBG_MODEL; nCnt++)
	{
		if (m_pBgModel[nCnt] == nullptr)
		{
			assert(false);
		}

		m_Revolution[nCnt] += m_RevolutionMove[nCnt];

		NestPos.x = cosf(D3DXToRadian(m_Revolution[nCnt].z)) * (DISTANCE * nCnt);
		NestPos.z = sinf(D3DXToRadian(m_Revolution[nCnt].z)) * (DISTANCE * nCnt);

		m_pBgModel[nCnt]->AddRot(m_RotationMove[nCnt]);
		m_pBgModel[nCnt]->Set3DObject(nCnt, NestPos);
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTitle3DBG::Draw()
{
	for (int nCnt = 0; nCnt < MAX_3DBG_MODEL; nCnt++)
	{
		if (m_pBgModel[nCnt] != nullptr)
		{
			m_pBgModel[nCnt]->Draw();
		}
	}
}
