//=============================================================================
//
// explosion.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "explosion.h"
#include "texture.h"
#include "anim.h"
#include "effect.h"
#include "sound.h"

// ポリゴンの幅
CExplosion *CExplosion::m_pExplosion = nullptr;
const float CExplosion::SIZE_EXPLOSION = 16.0f;
int CExplosion::m_nExplosionTextIndex = -1;
int CExplosion::m_nExplosionCnt = 0;
int CExplosion::m_nExplosionNextCnt = 0;

// 爆発表示のPOS
const D3DXVECTOR3 CExplosion::BOSS_EXPLOSION_POS[MAX_BOSS_EXPLOSION] =
{
	D3DXVECTOR3(1107.0f ,138.0f ,0.0f),D3DXVECTOR3(552.0f ,125.0f ,0.0f),
	D3DXVECTOR3(1080.0f ,361.0f ,0.0f),D3DXVECTOR3(847.0f ,180.0f, 0.0f),
	D3DXVECTOR3(678.0f ,589.0f, 0.0f),D3DXVECTOR3(611.0f ,348.0f, 0.0f),
	D3DXVECTOR3(1050.0f ,584.0f, 0.0f),D3DXVECTOR3(636.0f ,755.0f, 0.0f),
	D3DXVECTOR3(542.0f, 746.0f, 0.0f),D3DXVECTOR3(1076.0f, 801.0f, 0.0f),
	D3DXVECTOR3(883.0f, 435.0f, 0.0f),D3DXVECTOR3(671.0f ,292.0f, 0.0f),
	D3DXVECTOR3(783.0f, 457.0f, 0.0f),D3DXVECTOR3(892.0f, 661.0f, 0.0f),
	D3DXVECTOR3(725.0f, 738.0f, 0.0f),D3DXVECTOR3(890.0f, 788.0f, 0.0f),
	D3DXVECTOR3(439.0f, 482.0f, 0.0f),D3DXVECTOR3(950.0f, 389.0f, 0.0f),
	D3DXVECTOR3(1038.0f, 312.0f, 0.0f),D3DXVECTOR3(798.0f, 117.0f, 0.0f),
	D3DXVECTOR3(630.0f, 117.0f, 0.0f),	D3DXVECTOR3(565.0f, 213.0f, 0.0f),
	D3DXVECTOR3(488.0f, 261.0f, 0.0f),	D3DXVECTOR3(798.0f, 270.0f, 0.0f),
	D3DXVECTOR3(965.0f, 507.0f, 0.0f),	D3DXVECTOR3(795.0f, 628.0f, 0.0f),
	D3DXVECTOR3(787.0f, 719.0f, 0.0f),	D3DXVECTOR3(973.0f, 164.0f ,0.0f),
	D3DXVECTOR3(1078.0f, 448.0f, 0.0f),	D3DXVECTOR3(1018.0f, 682.0f, 0.0f)
};
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CExplosion::CExplosion()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CExplosion::~CExplosion()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
void CExplosion::Init()
{
	m_pExplosion = new CExplosion;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CExplosion::Uninit()
{
	if (m_pExplosion != nullptr)
	{
		delete m_pExplosion;
		m_pExplosion = nullptr;
	}
}

//*****************************************************************************
// 爆発の実行
//*****************************************************************************
void CExplosion::CreateExplosion(D3DXVECTOR3 pos)
{

	CEffect::Effect effect;

	for (int nCnt = 0; nCnt < 9; nCnt++)
	{
		effect.fAttenuation = -0.01f;
		effect.fSizeX = 70.0f;
		effect.fSizeY = 70.0f;
		effect.nLife = 120;
		effect.fScaleDown = -1.5f;
		effect.nTextIndex = 0;
		effect.pos = pos;
		effect.Color = D3DXCOLOR(0.8f, 0.2f, 0.1f, 1.0f);
		effect.move = D3DXVECTOR3(cosf(D3DXToRadian(nCnt * 45)) * 2.0f
			, sinf(D3DXToRadian(nCnt * 45)) * 2.0f
			, 0.0f);
		effect.bAddColor = true;

		
		CEffect::CreateEffect(effect);
		CEffect::CreateEffect(effect);
		CEffect::CreateEffect(effect);
		CEffect::CreateEffect(effect);
		CEffect::CreateEffect(effect);
		CEffect::CreateEffect(effect);
	
	}
}

//*****************************************************************************
// ボスの用
//*****************************************************************************
void CExplosion::BossDiedExplosion()
{
	m_nExplosionCnt++;
	if (m_nExplosionCnt > MAX_BOSS_EXPLOSION_CNT)
	{
		m_nExplosionCnt = 0;

		CreateExplosion(BOSS_EXPLOSION_POS[m_nExplosionNextCnt]);
		//サウンド再生
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		m_nExplosionNextCnt++;

		if (m_nExplosionNextCnt >= MAX_BOSS_EXPLOSION)
		{
			m_nExplosionNextCnt = 0;
		}
	}
}
