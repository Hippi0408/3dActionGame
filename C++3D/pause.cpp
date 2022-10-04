//=============================================================================
//
// pause.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "input.h"
#include "manager.h"
#include "pause.h"
#include "texture.h"
#include "2dpolygon.h"
#include "ui.h"
#include "sound.h"

const float CPause::SIZE_PAUSE_UI = 1.0f / MAX_PAUSE;
const float CPause::SIZE_PAUSE_UI_HALF = SIZE_PAUSE_UI * 0.5f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPause::CPause()
{
	m_pBg = nullptr;
	m_pUi = nullptr;
	m_nMood = 0;
	m_bPause = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPause::~CPause()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CPause::Init()
{
	m_pBg = new CUI;

	if (FAILED(m_pBg->Init()))
	{
		return -1;
	}

	C2DPolygon *pPolygon = m_pBg->CreateUi(2);

	pPolygon[0].SetTextIndex(0);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	pPolygon[0].SetDiagonalLine((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pPolygon[0].SetPolygon();

	pPolygon[1].SetTextIndex(0);
	pPolygon[1].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[1].SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	pPolygon[1].SetDiagonalLine(722.0f, 842.0f);
	pPolygon[1].SetPolygon();


	m_pUi = new C2DPolygon;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	m_pUi->SetTextIndex(CTexture::LoadTexture("data/TEXTURE/PauseUi.png"));
	m_pUi->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pUi->SetUV(D3DXVECTOR2(SIZE_PAUSE_UI_HALF, 0.5f));
	m_pUi->SetUVSize(D3DXVECTOR2(SIZE_PAUSE_UI_HALF,0.5f));
	m_pUi->SetDiagonalLine(720.0f, 840.0f);
	m_pUi->SetPolygon();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPause::Uninit()
{
	//BG
	if (m_pBg != nullptr)
	{
		// 終了処理
		m_pBg->Uninit();
		delete m_pBg;
		m_pBg = nullptr;
	}
	if (m_pUi != nullptr)
	{
		// 終了処理
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPause::Update()
{
	CManager * pManager = GetManager();

	if (pManager->IsChangingMode())
	{//モードチェンジ中の時はこれより下の処理をスキップ
		return;
	}


	CInput *pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_DECISION))
	{
		switch (m_nMood)
		{
		case 0:
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_BACK);
			m_bPause = false;
			return;
			break;
		case 1:
			pManager->NextMode(TYPE_TITLE);
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_DETERMINATION);
			return;
			break;
		case 2:
			pManager->NextMode(TYPE_GAME);
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_DETERMINATION);
			return;
			break;
		case 3:
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_BACK);
			m_bPause = false;
			return;
			break;
		default:
			break;
		}
	}

	if (pInput->Trigger(KEY_UP))
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nMood--;
	}
	else if (pInput->Trigger(KEY_DOWN))
	{
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nMood++;
	}

	if (m_nMood >= MAX_PAUSE)
	{
		m_nMood = 0;
	}
	else if (m_nMood < 0)
	{
		m_nMood = MAX_PAUSE - 1;
	}

	m_pUi->SetUV(D3DXVECTOR2(SIZE_PAUSE_UI_HALF + SIZE_PAUSE_UI * m_nMood, 0.5f));
	m_pUi->Update();

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPause::Draw()
{
	//BG
	m_pBg->Draw();
	m_pUi->Draw();
}