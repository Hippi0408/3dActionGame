//=============================================================================
//
// ranking.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "ranking.h"
#include "number.h"
#include "read.h"
#include "name.h"
#include "manager.h"
#include "result.h"
#include "texture.h"

const float CRanking::RANKING_SIZE = 128.0f;
const float CRanking::SIZE_UI = 1.0f / MAX_STAGE;
const float CRanking::SIZE_UI_HALF = SIZE_UI * 0.5f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CRanking::CRanking()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CRanking::~CRanking()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
void CRanking::Init(D3DXVECTOR3 pos)
{
	m_pStageName = nullptr;
	m_bNewScore = false;
	m_Pos = pos;
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_pCounter[nCnt] = nullptr;
		m_pName[nCnt] = nullptr;
		m_nScore[nCnt] = 0;
		m_NameData[nCnt].nNameNumIndex[0] = -1;
		m_NameData[nCnt].nNameNumIndex[1] = -1;
		m_NameData[nCnt].nNameNumIndex[2] = -1;
		m_NameData[nCnt].nNameNumIndex[3] = -1;
		m_pAirframe[nCnt] = nullptr;
	}


	m_nAirframe[0] = CTexture::LoadTexture("data/TEXTURE/自機1.png");
	m_nAirframe[1] = CTexture::LoadTexture("data/TEXTURE/自機2.png");
	m_nAirframe[2] = CTexture::LoadTexture("data/TEXTURE/自機3.png");

}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CRanking::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_pCounter[nCnt] != nullptr)
		{
			m_pCounter[nCnt]->Uninit();

			delete m_pCounter[nCnt];
			m_pCounter[nCnt] = nullptr;
		}

		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Uninit();

			delete m_pName[nCnt];
			m_pName[nCnt] = nullptr;
		}

		if (m_pAirframe[nCnt] != nullptr)
		{
			m_pAirframe[nCnt]->Uninit();

			delete m_pAirframe[nCnt];
			m_pAirframe[nCnt] = nullptr;
		}
	}

	if (m_pStageName != nullptr)
	{
		// 終了処理
		m_pStageName->Uninit();
		delete m_pStageName;
		m_pStageName = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CRanking::Update()
{
	CManager *pManager = GetManager();
	int nPLScr = pManager->GetScore();
	int nPL = pManager->GetAirframe();
	int nStage = 0;

	if (m_Pos.y < SCREEN_HEIGHT * 0.5f)
	{
		m_Pos += D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	}
	
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_pCounter[nCnt] == nullptr)
		{
			continue;
		}
		D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + (RANKING_SIZE * 1.5f * nCnt), 0.0f);

		m_pCounter[nCnt]->SetNumberPos(pos);

		if (m_pName[nCnt] == nullptr)
		{
			continue;
		}
		m_pName[nCnt]->SetPos(D3DXVECTOR3(m_Pos.x - 750.0f, pos.y, 0.0f));
		//13,4,22,-1,-1 = NEW
		if (m_nScore[nCnt] == nPLScr
			&& m_NameData[nCnt].nNameNumIndex[0] == 13
			&& m_NameData[nCnt].nNameNumIndex[1] == 4
			&& m_NameData[nCnt].nNameNumIndex[2] == 22
			&& m_NameData[nCnt].nNameNumIndex[3] == -1
			&& m_NameData[nCnt].nNameNumIndex[4] == -1
			&& !m_bNewScore)
		{
			m_bNewScore = true;
			m_pName[nCnt]->SetFlashing();
			m_pAirframe[nCnt]->SetTextIndex(m_nAirframe[nPL]);
			m_nAirframeTex[nCnt] = m_nAirframe[nPL] % 3;
		}

		m_pName[nCnt]->Update();

		m_pAirframe[nCnt]->SetPos(D3DXVECTOR3(m_Pos.x + 100.0f, pos.y, 0.0f));
		m_pAirframe[nCnt]->SetPolygon();
	}

	m_pStageName->SetPos(D3DXVECTOR3(m_Pos.x - 300.0f, m_Pos.y - 200.0f, 0.0f));
	m_pStageName->SetUV(D3DXVECTOR2(SIZE_UI_HALF + SIZE_UI * nStage, 0.5f));
	m_pStageName->SetPolygon();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CRanking::Draw()
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_pCounter[nCnt] != nullptr)
		{
			m_pCounter[nCnt]->Draw();
		}
		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Draw();
		}
		if (m_pAirframe[nCnt] != nullptr)
		{
			m_pAirframe[nCnt]->Draw();
		}
	}

	m_pStageName->Draw();
}

