//=============================================================================
//
// read.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "read.h"
#include <stdio.h>
#include "game.h"
#include "ranking.h"
#include "result.h"
#include "manager.h"
#include <assert.h>

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CRead::CRead()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CRead::~CRead()
{
}

//*****************************************************************************
// アンカーポイントのロード
//*****************************************************************************
void CRead::ReadAnchorPoint()
{
	//CEnemyManager *pEnemyManager = CGame::GetEnemy();

	FILE *pFile = nullptr;			//ファイルポインター宣言
	char cBff[LINE_MAX_READING_LENGTH];		//一行分読み取るための変数
	char cBffHead[LINE_MAX_READING_LENGTH];	//頭の文字を読み取るための変数
	int nDataNum = 0;

	//ファイルを開く
	pFile = fopen("data/TXT/SetAnchorPoint.txt", "r");

	if (pFile == nullptr)
	{//開けなかった時用
		assert(false);
	}
	//文字列の読み取りループ処理
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
	{
		//文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		if (strcmp(&cBffHead[0], "ANCHOR_POINT_START") == 0)
		{
			//アンカーポイントの数
			int nAnchorPointMax = 0;
			int nAnchorPointCnt = 0;
			//アンカーポイント
			D3DXVECTOR3 *pAnchorPoint = nullptr;

			//文字列の読み取りループ処理
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "ANCHOR_POINT_MAX") == 0)
				{
					if (pAnchorPoint != nullptr)
					{
						assert(false);
					}
					//一行の文字列から読み取り
					sscanf(cBff, "%s = %d", &cBffHead, &nAnchorPointMax);

					pAnchorPoint = new D3DXVECTOR3[nAnchorPointMax];
				}
				else if (strcmp(&cBffHead[0], "POS") == 0)
				{
					if (pAnchorPoint == nullptr)
					{
						assert(false);
					}
					//一行の文字列からPOSの読み取り
					sscanf(cBff, "%s = %f %f %f", &cBffHead, &pAnchorPoint[nAnchorPointCnt].x, &pAnchorPoint[nAnchorPointCnt].y, &pAnchorPoint[nAnchorPointCnt].z);

					nAnchorPointCnt++;

				}
				else if (strcmp(&cBffHead[0], "ANCHOR_POINT_END") == 0)
				{//テキストファイルを読み切った時
					break;
				}

				//保存中の文字列の初期化
				ZeroMemory(&cBff, sizeof(cBff));
				ZeroMemory(&cBffHead, sizeof(cBffHead));

			}

			//pEnemyManager->SetEnemyMoveType(nAnchorPointMax, pAnchorPoint);

			if (pAnchorPoint != nullptr)
			{
				delete[] pAnchorPoint;
				pAnchorPoint = nullptr;
			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{//テキストファイルを読み切った時
			break;
		}

		//保存中の文字列の初期化
		ZeroMemory(&cBff, sizeof(cBff));
		ZeroMemory(&cBffHead, sizeof(cBffHead));

	}
	//ファイルを閉じる
	fclose(pFile);
}

