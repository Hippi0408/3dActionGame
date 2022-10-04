//=============================================================================
//
// anim.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ANIM_H_			//このマクロ定義がされなかったら
#define _ANIM_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "2dpolygon.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CAnim : public C2DPolygon
{
private:
	// ポリゴンの幅
	static const float SIZE_ANIM;
	//アニメーションポリゴンの同時に出せる限界数
	static const int ANIM_MAX = 128;

public:
	CAnim();//コンストラクタ
	~CAnim();//デストラクタ

	static void ALLInit();//すべての初期化
	static void ALLUninit();//すべての終了処理
	static void ALLUpdate();//すべての更新処理
	static void ALLDraw();//すべての描画処理

	HRESULT Init() override;//初期化
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理

	bool IsUnused() override;//終了条件処理

	static void CreateAnim(D3DXVECTOR3 pos,int nAnimCnt, int nAnimXNumber, int nAnimYNumber, int nTextIndex);//アニメーションポリゴンの作成
	void SetAnim(int nAnimCnt, int nAnimXNumber, int nAnimYNumber) //セットアップ
	{ m_nAnimCnt = nAnimCnt; m_nAnimXNumber = nAnimXNumber; m_nAnimYNumber = nAnimYNumber; }

private:
	static CAnim *m_pAnim[ANIM_MAX];//クラスのポインタ配列
	D3DXVECTOR2 m_moveUV;//UVの移動量
	int m_nAnimCnt;//アニメーションのカウンタ
	int m_nAnimNumX;//横のアニメーション枚数
	int m_nAnimNumY;//縦のアニメーション枚数
	int m_nAnimTime;//次のアニメーションまでのフレーム数
	int m_nAnimXNumber;//現在の横枚数
	int m_nAnimYNumber;//現在の縦枚数
	

};

#endif