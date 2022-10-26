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
#include "motion_parts.h"

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
			char XFilePath[LINE_MAX_READING_LENGTH];

			//文字列の分析
			sscanf(cBff, "%s = %s", &cBffHead, &XFilePath);

			ReadXFile(XFilePath);
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
// モーションファイルの読み込み
//*****************************************************************************
int CRead::ReadMotion(char * sXFilePath)
{
	FILE *pFile = NULL;			//ファイルポインター宣言

	char cBff[LINE_MAX_READING_LENGTH];		//一行分読み取るための変数
	char cBffHead[LINE_MAX_READING_LENGTH];	//頭の文字を読み取るための変数
	//モデル構造体の保存用変数宣言
	MotionData* pMotiondata = nullptr;
	//各モデルのインデックス
	int* pMotionIndex = nullptr;

	int nMotionMax = 0;//モデルの数

	int nSettingCompletionParts = 0;//設定の完了したパーツ数

	int nSettingCompletionModel = 0;//設定の完了したモデル数

	//セットモーションオブジェクト
	int nMotionNum = 0;

	//ファイルを開く
	pFile = fopen(sXFilePath, "r");

	if (pFile == nullptr)
	{//開けなかった時用
		assert(false);
	}

	//文字列の読み取りループ処理
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
	{
		//文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		if (strcmp(&cBffHead[0], "NUM_MODEL") == 0)
		{//モデル数
			if (pMotionIndex != nullptr)
			{
				assert(false);
			}
			sscanf(cBff, "%s = %d", &cBffHead, &nMotionMax);
			pMotionIndex = new int[nMotionMax];
		}
		else if (strcmp(&cBffHead[0], "MODEL_FILENAME") == 0)
		{//Xファイルの相対パス用

			char sPath[LINE_MAX_READING_LENGTH];		//相対パス保存用

			//一行の文字列から相対パスの読み取り
			sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);

			//Xファイルの読み込み
			pMotionIndex[nSettingCompletionModel] = ReadXFile(sPath);
			nSettingCompletionModel++;
		}
		else if (strcmp(&cBffHead[0], "CHARACTERSET") == 0)
		{//動く物の配置用

		 //モデルセットに必要な情報読み取りループ処理
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "NUM_PARTS") == 0)
				{//パーツ数
				 //文字列の分析
					if (pMotiondata != nullptr)
					{
						assert(false);
					}
					int nPartsMax = 0;//パーツの数
					sscanf(cBff, "%s = %d", &cBffHead, &nPartsMax);

					pMotiondata = new MotionData[nPartsMax];
				}
				else if (strcmp(&cBffHead[0], "MOVE") == 0)
				{//移動量
				 //文字列の分析
					//sscanf(cBff, "%s = %f", &cBffHead, &);
				}
				else if (strcmp(&cBffHead[0], "JUMP") == 0)
				{//ジャンプ量
				 //文字列の分析
					//sscanf(cBff, "%s = %f", &cBffHead, &);
				}
				else if (strcmp(&cBffHead[0], "PARTSSET") == 0)
				{//モデルひとつのセット用のデータ読み取り
				 //インデックス保存用
				
					//モデルセットに必要な情報読み取りループ処理
					while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
					{
						//文字列の分析
						sscanf(cBff, "%s", &cBffHead);

						if (strcmp(&cBffHead[0], "INDEX") == 0)
						{//使用するモデルの番号
						 //文字列の分析
							int nNum = 0;
							sscanf(cBff, "%s = %d", &cBffHead, &nNum);
							pMotiondata[nSettingCompletionParts].nModelPattern = pMotionIndex[nNum];
						}
						else if (strcmp(&cBffHead[0], "PARENT") == 0)
						{//親の番号
						 //文字列の分析
							sscanf(cBff, "%s = %d", &cBffHead, &pMotiondata[nSettingCompletionParts].nParentNum);
						}
						else if (strcmp(&cBffHead[0], "POS") == 0)
						{//モデルの位置
						 //文字列の分析
							D3DXVECTOR3 pos;
							sscanf(cBff, "%s = %f%f%f", &cBffHead, &pos.x, &pos.y, &pos.z);
							pMotiondata[nSettingCompletionParts].pos = pos;
						}
						else if (strcmp(&cBffHead[0], "ROT") == 0)
						{//モデルの向き
						 //文字列の分析
							D3DXVECTOR3 rot;
							sscanf(cBff, "%s = %f%f%f", &cBffHead, &rot.x, &rot.y, &rot.z);
							pMotiondata[nSettingCompletionParts].rot = rot;
						}
						else if (strcmp(&cBffHead[0], "END_PARTSSET") == 0)
						{//モデル１パーツのセット終了
							nSettingCompletionParts++;
							break;
						}

						//保存中の文字列の初期化
						ZeroMemory(&cBff, sizeof(cBff));
						ZeroMemory(&cBffHead, sizeof(cBffHead));

					}
				}
				else if (strcmp(&cBffHead[0], "END_CHARACTERSET") == 0)
				{//モデルのデータ読み取り終了
					//セットモーションオブジェクト
					nMotionNum = CMotionParts::CreateMotionObj(pMotiondata, nSettingCompletionParts);

					if (pMotiondata != nullptr)
					{
						delete[] pMotiondata;
						pMotiondata = nullptr;
					}

					break;
				}

				//保存中の文字列の初期化
				ZeroMemory(&cBff, sizeof(cBff));
				ZeroMemory(&cBffHead, sizeof(cBffHead));

			}
		}
		else if (strcmp(&cBffHead[0], "MOTIONSET") == 0)
		{//モーション用のデータ読み取り
			MotionMoveData MotionMoveData;
			MotionMoveData.pMotionKeyData = nullptr;

			int nMotionKeyMax = 0;
			int nMotionKey = 0;//使ったキーの数のカウント
			//モデルセットに必要な情報読み取りループ処理
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "LOOP") == 0)
				{//このモーションはループ再生するかどうか
				 //文字列の分析
					int nLoop;
					sscanf(cBff, "%s = %d", &cBffHead, &nLoop);

					if (nLoop != 0)
					{
						MotionMoveData.bLoop = true;
					}
				}
				else if (strcmp(&cBffHead[0], "NUM_KEY") == 0)
				{//モーションのキー数
				 //文字列の分析
					sscanf(cBff, "%s = %d", &cBffHead, &nMotionKeyMax);

					if (MotionMoveData.pMotionKeyData != nullptr)
					{
						assert(false);
					}
					MotionMoveData.nKeyMax = nMotionKeyMax;//キー数の保存
					MotionMoveData.pMotionKeyData = new MotionKeyData[nMotionKeyMax];//キーごとに必要なデータの確保

					for (int nKey = 0; nKey < nMotionKeyMax; nKey++)
					{
						//初期化
						MotionMoveData.pMotionKeyData[nKey].pMotionPartsData = nullptr;
					}
				}
				else if (strcmp(&cBffHead[0], "KEYSET") == 0)
				{//モデルパーツのモーション設定


					//パーツごとに必要な情報を確保
					if (MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData != nullptr)
					{
						assert(false);
					}
					MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData = new MotionPartsData[nSettingCompletionParts];

					

					int nModelPasCnt = 0;		//モデルパーツのセット番号

					//モデルセットに必要な情報読み取りループ処理
					while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
					{
						//文字列の分析
						sscanf(cBff, "%s", &cBffHead);

						if (strcmp(&cBffHead[0], "FRAME") == 0)
						{//このモーションは何フレーム数で再生するかチェック
						 //文字列の分析
							int nFrame = 0;
							sscanf(cBff, "%s = %d", &cBffHead, &nFrame);
							if (nFrame == 0)
							{//再生フレーム数が0の場合1にする
								nFrame = 1;
							}
							MotionMoveData.pMotionKeyData[nMotionKey].nFrame = nFrame;
						}
						else if (strcmp(&cBffHead[0], "KEY") == 0)
						{//モーションの１パーツのセット
						 //モデルセットに必要な情報読み取りループ処理
							while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
							{
								//文字列の分析
								sscanf(cBff, "%s", &cBffHead);

								if (strcmp(&cBffHead[0], "POS") == 0)
								{//モーション中の１パーツの位置
								 //文字列の分析
									D3DXVECTOR3 pos;
									sscanf(cBff, "%s = %f%f%f", &cBffHead,&pos.x,&pos.y,&pos.z);

									MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData[nModelPasCnt].pos = pos;
								}
								else if (strcmp(&cBffHead[0], "ROT") == 0)
								{//モーション中の１パーツの向き
								 //文字列の分析
									D3DXVECTOR3 rot;
									sscanf(cBff, "%s = %f%f%f", &cBffHead, &rot.x, &rot.y, &rot.z);

									MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData[nModelPasCnt].rot = rot;
								}
								else if (strcmp(&cBffHead[0], "END_KEY") == 0)
								{//モーション中の１パーツのセット終了
									nModelPasCnt++;//１パーツのセット終了
									break;
								}

								//保存中の文字列の初期化
								ZeroMemory(&cBff, sizeof(cBff));
								ZeroMemory(&cBffHead, sizeof(cBffHead));

							}
						}
						else if (strcmp(&cBffHead[0], "END_KEYSET") == 0)
						{
							nMotionKey++;//設定したキー数のカウント
							break;
						}

						//保存中の文字列の初期化
						ZeroMemory(&cBff, sizeof(cBff));
						ZeroMemory(&cBffHead, sizeof(cBffHead));

					}
				}
				else if (strcmp(&cBffHead[0], "END_MOTIONSET") == 0)
				{//モデルパーツのモーション設定終了
					//モーションの登録
					CMotionParts::SetMotionFileData(MotionMoveData, nMotionNum);

					for (int nCnt = 0; nCnt < nMotionKey; nCnt++)
					{
						if (MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData != nullptr)
						{
							delete[] MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData;
							MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData = nullptr;
						}
					}

					if (MotionMoveData.pMotionKeyData != nullptr)
					{
						delete[] MotionMoveData.pMotionKeyData;
						MotionMoveData.pMotionKeyData = nullptr;
					}

					break;
				}

				//保存中の文字列の初期化
				ZeroMemory(&cBff, sizeof(cBff));
				ZeroMemory(&cBffHead, sizeof(cBffHead));

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

	

	if (pMotionIndex != nullptr)
	{
		delete[] pMotionIndex;
		pMotionIndex = nullptr;
	}

	return nMotionNum;
}

//*****************************************************************************
// Xファイルの読み込み
//*****************************************************************************
int CRead::ReadXFile(char * sXFilePath)
{
	C3DObject::ModelPattern Model;

	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(sXFilePath,
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		nullptr,
		&Model.pBuffMatModel,
		nullptr,
		&Model.nNumMatModel,
		&Model.pMeshModel);

	Model.bUse = true;

	// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)Model.pBuffMatModel->GetBufferPointer();

	// 各メッシュのマテリアル情報を取得する
	for (int i = 0; i < (int)Model.nNumMatModel; i++)
	{
		Model.pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename != nullptr)
		{// マテリアルで設定されているテクスチャ読み込み
			D3DXCreateTextureFromFileA(pD3DDevice,
				pMat[i].pTextureFilename,
				&Model.pTexture[i]);
		}
		else
		{
			Model.pTexture[i] = nullptr;
		}
	}

	//モデルの登録
	return C3DObject::SetModel(&Model);
}