//*****************************************************************************
// グループのロード
//*****************************************************************************
//void CRead::ReadEnemy(StageNum Stage)
//{
//	CEnemyManager *pEnemyManager = CGame::GetEnemy();
//	FILE *pFile = nullptr;			//ファイルポインター宣言
//	char cBff[LINE_MAX_READING_LENGTH];		//一行分読み取るための変数
//	char cBffHead[LINE_MAX_READING_LENGTH];	//頭の文字を読み取るための変数
//
//	//ファイルを開く
//	switch (Stage)
//	{
//	case StageNum_01:
//		pFile = fopen("data/TXT/SetEnemyData01.txt", "r");
//		break;
//	case StageNum_02:
//		pFile = fopen("data/TXT/SetEnemyData02.txt", "r");
//		break;
//	case StageNum_03:
//		pFile = fopen("data/TXT/SetEnemyData03.txt", "r");
//		break;
//	case StageNum_04:
//		pFile = fopen("data/TXT/SetEnemyData04.txt", "r");
//		break;
//	case StageNum_05:
//		pFile = fopen("data/TXT/SetEnemyData05.txt", "r");
//		break;
//	case StageNum_06:
//		pFile = fopen("data/TXT/SetEnemyData06.txt", "r");
//		break;
//	default:
//		break;
//	}
//	
//
//	if (pFile == nullptr)
//	{//開けなかった時用
//		return;
//	}
//	
//	//文字列の読み取りループ処理
//	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
//	{
//		//文字列の分析
//		sscanf(cBff, "%s", &cBffHead);
//
//		if (strcmp(&cBffHead[0], "GROUP_START") == 0)
//		{//1グループの読込開始
//
//			//エネミーの数
//			int nEnemyCnt = 0;
//			int nEnemyMax = 0;
//			//エネミーの動き方
//			int *pMoveIndex = nullptr;
//			//エネミーの種類
//			int *pTypeIndex = nullptr;
//			//エネミーの初期位置
//			D3DXVECTOR3 *pInitPos = nullptr;
//
//			 //文字列の読み取りループ処理
//			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
//			{
//				//文字列の分析
//				sscanf(cBff, "%s", &cBffHead);
//				if (strcmp(&cBffHead[0], "ENEMY_NUM_MAX") == 0)
//				{//グループ内の敵の数
//					if (pMoveIndex != nullptr)
//					{
//						assert(false);
//					}
//
//					sscanf(cBff, "%s = %d", &cBffHead, &nEnemyMax);
//
//					pMoveIndex = new int[nEnemyMax];
//
//					pTypeIndex = new int[nEnemyMax];
//
//					pInitPos = new D3DXVECTOR3[nEnemyMax];
//
//				}
//				else if (strcmp(&cBffHead[0], "MOVE_INDEX") == 0)
//				{//敵の動き方の
//					if (pMoveIndex == nullptr)
//					{
//						assert(false);
//					}
//
//					//一行の文字列から読み取り
//					sscanf(cBff, "%s = %d", &cBffHead, &pMoveIndex[nEnemyCnt]);
//				}
//				else if (strcmp(&cBffHead[0], "INIT_POS") == 0)
//				{//敵の動き方の
//					if (pInitPos == nullptr)
//					{
//						assert(false);
//					}
//
//					//一行の文字列から読み取り
//					sscanf(cBff, "%s = %f %f %f", &cBffHead, &pInitPos[nEnemyCnt].x, &pInitPos[nEnemyCnt].y, &pInitPos[nEnemyCnt].z);
//					nEnemyCnt++;
//				}
//				else if (strcmp(&cBffHead[0], "ENEMY_TYPE") == 0)
//				{//敵の動き方の
//					if (pTypeIndex == nullptr)
//					{
//						assert(false);
//					}
//
//					//一行の文字列から読み取り
//					sscanf(cBff, "%s = %d", &cBffHead, &pTypeIndex[nEnemyCnt]);
//				}
//				else if (strcmp(&cBffHead[0], "GROUP_END") == 0)
//				{//1グループを読み切った時
//					break;
//				}
//
//				//保存中の文字列の初期化
//				ZeroMemory(&cBff, sizeof(cBff));
//				ZeroMemory(&cBffHead, sizeof(cBffHead));
//			}
//
//			//エネミーのグループの登録
//			pEnemyManager->SetGroupData(nEnemyMax, pMoveIndex, pTypeIndex, pInitPos);
//
//			
//			if (pTypeIndex != nullptr)
//			{
//				delete[] pTypeIndex;
//				pTypeIndex = nullptr;
//			}
//
//			if (pMoveIndex != nullptr)
//			{
//				delete[] pMoveIndex;
//				pMoveIndex = nullptr;
//			}
//
//			if (pInitPos != nullptr)
//			{
//				delete[] pInitPos;
//				pInitPos = nullptr;
//			}
//
//		}
//		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
//		{//テキストファイルを読み切った時
//			break;
//		}
//
//		//保存中の文字列の初期化
//		ZeroMemory(&cBff, sizeof(cBff));
//		ZeroMemory(&cBffHead, sizeof(cBffHead));
//
//	}
//
//	//ファイルを閉じる
//	fclose(pFile);
//}
//
////*****************************************************************************
//// ランキングのロード
////*****************************************************************************
//void CRead::ReadRanking(StageNum Stage,CRanking *pRnking)
//{
//	CManager *pManager = GetManager();
//	CResult *pResult = (CResult*)pManager->GetGameObject();
//	//ランキングスコア
//	int aRanking[CRanking::MAX_RANKING + 1] = {};
//	aRanking[CRanking::MAX_RANKING] = pManager->GetScore();
//	//ランキングネーム
//	CRanking::NameData NameData[CRanking::MAX_RANKING + 1] = {};
//	NameData[CRanking::MAX_RANKING] = {13,4,22,-1,-1};
//	int aAirframe[CRanking::MAX_RANKING + 1] = {};
//	aAirframe[CRanking::MAX_RANKING] = pManager->GetAirframe();
//
//	FILE *pFile = nullptr;			//ファイルポインター宣言
//	//ファイルを開く
//	switch (Stage)
//	{
//	case StageNum_01:
//		pFile = fopen("data/TXT/RankingStage01.txt", "r");
//		break;
//	case StageNum_02:
//		pFile = fopen("data/TXT/RankingStage02.txt", "r");
//		break;
//	case StageNum_03:
//		pFile = fopen("data/TXT/RankingStage03.txt", "r");
//		break;
//	case StageNum_04:
//		pFile = fopen("data/TXT/RankingStage04.txt", "r");
//		break;
//	case StageNum_05:
//		pFile = fopen("data/TXT/RankingStage05.txt", "r");
//		break;
//	case StageNum_06:
//		pFile = fopen("data/TXT/RankingStage06.txt", "r");
//		break;
//	default:
//		break;
//	}
//
//	if (pFile == nullptr)
//	{//開けなかった時用
//		return;
//	}
//	for (int nCnt = 0; nCnt < CRanking::MAX_RANKING; nCnt++)
//	{
//		fscanf(pFile, "%d,%d,%d,%d,%d = %d,%d",&NameData[nCnt].nNameNumIndex[0], &NameData[nCnt].nNameNumIndex[1],
//			&NameData[nCnt].nNameNumIndex[2], &NameData[nCnt].nNameNumIndex[3], &NameData[nCnt].nNameNumIndex[4]
//			,&aRanking[nCnt], &aAirframe[nCnt]);
//	}
//	//ファイルを閉じる
//	fclose(pFile);
//
//	int nScore = 0;
//	int nAirframe = 0;
//	CRanking::NameData namedata = {};
//
//	for (int nCnt1 = 0; nCnt1 < CRanking::MAX_RANKING; nCnt1++)
//	{
//		for (int nCnt2 = (nCnt1 + 1); nCnt2 < CRanking::MAX_RANKING + 1; nCnt2++)
//		{
//			if (aRanking[nCnt1] <= aRanking[nCnt2])
//			{
//				nScore = aRanking[nCnt2];
//				aRanking[nCnt2] = aRanking[nCnt1];
//				aRanking[nCnt1] = nScore;
//
//				for (int nName = 0;nName < CName::MAX_NAME_LENGTH;nName++)
//				{
//					namedata.nNameNumIndex[nName] = NameData[nCnt2].nNameNumIndex[nName];
//					NameData[nCnt2].nNameNumIndex[nName] = NameData[nCnt1].nNameNumIndex[nName];
//					NameData[nCnt1].nNameNumIndex[nName] = namedata.nNameNumIndex[nName];
//				}
//
//				nAirframe = aAirframe[nCnt2];
//				aAirframe[nCnt2] = aAirframe[nCnt1];
//				aAirframe[nCnt1] = nAirframe;
//			}
//		}
//	}
//
//	pRnking->Create(&NameData[0],&aRanking[0],&aAirframe[0]);
//}

