//=============================================================================
//
// motion_parts.cpp
// Author : kozuna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "motion_parts.h"
#include "manager.h"
#include <assert.h>

const D3DXVECTOR3 CMotionParts::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CMotionParts *CMotionParts::m_pMotionPartsTop = nullptr;
CMotionParts *CMotionParts::m_pMotionPartsCurrent = nullptr;
int CMotionParts::m_nModelMax = 0;
int CMotionParts::m_nMotionPlayMotonNum[MAX_MOTION_ALL] = {};
int CMotionParts::m_nMotionRegistrationNum[MAX_MOTION_ALL] = {};
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CMotionParts::CMotionParts()
{
	m_nFrame = 0;
	m_nKey = 0;
	m_pRarent = nullptr;

	if (m_pMotionPartsTop == nullptr)
	{
		m_pMotionPartsTop = this;
	}

	m_pNextMotionParts = nullptr;

	m_pLastTimeMotionParts = GetCurrentMotionParts();

	if (m_pLastTimeMotionParts != nullptr)
	{
		m_pLastTimeMotionParts->SetNextMotionParts(this);

	}
	SetCurrentMotionParts(this);

	m_nModelObjNum = 0;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CMotionParts::~CMotionParts()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CMotionParts::Init()
{
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CMotionParts::Uninit()
{
	if (m_pMotionPartsTop == this)
	{
		m_pMotionPartsTop = m_pNextMotionParts;
	}

	if (m_pMotionPartsCurrent == this)
	{
		m_pMotionPartsCurrent = m_pLastTimeMotionParts;
	}

	if (m_pLastTimeMotionParts != nullptr)
	{
		m_pLastTimeMotionParts->SetNextMotionParts(m_pNextMotionParts);
	}

	if (m_pNextMotionParts != nullptr)
	{
		m_pNextMotionParts->SetLastTimeMotionParts(m_pLastTimeMotionParts);
	}

	for (int nMotion = 0; nMotion < 1; nMotion++)
	{
		if (m_MotionKey[nMotion].pKey != nullptr)
		{
			delete[] m_MotionKey[nMotion].pKey;
			m_MotionKey[nMotion].pKey = nullptr;
		}
	}


	C3DObject::Uninit();

	delete this;
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CMotionParts::Update()
{
	// 目的のフレーム
	int nObjectiveFrame = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey].nFrame;

	// フレームの加算
	m_nFrame++;
	// 目的のフレーム　＜　現在のフレーム
	if (nObjectiveFrame < m_nFrame)
	{
		// 次の位置までの計算
		NextMotionPosition();
		m_nFrame = 0;
	}

	// rotの加算
	AddRot(m_RotMove);

	D3DXVECTOR3 rot = GetRot();

	if (rot.x >= D3DX_PI)
	{
		rot.x -= D3DX_PI * 2;
	}
	else if (rot.x <= -D3DX_PI)
	{
		rot.x += D3DX_PI * 2;
	}

	if (rot.y >= D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}
	else if (rot.y <= -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}
	
	if (rot.z >= D3DX_PI)
	{
		rot.z -= D3DX_PI * 2;
	}
	else if (rot.z <= -D3DX_PI)
	{
		rot.z += D3DX_PI * 2;
	}

	SetRot(rot);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CMotionParts::Draw()
{
	D3DXMATRIX mtxRarent;
	D3DXMATRIX mtx;
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();
	// 親が存在する場合
	if (m_pRarent != nullptr)
	{
		mtxRarent = m_pRarent->GetMatrix();
	}
	else
	{
		pD3DDevice->GetTransform(D3DTS_WORLD, &mtxRarent);
	}
	
	//自身のマトリックスの計算
	CalculationMatrix();
	mtx = GetMatrix();

	//モデルのマトリックス　＊　親のワールドマトリックス
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRarent);

	SetMatrix(mtx);

	C3DObject::Draw();
}

//*****************************************************************************
//	終了条件処理
//*****************************************************************************
bool CMotionParts::IsUnused()
{
	return false;
}

//*****************************************************************************
//	モーション番号指定でセットする
//*****************************************************************************
void CMotionParts::SetMotion(int nMotionNum)
{
	m_nFrame = 0;
	m_nKey = 0;
	D3DXVECTOR3 rot = m_MotionKey[nMotionNum].pKey[m_nKey].rot;
	SetRot(rot);
}

//*****************************************************************************
//実際の動きの登録
//*****************************************************************************
void CMotionParts::SetMotionData(KEY_SET KeyData)
{
	m_MotionKey[0].bLoop = KeyData.bLoop;
	m_MotionKey[0].nKeyMax = KeyData.nKeyMax;
	m_MotionKey[0].pKey = KeyData.pKey;
}

//*****************************************************************************
// 次の位置までの計算
//*****************************************************************************
void CMotionParts::NextMotionPosition()
{
	D3DXVECTOR3 nowRot, nextRot;
	int nFrameRatio;

	int nDestKey = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].nKeyMax;

	//現在のKEYが目的を超えたら
	if (m_nKey >= nDestKey - 1)
	{
		//今の向き
		nowRot = GetRot();
		//次の向き
		nextRot = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[0].rot;
		//全体フレーム数に対しての割合
		nFrameRatio = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[0].nFrame;
	}
	else
	{
		//今の向き
		nowRot = GetRot();
		//次の向き
		nextRot = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey + 1].rot;
		//全体フレーム数に対しての割合
		nFrameRatio = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey + 1].nFrame;
	}
	
	

	//1フレームあたりの動く量
	D3DXVECTOR3 rotMove;
	

	D3DXVECTOR3 rot = (nextRot - nowRot);

	if (rot.x >= D3DX_PI)
	{
		rot.x -= D3DX_PI * 2;
	}
	else if (rot.x <= -D3DX_PI)
	{
		rot.x += D3DX_PI * 2;
	}

	if (rot.y >= D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}
	else if (rot.y <= -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	if (rot.z >= D3DX_PI)
	{
		rot.z -= D3DX_PI * 2;
	}
	else if (rot.z <= -D3DX_PI)
	{
		rot.z += D3DX_PI * 2;
	}

	rotMove = rot / nFrameRatio;
	m_RotMove = rotMove;

	m_nKey++;
	if (m_nKey >= nDestKey)
	{
		m_nKey = 0;
	}
	
}

