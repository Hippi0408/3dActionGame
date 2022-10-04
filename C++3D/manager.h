//=============================================================================
//
// manager.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _MANAGER_H_			//このマクロ定義がされなかったら
#define _MANAGER_H_			//2重インクルード防止のマクロ定義
//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInput;
class CObject;
class CRenderer;
class CFade;

//*****************************************************************************
// 列挙型定義
//*****************************************************************************

enum MODE_TYPE
{
	TYPE_TITLE = 0,
	TYPE_GAME,
	TYPE_RESULT,
	TYPE_MAX
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{

public:
	

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw(int nFPS);
	LPDIRECT3DDEVICE9 GetDeviceManager();
	CObject *GetGameObject() { return m_pGame; }
	CFade *GetFadeObject() { return m_pFade; }
	void SetGemeObject(CObject *Object) {m_pGame = Object;}
	void ChangeMode(MODE_TYPE type);
	void NextMode(MODE_TYPE type, int nFadeCnt = 0);
	void SetScore(int nScore) { m_nScore = nScore; }
	int GetScore() { return m_nScore; }
	bool IsChangingMode() { return m_bChange; }
	int GetAirframe() { return m_nAirframe; }
	void SetAirframe(int nAirframe) { m_nAirframe = nAirframe; }

private:
	MODE_TYPE m_Mode;
	bool m_bChange;
	CRenderer *m_pRenderer;
	CObject *m_pGame;
	CInput *m_pInput;
	CFade *m_pFade;
	int m_nScore;
	int m_nFadeCnt;
	int m_nAirframe;
};
#endif

