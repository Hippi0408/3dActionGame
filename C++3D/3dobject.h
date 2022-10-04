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
	static const int MODEL_MAX_TEXTURE = 20;
	static const int MODEL_PATTERN_MAX = 20;

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
		D3DXMATRIX mtxWorld;				//ワールドマトリックス
		D3DXVECTOR3 posChildren;			//子の位置
		D3DXVECTOR3 pos;					//位置親
		D3DXVECTOR3 move;					//移動
		D3DXVECTOR3 vtxMin, vtxMax;			//モデルのサイズ
		D3DXVECTOR3 rot;					//向き
		int nPattn;							//モデルのパターン
	}Model;

public:
	C3DObject();
	~C3DObject() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set3DObject(int nPattn, D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos() { return m_Model.pos; }
	void SetPos(D3DXVECTOR3 pos) { m_Model.pos = pos; }
	void AddPos(D3DXVECTOR3 add) { m_Model.pos += add; }
	void SetRot(D3DXVECTOR3 rot) { m_Model.rot = rot; }
	void AddRot(D3DXVECTOR3 add) { m_Model.rot += add; }
	void SetSize(float fSize) { m_fSize = fSize; }

	D3DXVECTOR3 GetSize();

	static void SetModel(ModelPattern *pModel);
	static void UninitAllModel();

private:
	static ModelPattern m_ModelPattern[MODEL_PATTERN_MAX];
	Model m_Model;
	float m_fSize;						//サイズ
};

#endif