//*****************************************************************************
// 引数との一致があるかどうか
//*****************************************************************************
bool CMotionParts::GetMotionParts(int nMotionNum, int nPartsNum)
{
	if (m_nModelObjNum == nMotionNum
		&& m_nPartsNum == nPartsNum)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// 引数との一致があるかどうか
//*****************************************************************************
bool CMotionParts::GetMotionParts(int nMotionNum)
{
	if (m_nModelObjNum == nMotionNum)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// ALL終了処理
//*****************************************************************************
void CMotionParts::ALLUninit()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		CMotionParts* pMotionPartsNext = pMotionParts->GetNextMotionParts();
		pMotionParts->Uninit();
		pMotionParts = pMotionPartsNext;
	}
}

//*****************************************************************************
// ALL更新処理
//*****************************************************************************
void CMotionParts::ALLUpdate()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		pMotionParts->Update();

		if (pMotionParts->IsUnused())
		{
			CMotionParts* pMotionPartsBreak = pMotionParts;
			pMotionParts = pMotionPartsBreak->GetNextMotionParts();
			pMotionPartsBreak->Uninit();
		}
		else
		{
			pMotionParts = pMotionParts->GetNextMotionParts();
		}
	}
}

//*****************************************************************************
// ALL描画処理
//*****************************************************************************
void CMotionParts::ALLDraw()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		pMotionParts->Draw();
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
// 動くOBJの生成
//*****************************************************************************
int CMotionParts::CreateMotionObj(MotionData* pMotionData, int nPartsMax)
{
	for (int nCnt = 0; nCnt < nPartsMax; nCnt++)
	{
		CMotionParts* pMotionParts = new CMotionParts;

		if (FAILED(pMotionParts->Init()))
		{
			assert(false);
		}

		pMotionParts->SetPartsNum(nCnt);//一つのモーションの中の番号
		pMotionParts->SetModelPattnNum(pMotionData[nCnt].nModelPattern);//使用するモデルのインデックス
		pMotionParts->SetPos(pMotionData[nCnt].pos);//モデルの位置
		pMotionParts->SetRot(pMotionData[nCnt].rot);//モデルの向き
		
		if (pMotionData[nCnt].nParentNum >= 0)
		{
			//親の設定
			pMotionParts->SetMotionRarent(GetMotionPartsPointer(m_nModelMax, pMotionData[nCnt].nParentNum));
		}
		
	}

	int nModelNum = m_nModelMax;

	//動く物体の登録完了
	SettingCompletion();

	return nModelNum;

}

