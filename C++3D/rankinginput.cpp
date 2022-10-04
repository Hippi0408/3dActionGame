//=============================================================================
//
// rankinginput.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "rankinginput.h"
#include "beeline.h"
#include "input.h"
#include "result.h"
#include "manager.h"
#include "ranking.h"
#include "sound.h"

const float CRankingInput::SIZE_SET_MAME = 60.0f;
const float CRankingInput::SIZE_SET_SELECT_MAME = CRankingInput::SIZE_SET_MAME * 2.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CRankingInput::CRankingInput()
{
	m_pPLName = nullptr;

	ZeroMemory(m_pSetName,sizeof(m_pSetName));

	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nCurrentValue = 0;//選択中の数値
	m_nSetNameNum = 0;
	m_bChange = false;
	m_bUp = false;
	m_bSetEnd = false;
	m_nFpsCnt = 0;
	for (int nCnt = 0; nCnt < CName::MAX_NAME_LENGTH; nCnt++)
	{
		m_aPLNameIndex[nCnt] = -1;
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CRankingInput::~CRankingInput()
{

}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CRankingInput::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;

	m_pPLName = new CName;
	if (FAILED(m_pPLName->Init()))
	{
		return -1;
	}
	m_pPLName->SetSize(SIZE_SET_SELECT_MAME);
	m_pPLName->SetPos(pos);

	int nTex = m_pPLName->GetTextureIndex();

	float fTopPosY = pos.y - SIZE_SET_MAME * SET_PL_MAME_HALF;

	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{
		if (m_pSetName[nCnt] != nullptr)
		{
			continue;
		}

		m_pSetName[nCnt] = new CBeeline;
		if (FAILED(m_pSetName[nCnt]->Init()))
		{
			return -1;
		}

		if (SET_PL_MAME_HALF > nCnt)
		{
			m_pSetName[nCnt]->SetPos(D3DXVECTOR3(pos.x, pos.y + SIZE_SET_MAME * nCnt, 0.0f));
		}
		else
		{
			int nCntNum = nCnt % SET_PL_MAME_HALF;
			m_pSetName[nCnt]->SetPos(D3DXVECTOR3(pos.x, fTopPosY + SIZE_SET_MAME * nCntNum, 0.0f));
		}

		if (nCnt == 0)
		{
			m_pSetName[nCnt]->SetSize(SIZE_SET_SELECT_MAME);
		}
		else
		{
			m_pSetName[nCnt]->SetSize(SIZE_SET_MAME);

		}
		m_pSetName[nCnt]->SetTextureIndex(nTex);
		m_pSetName[nCnt]->SetBeeline(nCnt);
	}

	//マネージャーのアドレス
	CManager *pManager = GetManager();
	//リザルトのアドレス
	CResult *pResult = (CResult*)pManager->GetGameObject();
	//ランキングのアドレス
	//CRanking *pRanking = pResult->GetRanking();

	//m_bSetEnd = pRanking->PLNewRanking();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CRankingInput::Uninit()
{
	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{
		if (m_pSetName[nCnt] == nullptr)
		{
			continue;
		}

		m_pSetName[nCnt]->Uninit();

		delete m_pSetName[nCnt];
		m_pSetName[nCnt] = nullptr;
	}


	if (m_pPLName != nullptr)
	{
		m_pPLName->Uninit();

		delete m_pPLName;
		m_pPLName = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
bool CRankingInput::Update()
{
	CInput *pInput = CInput::GetKey();
	//マネージャーのアドレス
	CManager *pManager = GetManager();
	//リザルトのアドレス
	CResult *pResult = (CResult*)pManager->GetGameObject();
	//ランキングのアドレス
	//CRanking *pRanking = pResult->GetRanking();


	if (m_bSetEnd)
	{//最終決定
		if (pInput->Trigger(KEY_DECISION))
		{
			//サウンド再生
			PlaySound(SOUND_LABEL_SE_DETERMINATION);
			//pRanking->SetPLNewData(&m_aPLNameIndex[0]);
			//pRanking->SaveRanking();
			pManager->SetScore(0);
			return true;
		}

	}

	if (pInput->Trigger(KEY_BACK) && !m_bChange && m_nSetNameNum > 0)
	{//一文字戻る
		if (m_nSetNameNum >= CName::MAX_NAME_LENGTH)
		{
			m_Pos.x -= SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;
			m_pPLName->BreakBeeline();
			m_nSetNameNum--;
		}
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_BACK);
		m_Pos.x -= SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;
		m_pPLName->BreakBeeline();
		m_nSetNameNum--;
		m_aPLNameIndex[m_nSetNameNum] = -1;
		m_bSetEnd = false;
	}

	if (m_bSetEnd)
	{//ネームの打ち込みが終わったらこれよりしたの更新処理をスキップ
		return false;
	}
	
	if (pInput->Trigger(KEY_DECISION) && !m_bChange)
	{//文字の決定
		
		if (m_nCurrentValue == CName::MAX_NAME_INDEX - 1 && m_nSetNameNum == 0)
		{//いきなりENDが出来ないようにする処理
			return false;
		}

		//サウンド再生
		PlaySound(SOUND_LABEL_SE_DETERMINATION);
		m_aPLNameIndex[m_nSetNameNum] = m_nCurrentValue;
		m_pPLName->SetName(m_nCurrentValue);
		m_Pos.x += SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;

		if (m_nCurrentValue == CName::MAX_NAME_INDEX - 1)
		{
			m_bSetEnd = true;
			m_aPLNameIndex[m_nSetNameNum] = -1;
		}
		m_nSetNameNum++;

	}

	if (pInput->Press(KEY_UP) && !m_bChange)
	{//文字の変更上
	 //サウンド再生
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nCurrentValue++;
		m_bChange = true;
		m_bUp = true;
	}
	else if (pInput->Press(KEY_DOWN) && !m_bChange)
	{//文字の変更下
	 //サウンド再生
		PlaySound(SOUND_LABEL_SE_UP_DOWN);
		m_nCurrentValue--;
		m_bChange = true;
	}

	if (m_nCurrentValue >= SET_PL_MAME)
	{//選択文字の上限設定
		m_nCurrentValue = 0;
	}
	else if (m_nCurrentValue < 0)
	{//選択文字の下限設定
		m_nCurrentValue = SET_PL_MAME - 1;
	}

	//文字の変更の移動量
	float fMove = 0.0f;

	if (m_bChange)
	{//変更があった際の移動量の設定
		fMove = SIZE_SET_MAME / CHANGE_CNT;

		if (m_bUp)
		{
			fMove *= -1.0f;
		}
	}

	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{//文字の更新
		if (m_pSetName[nCnt] == nullptr)
		{//NULLチェック
			continue;
		}
		//文字のスクロール移動
		m_pSetName[nCnt]->AddPos(D3DXVECTOR3(0.0f, fMove, 0.0f));

		if (nCnt == m_nCurrentValue)
		{//選択中の文字のサイズを大きくする
			m_pSetName[nCnt]->SetSize(SIZE_SET_SELECT_MAME);
		}
		else
		{//選択中の文字以外を通常サイズの変更
			m_pSetName[nCnt]->SetSize(SIZE_SET_MAME);

		}
		//文字描画ポリゴンのGETPOS
		D3DXVECTOR3 CheckPos = m_pSetName[nCnt]->GetPos();

		if (CheckPos.y >= m_Pos.y + SIZE_SET_MAME * SET_PL_MAME_HALF)
		{//一定以上下に行ったら上に移動
			D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, m_Pos.y - SIZE_SET_MAME * SET_PL_MAME_HALF, 0.0f);
			m_pSetName[nCnt]->SetPos(pos);
		}
		else if (CheckPos.y <= m_Pos.y - SIZE_SET_MAME * SET_PL_MAME_HALF)
		{//一定以上上に行ったら下に移動
			D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, m_Pos.y + SIZE_SET_MAME * SET_PL_MAME_HALF, 0.0f);
			m_pSetName[nCnt]->SetPos(pos);
		}

		if (CheckPos.x != m_Pos.x)
		{//設定する文字のX軸の変更がある時変更する
			D3DXVECTOR3 pos = D3DXVECTOR3(m_Pos.x, CheckPos.y, 0.0f);
			m_pSetName[nCnt]->SetPos(pos);
		}
		
	}

	if (m_nSetNameNum >= CName::MAX_NAME_LENGTH - 1 && !m_bSetEnd)
	{//ネームの設定が終了
		m_bSetEnd = true;
		m_pPLName->SetName(CName::MAX_NAME_INDEX - 1);
		m_Pos.x += SIZE_SET_SELECT_MAME * CName::NAME_SIZE_ADJUSTMENT;
		m_nSetNameNum++;
	}

	if (!m_bChange)
	{//文字のスクロール移動がないときこれより下の更新をスキップする
		return false;
	}

	//選択中の文字を変更
	m_nFpsCnt++;


	if (m_nFpsCnt >= CHANGE_CNT)
	{//文字のスクロール移動のフレームチェック
		m_bChange = false;
		m_bUp = false;
		m_nFpsCnt = 0;
	}

	return false;
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CRankingInput::Draw()
{
	if (m_pPLName != nullptr)
	{
		m_pPLName->Draw();
	}

	if (m_bSetEnd)
	{
		return;
	}

	for (int nCnt = 0; nCnt < SET_PL_MAME; nCnt++)
	{
		if (m_pSetName[nCnt] == nullptr || nCnt == m_nCurrentValue)
		{
			continue;
		}

		D3DXVECTOR3 pos = m_pSetName[nCnt]->GetPos();
		if (pos.y >= m_Pos.y - SIZE_SET_MAME * SELECT_PL_MAME_HALF - SIZE_SET_MAME / 2.0f
			&& pos.y <= m_Pos.y + SIZE_SET_MAME * SELECT_PL_MAME_HALF + SIZE_SET_MAME / 2.0f)
		{
			m_pSetName[nCnt]->Draw();
		}
	}

	if (m_pSetName[m_nCurrentValue] != nullptr)
	{
		m_pSetName[m_nCurrentValue]->Draw();
	}
	
}