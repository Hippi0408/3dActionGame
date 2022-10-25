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
// 構造定義
//*****************************************************************************
// 構造体
struct MotionData
{
	int nModelPattern;//使用するモデルのインデック
	int nParentNum;//親の番号
	D3DXVECTOR3 pos;//親からの位置
	D3DXVECTOR3 rot;//親からの向き

};

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
		int nKeyMax;
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
	
	void SetPartsNum(int nPartsNum) { m_nPartsNum = nPartsNum; }
	void NextMotionPosition();
	void SetMotionRarent(CMotionParts* pMotionRarent) { m_pRarent = pMotionRarent; }
	bool GetMotionParts(int nMotionNum, int nPartsNum);//引数との一致があるかどうか
	bool GetMotionParts(int nMotionNum);//引数との一致があるかどうか

	static void ALLUninit();//すべての終了処理
	static void ALLUpdate();//すべての更新処理
	static void ALLDraw();//すべての描画処理

	static void SettingCompletion() { m_nModelMax++; }//動く物体の登録完了
	static CMotionParts* GetMotionParts() { return m_pMotionPartsTop; }
	static CMotionParts* GetCurrentMotionParts() { return m_pMotionPartsCurrent; }
	static void SetTopMotionParts(CMotionParts* pMotionPartsTop) { m_pMotionPartsTop = pMotionPartsTop; }
	static void SetCurrentMotionParts(CMotionParts* pMotionPartsCurrent) { m_pMotionPartsCurrent = pMotionPartsCurrent; }
	static int CreateMotionObj(MotionData* pMotionData,int nPartsMax);//動くOBJの生成
	static CMotionParts* GetMotionPartsPointer(int nMotionNum, int nPartsNum);

	static void MoveMotionModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nMotionNum);//モーションモデルの移動
	static void SetLight(D3DXVECTOR3 vec, int nMotionNum);//モーションモデルのライトベクトル
	static void AllSetShadowPos(D3DXVECTOR3 pos, int nMotionNum);//影の設定
private:
	static CMotionParts* m_pMotionPartsTop;//リスト構造の初め
	static CMotionParts* m_pMotionPartsCurrent;//リスト構造の終わり
	static int m_nModelMax;//登録した動く物体の数
	static int m_MotionPlayMotonNum[MAX_MOTION_ALL];//今再生中のモーション番号
	CMotionParts* m_pNextMotionParts;
	CMotionParts* m_pLastTimeMotionParts;

	CMotionParts* m_pRarent;		//親のポインタ
	KEY_SET m_MotionKey[MAX_MOTION];//登録した動きの情報
	D3DXVECTOR3 m_RotMove;			//1フレームあたりの動く量(rot)
	D3DXVECTOR3 m_RarentPosDistance;//親との距離
	int m_nModelObjNum;				//モーションオブジェクトの番号
	int m_nFrame;					//現在のフレーム
	int m_nKey;						//現在のキー
	int m_nPartsNum;				//動く物体の中の番号

};

#endif