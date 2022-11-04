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
#include "meshfield.h"
#include "motion_parts.h"
#include "read.h"

int g_nCnt = 0;
int g_nCnt2 = 0;
int g_nCnt3 = 0;

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
	m_pMeshfieldBG = new CMeshfield;
	if (FAILED(m_pMeshfieldBG->Init()))
	{
	return -1;
	}
	
	MeshfieldStructure MeshData;
	ZeroMemory(&MeshData,sizeof(MeshData));
	MeshData.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MeshData.rot = D3DXVECTOR3(D3DXToRadian(0), 0.0f, 0.0f);
	MeshData.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	MeshData.fRadiusX = 100.0f;
	MeshData.fRadiusZ = 100.0f;
	MeshData.nMeshX = 20;
	MeshData.nMeshZ = 20;
	MeshData.nTextIndex = CTexture::LoadTexture("data/TEXTURE/ゲーム.png");
	m_pMeshfieldBG->SetMeshfield(MeshData);
	


	//Player
	m_pPlayer = new CPlayer;
	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}
	m_pPlayer->SetLight(m_pLight->GetLightVec());

	m_pBillcoard = new CBillcoard;
	if (FAILED(m_pBillcoard->Init()))
	{
		return -1;
	}
	int nIndex = CTexture::LoadTexture("data/TEXTURE/陰陽玉.png");
	m_pBillcoard->SetPos(D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	m_pBillcoard->SetRot(D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBillcoard->SetTextIndex(nIndex);
	m_pBillcoard->SetDiagonalLine(50.0f, 50.0f);
	m_pBillcoard->SetPolygon();

	CEffect::InitTextIndex();

	CRead cRead;

	g_nCnt = cRead.ReadMotion("data/MOTION/motionblock.txt");
	g_nCnt2 = cRead.ReadMotion("data/MOTION/motionblock.txt");
	g_nCnt3 = cRead.ReadMotion("data/MOTION/motionblock.txt");

	CMotionParts::SetLight(m_pLight->GetLightVec(), g_nCnt);
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



	if (m_pMeshfieldBG != nullptr)
	{
		m_pMeshfieldBG->Uninit();
		delete m_pMeshfieldBG;
		m_pMeshfieldBG = nullptr;
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

	CMotionParts::ALLUninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update()
{
	//m_pMeshfieldBG->Update();
	CEffect::ALLUpdate();
	m_pPlayer->Update();
	CInput *pInput = CInput::GetKey();

	CMotionParts::MoveMotionModel(D3DXVECTOR3(200.0f, 200.0f, -200.0f), D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f), g_nCnt, 0);
	CMotionParts::MoveMotionModel(D3DXVECTOR3(600.0f, 0.0f, -200.0f), D3DXVECTOR3(-D3DX_PI * 0.5f, -D3DX_PI * 0.1f, 0.0f), g_nCnt2, 0);
	CMotionParts::MoveMotionModel(D3DXVECTOR3(1000.0f, 0.0f, -200.0f), D3DXVECTOR3(-D3DX_PI * 0.1f, -D3DX_PI * 0.1f, 0.0f), g_nCnt3, 0);

	CMotionParts::AllSetShadowPos(D3DXVECTOR3(300.0f, 50.0f, -500.0f), g_nCnt);

	if (pInput->Press(DIK_UP))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	}
	else if (pInput->Press(DIK_DOWN))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	}

	if (pInput->Press(DIK_LEFT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(DIK_RIGHT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	}


	if (pInput->Press(DIK_RSHIFT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	}
	else if (pInput->Press(DIK_RCONTROL))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	}

	if (pInput->Press(DIK_I))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	}
	else if (pInput->Press(DIK_K))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	}


	if (pInput->Press(DIK_T))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	}
	else if (pInput->Press(DIK_G))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	}

	if (pInput->Press(DIK_F))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(DIK_H))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	}


	D3DXVECTOR3 Ppos = m_pPlayer->GetPos();

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
	//CEffect::CreateEffect(effect);


	CMotionParts::ALLUpdate();

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

	//m_pBG->Draw();

	m_pMeshfieldBG->Draw();

	m_pPlayer->Draw();

	CMotionParts::ALLDraw();

	m_pBillcoard->Draw();



	CEffect::ALLDraw();
}
