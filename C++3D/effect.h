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
// 構造定義
//*****************************************************************************
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
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEffect : public C2DPolygon
{
private:
	
public:

	CEffect();//コンストラクタ
	~CEffect() override;//デストラクタ

	HRESULT Init() override;//初期化
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	bool IsUnused() override;//終了条件

	CEffect* GetNextEffect() { return m_pNextEffect; }
	CEffect* GetLastTimeEffect() { return m_pLastTimeEffect; }

	void SetNextEffect(CEffect* pNextEffect) { m_pNextEffect = pNextEffect; }
	void SetLastTimeEffect(CEffect* pLastTimeEffect) { m_pLastTimeEffect = pLastTimeEffect; }

	void SetEffect(const Effect effect);

	static void CreateEffect(const Effect effect);

	static void InitTextIndex();
	static void ALLUninit();//すべての終了処理
	static void ALLUpdate();//すべての更新処理
	static void ALLDraw();//すべての描画処理

	static CEffect* GetTopEffect() { return m_pEffectTop; }
	static CEffect* GetCurrentEffect() { return m_pEffectCurrent; }
	static void SetTopEffect(CEffect* pEffectTop) { m_pEffectTop = pEffectTop; }
	static void SetCurrentEffect(CEffect* pEffectCurrent) { m_pEffectCurrent = pEffectCurrent; }

private:
	static int m_nEffectTextIndexAll;
	static CEffect* m_pEffectTop;//リスト構造の初め
	static CEffect* m_pEffectCurrent;//リスト構造の終わり
	CEffect* m_pNextEffect;
	CEffect* m_pLastTimeEffect;

	int m_nEffectTextIndex;
	float m_fScaleDown;//縮小率
	float m_fAttenuation;//減衰量
	int m_nLife;//寿命
	bool m_bAddColor;//加算合成
};

#endif