//*****************************************************************************
// 条件に合うポインタを返す
//*****************************************************************************
CMotionParts * CMotionParts::GetMotionPartsPointer(int nMotionNum, int nPartsNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum, nPartsNum))
		{
			return pMotionParts;
		}

		pMotionParts = pMotionParts->GetNextMotionParts();
	}

	return nullptr;
}

//*****************************************************************************
//モーションモデルの移動
//*****************************************************************************
void CMotionParts::MoveMotionModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nMotionNum)
{
	GetMotionPartsPointer(nMotionNum, 0)->SetParentPos(pos);
	GetMotionPartsPointer(nMotionNum, 0)->SetParentRot(rot);
}

//*****************************************************************************
//モーションモデルのライトベクトル
//*****************************************************************************
void CMotionParts::SetLight(D3DXVECTOR3 vec, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			pMotionParts->SetLightVec(vec);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
//影の設定
//*****************************************************************************
void CMotionParts::AllSetShadowPos(D3DXVECTOR3 pos, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			D3DXVECTOR3 ShadowPos = pMotionParts->GetWorldPos();
			ShadowPos.y = pos.y;
			pMotionParts->SetShadowPos(ShadowPos);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
//モーションの登録
//*****************************************************************************
void CMotionParts::SetMotionFileData(const MotionMoveData MotionMoveData, int nMotionNum)
{
	CMotionParts* pMotionParts = nullptr;//一時保管場所
	int nPartsNum = 0;//カウンター
	pMotionParts = GetMotionPartsPointer(nMotionNum, nPartsNum);//条件に合うポインタの獲得
	while (pMotionParts != nullptr)
	{
		//一時保管場所
		KEY_SET KeySet;

		KeySet.pKey = new KEY[MotionMoveData.nKeyMax];

		for (int nCnt = 0; nCnt < MotionMoveData.nKeyMax; nCnt++)
		{
			//フレーム
			KeySet.pKey[nCnt].nFrame = MotionMoveData.pMotionKeyData[nCnt].nFrame;
			//Pos
			KeySet.pKey[nCnt].pos = MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData[nPartsNum].pos;
			//Rot
			KeySet.pKey[nCnt].rot = MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData[nPartsNum].rot;
		}

		//ループ設定
		KeySet.bLoop = MotionMoveData.bLoop;
		//キーの最大
		KeySet.nKeyMax = MotionMoveData.nKeyMax;

		//登録
		pMotionParts->SetMotionData(KeySet);

		//pMotionParts->SetPos(INIT_POS);
		pMotionParts->SetMotion(0);


		nPartsNum++;//カウンターを進める
		pMotionParts = GetMotionPartsPointer(nMotionNum, nPartsNum);//条件に合うポインタの獲得
	}
	
}
