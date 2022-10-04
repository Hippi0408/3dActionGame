//=============================================================================
//
// camera.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _CAMERA_H_			//このマクロ定義がされなかったら
#define _CAMERA_H_			//2重インクルード防止のマクロ定義

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
class CCamera : public CObject
{
private:
	//カメラ構造体
	typedef struct
	{
		D3DXVECTOR3 posV;		//視点
		D3DXVECTOR3 posVDest;		//視点
		D3DXVECTOR3 posR;		//注視点
		D3DXVECTOR3 posRDest;		//注視点
		D3DXVECTOR3 vecU;		//上方向ベクトル
		D3DXMATRIX mtxProjection; //プロジェクションマトリックス
		D3DXMATRIX mtxView;		  //ビューマトリックス
		float fDistance;			//視点か注視点のまでの距離
	}Camera;

public:
	CCamera();
	~CCamera() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetCamera();

	void SetPosV(D3DXVECTOR3 posV) { m_Camera.posV = posV; }
	void SetPosR(D3DXVECTOR3 posR) { m_Camera.posR = posR; }
	void SetVecU(D3DXVECTOR3 vecU) { m_Camera.vecU = vecU; }

private:
	Camera m_Camera;
};

#endif