//*****************************************************************************
// 数値の設定
//*****************************************************************************
void CRanking::Create(const NameData *pName, const int *pScore, const int *pAirframe)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (m_pCounter[nCnt] != nullptr)
		{
			continue;
		}

		m_pCounter[nCnt] = new CNumber;

		if (FAILED(m_pCounter[nCnt]->Init()))
		{
			return;
		}

		m_pCounter[nCnt]->SetNumber(D3DXVECTOR3(m_Pos.x,m_Pos.y + (RANKING_SIZE * 2.0f * nCnt),0.0f), MAX_RANKING_DIGIT, RANKING_SIZE, pScore[nCnt]);

		m_nScore[nCnt] = pScore[nCnt];

		for (int nName = 0; nName < CName::MAX_NAME_LENGTH; nName++)
		{
			m_NameData[nCnt].nNameNumIndex[nName] = pName[nCnt].nNameNumIndex[nName];
		}

		if (m_pName[nCnt] != nullptr)
		{
			continue;
		}

		m_pName[nCnt] = new CName;

		if (FAILED(m_pName[nCnt]->Init()))
		{
			return;
		}
		m_pName[nCnt]->SetPos(D3DXVECTOR3(m_Pos.x - 750.0f, m_Pos.y + (RANKING_SIZE * 2.0f * nCnt), 0.0f));
		m_pName[nCnt]->SetSize(80.0f);
		m_pName[nCnt]->SetAllName(&pName[nCnt].nNameNumIndex[0]);

		m_pAirframe[nCnt] = new C2DPolygon;

		if (FAILED(m_pAirframe[nCnt]->Init()))
		{
			return;
		}

		m_nAirframeTex[nCnt] = m_nAirframe[pAirframe[nCnt]] % 3;
		m_pAirframe[nCnt]->SetTextIndex(m_nAirframe[pAirframe[nCnt]]);
		m_pAirframe[nCnt]->SetPos(D3DXVECTOR3(m_Pos.x + 100.0f, m_Pos.y + (RANKING_SIZE * 2.0f * nCnt), 0.0f));
		m_pAirframe[nCnt]->SetDiagonalLine(100.0f, 100.0f);
		m_pAirframe[nCnt]->SetPolygon();

	}

	m_pStageName = new C2DPolygon;

	if (FAILED(m_pStageName->Init()))
	{
		return;
	}
	int nIndex = CTexture::LoadTexture("data/TEXTURE/StageSelectUI03.png");
	m_pStageName->SetTextIndex(nIndex);
	m_pStageName->SetUVSize(D3DXVECTOR2(SIZE_UI_HALF, 0.5f));
	m_pStageName->SetUV(D3DXVECTOR2(SIZE_UI_HALF, 0.5f));
	m_pStageName->SetPos(D3DXVECTOR3(m_Pos.x - 300.0f, m_Pos.y - 200.0f, 0.0f));
	m_pStageName->SetDiagonalLine(500.0f, 500.0f);
	m_pStageName->SetPolygon();
}

//*****************************************************************************
// PLネームの設定
//*****************************************************************************
void CRanking::SetPLNewData(int *pNameIndex)
{
	CManager *pManager = GetManager();
	int nPLScr = pManager->GetScore();

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		//13,4,22,-1,-1 = NEW
		if (m_nScore[nCnt] == nPLScr
			&& m_NameData[nCnt].nNameNumIndex[0] == 13
			&& m_NameData[nCnt].nNameNumIndex[1] == 4
			&& m_NameData[nCnt].nNameNumIndex[2] == 22
			&& m_NameData[nCnt].nNameNumIndex[3] == -1
			&& m_NameData[nCnt].nNameNumIndex[4] == -1)
		{
			for (int nName = 0; nName < CName::MAX_NAME_LENGTH; nName++)
			{
				m_NameData[nCnt].nNameNumIndex[nName] = pNameIndex[nName];
			}
			break;
		}
	}
}

//*****************************************************************************
// ランキングのセーブ
//*****************************************************************************
void CRanking::SaveRanking()
{
	//マネージャーのアドレス
	CManager *pManager = GetManager();
	//リザルトのアドレス
	CResult *pResult = (CResult*)pManager->GetGameObject();

	//pResult->GetRead()->SaveRanking(pManager->GetStage(),&m_nScore[0], &m_NameData[0],&m_nAirframeTex[0]);
}

//*****************************************************************************
// ランキングが更新されたか
//*****************************************************************************
bool CRanking::PLNewRanking()
{
	CManager *pManager = GetManager();
	int nPLScr = pManager->GetScore();

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		//13,4,22,-1,-1 = NEW
		if (m_nScore[nCnt] == nPLScr
			&& m_NameData[nCnt].nNameNumIndex[0] == 13
			&& m_NameData[nCnt].nNameNumIndex[1] == 4
			&& m_NameData[nCnt].nNameNumIndex[2] == 22
			&& m_NameData[nCnt].nNameNumIndex[3] == -1
			&& m_NameData[nCnt].nNameNumIndex[4] == -1)
		{
			return false;
		}
	}

	return true;
}