//*****************************************************************************
// ランキングのセーブ
//*****************************************************************************
//void CRead::SaveRanking(StageNum Stage,const int *pRanking, const CRanking::NameData *pNameData, const int *pAirframe)
//{
//	FILE *pFile = nullptr;			//ファイルポインター宣言
//	//ファイルを開く
//	switch (Stage)
//	{
//	case StageNum_01:
//		pFile = fopen("data/TXT/RankingStage01.txt", "w");
//		break;
//	case StageNum_02:
//		pFile = fopen("data/TXT/RankingStage02.txt", "w");
//		break;
//	case StageNum_03:
//		pFile = fopen("data/TXT/RankingStage03.txt", "w");
//		break;
//	case StageNum_04:
//		pFile = fopen("data/TXT/RankingStage04.txt", "w");
//		break;
//	case StageNum_05:
//		pFile = fopen("data/TXT/RankingStage05.txt", "w");
//		break;
//	case StageNum_06:
//		pFile = fopen("data/TXT/RankingStage06.txt", "w");
//		break;
//	default:
//		break;
//	}
//
//	if (pFile == nullptr)
//	{//開けなかった時用
//		return;
//	}
//	for (int nCnt = 0; nCnt < CRanking::MAX_RANKING; nCnt++)
//	{
//		fprintf(pFile, "%d,%d,%d,%d,%d = %d,%d\n", pNameData[nCnt].nNameNumIndex[0], pNameData[nCnt].nNameNumIndex[1],
//			pNameData[nCnt].nNameNumIndex[2], pNameData[nCnt].nNameNumIndex[3], pNameData[nCnt].nNameNumIndex[4]
//			, pRanking[nCnt], pAirframe[nCnt]);
//	}
//	//ファイルを閉じる
//	fclose(pFile);
//}

