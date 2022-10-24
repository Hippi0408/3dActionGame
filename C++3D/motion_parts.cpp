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
int CMotionParts::m_MotionPlayMotonNum[MAX_MOTION_ALL] = {};
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

	m_nModelObjNum = m_nModelMax;
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

	SetPos(INIT_POS);
	SetMotion(0);

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

	C3DObject::Uninit();

	delete this;
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CMotionParts::Update()
{
	// 目的のフレーム
	int nObjectiveFrame = m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].nFrame[m_nKey];

	// 目的のフレーム　＜　現在のフレーム
	if (nObjectiveFrame < m_nFrame)
	{
		// 次の位置までの計算
		NextMotionPosition();
	}

	// rotの加算
	AddRot(m_RotMove);
	// フレームの加算
	m_nFrame++;
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
		SetPos(m_pRarent->GetWorldPos());
		SetRot(m_pRarent->GetRot());
	}
	else
	{
		pD3DDevice->GetTransform(D3DTS_WORLD, &mtxRarent);
	}

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
	D3DXVECTOR3 rot = m_MotionKey[nMotionNum].aKey[m_nKey].rot;
	SetRot(rot);
}

//*****************************************************************************
// 次の位置までの計算
//*****************************************************************************
void CMotionParts::NextMotionPosition()
{
	//現在のKEYが目的を超えたら
	if (m_nKey > m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].nKeyMax)
	{
		m_nKey = 0;
	}

	//今の向き
	D3DXVECTOR3 nowRot = GetRot();
	//次の向き
	D3DXVECTOR3 nextRot = m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].aKey[m_nKey + 1].rot;
	//全体フレーム数に対しての割合
	float fFrameRatio = (float)100.0f / m_MotionKey[m_MotionPlayMotonNum[m_nModelObjNum]].nFrame[m_nKey + 1];

	//1フレームあたりの動く量
	D3DXVECTOR3 rotMove;
	rotMove = (nextRot - nowRot) / fFrameRatio;
	m_RotMove = rotMove;
	m_nKey++;
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
		pMotionParts->SetChildrenPos(pMotionData[nCnt].pos);//モデルの位置
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


	assert(false);
	return nullptr;
}

//*****************************************************************************
//モーションモデルの移動
//*****************************************************************************
void CMotionParts::MoveMotionModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nMotionNum)
{
	GetMotionPartsPointer(nMotionNum, 0)->SetPos(pos);
	GetMotionPartsPointer(nMotionNum, 0)->SetRot(rot);
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
