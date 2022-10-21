//=============================================================================
//
// camera.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "camera.h"
#include "manager.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCamera::CCamera()
{
	ZeroMemory(&m_Camera, sizeof(m_Camera));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCamera::~CCamera()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CCamera::Init()
{

	m_Camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	float fData = m_Camera.posV.x - m_Camera.posR.x;
	float fData1 = m_Camera.posV.z - m_Camera.posR.z;

	//m_Camera.fDistance = ThreeSquareTheorem(fData, fData1);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCamera::Uninit()
{
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCamera::Update()
{
	
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCamera::Draw()
{
}

//*****************************************************************************
// カメラのセット
//*****************************************************************************
void CCamera::SetCamera()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_Camera.mtxView);

	D3DXMatrixLookAtLH(&m_Camera.mtxView, &m_Camera.posV, &m_Camera.posR, &m_Camera.vecU);

	//ビューマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_Camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_Camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_Camera.mtxProjection,
		D3DXToRadian(45.0f),//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//アスペクト比
		10.0f,//どこからどこまでカメラで表示するか
		50000.0f);

	//プロジェクションマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_Camera.mtxProjection);
}

float CCamera::GetRot()
{
	D3DXVECTOR3 vec = m_Camera.posR - m_Camera.posV;

	float fAngle = atan2f(vec.x, vec.z);

	return fAngle;
}
