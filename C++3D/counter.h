//=============================================================================
//
// counter.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _COUNTER_H_			//このマクロ定義がされなかったら
#define _COUNTER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCounter
{
private:

public:

	CCounter();//コンストラクタ
	~CCounter();//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, int nDigit, float fSize, int nNumerical);//初期化
	void Uninit();//終了処理
	void Draw();//描画処理
	void Add(int nAdd);
	int GetCount() { return m_nCounter; }

	static void AllUninit();
	static void AllDraw();

	static CCounter *Create();
	static void AddCounter(int nAdd);//カウントを進める
	static int GetCounter() { return m_pCCounter->GetCount(); }

private:
	static CCounter *m_pCCounter;//自分のポインタ
	CNumber *m_pCounter;//数値を描画するクラス
	int m_nCounter;//現在の数値
};

#endif