//=============================================================================
//
// motion_parts.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _MOTION_PARTS_H_			//このマクロ定義がされなかったら
#define _MOTION_PARTS_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "3dobject.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMotionParts : public C3DObject
{
private:
	static const D3DXVECTOR3 INIT_POS;
	static const int MAX_MOTION = 1;
	static const int MAX_KEY = 10;
	static const int MAX_MOTION_ALL = 4;
public:

	// 構造体
	struct KEY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	};

	struct KEY_SET
	{
		int nFrame[MAX_KEY];
		KEY aKey[MAX_KEY];
		bool bLoop;
	};

	CMotionParts();
	~CMotionParts() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	bool IsUnused();

	CMotionParts* GetNextMotionParts() { return m_pNextMotionParts; }
	CMotionParts* GetLastTimeMotionParts() { return m_pLastTimeMotionParts; }

	void SetNextMotionParts(CMotionParts* pNextMotionParts) { m_pNextMotionParts = pNextMotionParts; }
	void SetLastTimeMotionParts(CMotionParts* pLastTimeMotionParts) { m_pLastTimeMotionParts = pLastTimeMotionParts; }
	void SetMotion(int nMotionNum);
	void SettingCompletion() { m_nModelMax++; }

	static void ALLUninit();//すべての終了処理
	static void ALLUpdate();//すべての更新処理
	static void ALLDraw();//すべての描画処理

	static CMotionParts* GetMotionParts() { return m_pMotionPartsTop; }
	static CMotionParts* GetCurrentMotionParts() { return m_pMotionPartsCurrent; }
	static void SetTopMotionParts(CMotionParts* pMotionPartsTop) { m_pMotionPartsTop = pMotionPartsTop; }
	static void SetCurrentMotionParts(CMotionParts* pMotionPartsCurrent) { m_pMotionPartsCurrent = pMotionPartsCurrent; }

private:
	static CMotionParts* m_pMotionPartsTop;//リスト構造の初め
	static CMotionParts* m_pMotionPartsCurrent;//リスト構造の終わり
	static int m_nModelMax;
	static int m_MotionPlayMotonNum[MAX_MOTION_ALL];
	static int m_MotionPlayKeyNum[MAX_KEY];
	CMotionParts* m_pNextMotionParts;
	CMotionParts* m_pLastTimeMotionParts;

	CMotionParts* m_pRarent;
	KEY_SET m_MotionKey[MAX_MOTION];
	int m_nModelObjNum;				//モーションオブジェクトの番号


};

#endif