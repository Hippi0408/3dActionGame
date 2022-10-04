//=============================================================================
//
// effect.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _EFFECT_H_			//このマクロ定義がされなかったら
#define _EFFECT_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "2dpolygon.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEffect : public C2DPolygon
{
private:
	// エフェクトの最大数
	static const int EFFECT_MAX = 2048;

public:

	struct Effect
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//始まりのPOS
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//始まりのROT
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
		D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//色
		float fSizeX = 0.0f;//サイズX
		float fSizeY = 0.0f;//サイズY
		float fScaleDown = 0.0f;//縮小率
		float fAttenuation = 0.0f;//減衰量
		int nLife = 0;//寿命
		int nTextIndex = 0;//テクスチャ番号
		bool bAddColor = false;//加算合成
	};

	CEffect();//コンストラクタ
	~CEffect() override;//デストラクタ

	HRESULT Init() override;//初期化
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	bool IsUnused() override;//終了条件

	void SetEffect(const Effect effect);

	static void CreateEffect(const Effect effect);
	static void ALLInit();//すべての初期化
	static void ALLUninit();//すべての終了処理
	static void ALLUpdate();//すべての更新処理
	static void ALLDraw();//すべての描画処理

private:
	static int m_nEffectTextIndex;
	static CEffect *m_pEffect[EFFECT_MAX];//ポインタの配列
	float m_fScaleDown;//縮小率
	float m_fAttenuation;//減衰量
	int m_nLife;//寿命
	bool m_bAddColor;//加算合成
};

#endif