//*****************************************************************************
// モデルの読み込み
//*****************************************************************************
void CRead::ReadModel(ModelTxt ModelTxt)
{
	FILE *pFile = nullptr;			//ファイルポインター宣言
	char cBff[LINE_MAX_READING_LENGTH];		//一行分読み取るための変数
	char cBffHead[LINE_MAX_READING_LENGTH];	//頭の文字を読み取るための変数

	//ファイルを開く
	switch (ModelTxt)
	{
	case TitleModel:
		pFile = fopen("data/TXT/SetModelDataTitle.txt", "r");
		break;
	case StageSelectModel:
		pFile = fopen("data/TXT/SetModelDataStageSelect.txt", "r");
		break;
	case GameStage01:
		pFile = fopen("data/TXT/SetModelDataGameStage01.txt", "r");
		break;
	case GameStage02:
		pFile = fopen("data/TXT/SetModelDataGameStage02.txt", "r");
		break;
	case GameStage03:
		pFile = fopen("data/TXT/SetModelDataGameStage03.txt", "r");
		break;
	case GameStage04:
		pFile = fopen("data/TXT/SetModelDataGameStage04.txt", "r");
		break;
	case GameStage05:
		pFile = fopen("data/TXT/SetModelDataGameStage05.txt", "r");
		break;
	case GameStage06:
		pFile = fopen("data/TXT/SetModelDataGameStage06.txt", "r");
		break;
	case ResultModel:
	case ModelTxtMax:
	default:
		assert(false);
		break;
	}

	if (pFile == nullptr)
	{//開けなかった時用
		assert(false);
	}

	//文字列の読み取りループ処理
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
	{
		//文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		if (strcmp(&cBffHead[0], "MODEL") == 0)
		{//xファイルのパス
			C3DObject::ModelPattern model;
			//モデルの一時保管場所の初期化
			ZeroMemory(&model, sizeof(model));

			char XFilePath[LINE_MAX_READING_LENGTH];

			//文字列の分析
			sscanf(cBff, "%s = %s", &cBffHead, &XFilePath);

			ReadXFile(XFilePath , &model);

			C3DObject::SetModel(&model);
		}
		else if (strcmp(&cBffHead[0], "END") == 0)
		{//読み切った時
			break;
		}

		//保存中の文字列の初期化
		ZeroMemory(&cBff, sizeof(cBff));
		ZeroMemory(&cBffHead, sizeof(cBffHead));
	}

	//ファイルを閉じる
	fclose(pFile);
}

//*****************************************************************************
// Xファイルの読み込み
//*****************************************************************************
void CRead::ReadXFile(char * sXFilePath, C3DObject::ModelPattern * pModel)
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(sXFilePath,
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		nullptr,
		&pModel->pBuffMatModel,
		nullptr,
		&pModel->nNumMatModel,
		&pModel->pMeshModel);

	pModel->bUse = true;

	// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)pModel->pBuffMatModel->GetBufferPointer();

	// 各メッシュのマテリアル情報を取得する
	for (int i = 0; i < (int)pModel->nNumMatModel; i++)
	{
		pModel->pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename != nullptr)
		{// マテリアルで設定されているテクスチャ読み込み
			D3DXCreateTextureFromFileA(pD3DDevice,
				pMat[i].pTextureFilename,
				&pModel->pTexture[i]);
		}
		else
		{
			pModel->pTexture[i] = nullptr;
		}
	}
}