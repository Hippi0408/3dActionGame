//=============================================================================
//
// read.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _READ_H_			//このマクロ定義がされなかったら
#define _READ_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "ranking.h"
#include "3dobject.h"
#include "manager.h"

//*****************************************************************************
// 列挙型定義
//*****************************************************************************
enum ModelTxt
{
	TitleModel = 0,
	StageSelectModel,
	GameStage01,
	GameStage02,
	GameStage03,
	GameStage04,
	GameStage05,
	GameStage06,
	ResultModel,
	ModelTxtMax
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRead
{
	static const int LINE_MAX_READING_LENGTH = 256;
public:

	CRead();
	~CRead();
	void ReadAnchorPoint();
	//void ReadEnemy(StageNum Stage);
	void ReadXFile(char *sXFilePath ,C3DObject::ModelPattern *pModel);
	void ReadModel(ModelTxt ModelTxt);
	//void ReadRanking(StageNum Stage,CRanking *pRnking);
	//void SaveRanking(StageNum Stage,const int *pRanking ,const CRanking::NameData *pNameData, const int *pAirframe);

private:
	
};

#endif