//=============================================================================
//
// time.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TIME_H_			//このマクロ定義がされなかったら
#define _TIME_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;
enum MODE_TYPE;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTime
{
private:

public:

	CTime();
	~CTime();

	static HRESULT Init(D3DXVECTOR3 pos, int nDigit, int nNumerical, int nTime, float fSize);
	static void Uninit();
	static void Update(MODE_TYPE type);
	static void Draw();

	static int GetTime() { return m_nTime; }
	static void SetTimer(int nTime) { m_nTime = nTime; }

private:
	static CTime *m_pCTime;
	static CNumber *m_pTime;
	static int m_nTime;
	static int m_nFPS;
};

#endif