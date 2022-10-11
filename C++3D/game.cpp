//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "light.h"
#include "3dpolygon.h"
#include "texture.h"
#include "player.h"
#include "3dobject.h"
#include "billboard.h"
#include "effect.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CGame::Init()
{
	//カメラ
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}

	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 200.0f, -1000.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCamera->SetVecU(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//ライト
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pBG = new C3DPolygon;
	if (FAILED(m_pBG->Init()))
	{
		return -1;
	}
	int nIndex = CTexture::LoadTexture("data/TEXTURE/ゲーム.png");
	m_pBG->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBG->SetRot(D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBG->SetTextIndex(nIndex);
	m_pBG->SetDiagonalLine(500.0f, 500.0f);
	m_pBG->SetPolygon();

	//Player
	m_pPlayer = new CPlayer;
	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}

	m_pBillcoard = new CBillcoard;
	if (FAILED(m_pBillcoard->Init()))
	{
		return -1;
	}
	nIndex = CTexture::LoadTexture("data/TEXTURE/陰陽玉.png");
	m_pBillcoard->SetPos(D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	m_pBillcoard->SetRot(D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBillcoard->SetTextIndex(nIndex);
	m_pBillcoard->SetDiagonalLine(50.0f, 50.0f);
	m_pBillcoard->SetPolygon();

	CEffect::InitTextIndex();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit()
{
	CEffect::ALLUninit();

	//カメラ
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//ライト
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	//3DBG
	if (m_pBG != nullptr)
	{
		m_pBG->Uninit();
		delete m_pBG;
		m_pBG = nullptr;
	}

	//
	if (m_pBillcoard != nullptr)
	{
		m_pBillcoard->Uninit();
		delete m_pBillcoard;
		m_pBillcoard = nullptr;
	}

	//Player
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	C3DObject::UninitAllModel();
	
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update()
{
	CEffect::ALLUpdate();
	m_pPlayer->Update();
	CInput *pInput = CInput::GetKey();


	if (pInput->Press(DIK_UP))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f,0.0f,5.0f));
	}
	else if (pInput->Press(DIK_DOWN))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	}

	if (pInput->Press(DIK_LEFT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(DIK_RIGHT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	}


	if (pInput->Press(DIK_I))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	}
	else if (pInput->Press(DIK_K))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	}

	Effect effect;
	effect.fAttenuation = -0.01f;
	effect.fSizeX = 100.0f;
	effect.fSizeY = 100.0f;
	effect.nLife = 60;
	effect.fScaleDown = -2.0f;
	effect.nTextIndex = 0;
	effect.pos = pInput->GetMouseCursor();
	effect.Color = D3DXCOLOR(0.6f, 0.3f, 0.3f, 1.0f);
	effect.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	effect.bAddColor = true;
	CEffect::CreateEffect(effect);


	if (pInput->Trigger(KEY_DECISION))
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame::Draw()
{
	//カメラ
	m_pCamera->SetCamera();

	m_pBG->Draw();

	m_pPlayer->Draw();

	m_pBillcoard->Draw();

	CEffect::ALLDraw();
}
