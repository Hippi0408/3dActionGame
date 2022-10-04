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
#include "title.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include "texture.h"
#include "3dpolygon.h"
#include "camera.h"
#include "light.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{
	
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CTitle::Init()
{
	m_pUi = nullptr;

	m_pUi = new CUI;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pUi->CreateUi(1);

	int nIndex = CTexture::LoadTexture("data/TEXTURE/タイトル.png");
	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine(200.0f, 200.0f);
	pPolygon[0].SetPolygon();

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
	nIndex = CTexture::LoadTexture("data/TEXTURE/タイトル.png");
	m_pBG->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBG->SetRot(D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBG->SetTextIndex(nIndex);
	m_pBG->SetDiagonalLine(500.0f, 500.0f);
	m_pBG->SetPolygon();


	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTitle::Uninit()
{
	//UI
	if (m_pUi != nullptr)
	{
		// 終了処理
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}

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
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTitle::Update()
{
	m_pUi->Update();

	CInput *pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_DECISION))
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_GAME);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTitle::Draw()
{
	//カメラ
	m_pCamera->SetCamera();

	m_pBG->Draw();
	//ＵＩ
	//m_pUi->Draw();
}