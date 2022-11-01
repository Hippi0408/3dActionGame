//=============================================================================
//
// 3dobject.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _3DOBJECT_H_			//このマクロ定義がされなかったら
#define _3DOBJECT_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class C3DObject : public CObject
{
public:
	static const int MODEL_MAX_TEXTURE = 30;
	static const int MODEL_PATTERN_MAX = 30;

	//モデルパターン構造体
	typedef struct
	{
		LPD3DXMESH pMeshModel;		//メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffMatModel;	//マテリアル情報へのポインタ
		DWORD nNumMatModel;				//マテリアル情報の数
		LPDIRECT3DTEXTURE9 pTexture[MODEL_MAX_TEXTURE];		// テクスチャへのポインタ
		bool bUse;
	}ModelPattern;

	//モデル構造体
	typedef struct
	{
		D3DXVECTOR3* pNormalPolygon;		//面法線
		D3DXVECTOR3* pTopPos;				//頂点の位置
		D3DXMATRIX mtxWorld;				//ワールドマトリックス
		D3DXVECTOR3 posParent;				//位置親
		D3DXVECTOR3 rotParent;				//向き親
		D3DXVECTOR3 rot;					//向き
		D3DXVECTOR3 pos;					//位置
		D3DXVECTOR3 move;					//移動
		D3DXVECTOR3 vtxMin, vtxMax;			//モデルのサイズ
		D3DXVECTOR3 posMove;				//位置動く時用
		int nPattn;							//モデルのパターン
	}Model;

public:
	C3DObject();
	virtual ~C3DObject() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	void Set3DObject(int nPattn, D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos() { return m_Model.pos; }
	D3DXVECTOR3 GetRot() { return m_Model.rot; }
	void SetPos(D3DXVECTOR3 pos) { m_Model.pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_Model.rot = rot; }
	D3DXVECTOR3 GetParentPos() { return m_Model.posParent; }
	D3DXVECTOR3 GetParentRot() { return m_Model.rotParent; }
	void SetParentPos(D3DXVECTOR3 pos) { m_Model.posParent = pos; }
	void SetParentRot(D3DXVECTOR3 rot) { m_Model.rotParent = rot; }
	void AddParentPos(D3DXVECTOR3 add) { m_Model.posParent += add; }
	void SetPosMove(D3DXVECTOR3 pos) { m_Model.posMove = pos; }
	D3DXVECTOR3 GetPosMove() { return m_Model.posMove; }
	void AddPosMove(D3DXVECTOR3 add) { m_Model.posMove += add; }
	void AddPos(D3DXVECTOR3 add) { m_Model.pos += add; }
	void AddRot(D3DXVECTOR3 add) { m_Model.rot += add; }
	void SetSize(float fSize) { m_fSize = fSize; }
	void SetLightVec(D3DXVECTOR3 LightVec) { m_LightVec = LightVec; }
	void SetShadowPos(D3DXVECTOR3 shadowpos) { m_ShadowPos = shadowpos; }
	D3DXVECTOR3 GetWorldPos();
	D3DXVECTOR3 GetWorldRot();
	D3DXMATRIX GetMatrix() { return m_Model.mtxWorld; }
	void SetMatrix(D3DXMATRIX mtx) { m_Model.mtxWorld = mtx; }
	D3DXVECTOR3 GetSize();
	void SetModelPattnNum(int nPattnNum) { m_Model.nPattn = nPattnNum; }
	void CalculationMatrix();
	D3DXVECTOR3 NormalizationRot(D3DXVECTOR3 In);
	void SetNormal();			//法線設定
	void UpdateNormal();		//法線の向きの更新
	virtual D3DXVECTOR3 Collision(D3DXVECTOR3 pos);//当たり判定

	static int SetModel(ModelPattern *pModel);
	static void UninitAllModel();

private:
	static ModelPattern m_ModelPattern[MODEL_PATTERN_MAX];
	Model m_Model;
	float m_fSize;//サイズ
	D3DXVECTOR3 m_LightVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_ShadowPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};

#endif