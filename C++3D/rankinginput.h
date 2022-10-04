//=============================================================================
//
// rankinginput.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RANKINGINPUT_H_			//このマクロ定義がされなかったら
#define _RANKINGINPUT_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "name.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBeeline;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRankingInput
{
public:
	static const float SIZE_SET_MAME;
	static const float SIZE_SET_SELECT_MAME;
	static const int SELECT_PL_MAME = 5; //選択用の数
	static const int SELECT_PL_MAME_HALF = 2; //選択用の数
	static const int SET_PL_MAME = 32; //選択用の数
	static const int SET_PL_MAME_HALF = SET_PL_MAME / 2; //選択用の数
	static const int CHANGE_CNT = 10; //選択用の数

	CRankingInput();
	~CRankingInput();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	bool Update();
	void Draw();
	
private:
	CName *m_pPLName;
	CBeeline *m_pSetName[SET_PL_MAME];
	D3DXVECTOR3 m_Pos;
	int m_nCurrentValue;//選択中の数値
	int m_nFpsCnt;
	int m_nSetNameNum;
	bool m_bChange;
	bool m_bUp;
	bool m_bSetEnd;
	int m_aPLNameIndex[CName::MAX_NAME_LENGTH];
};

#endif