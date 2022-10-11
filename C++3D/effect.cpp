//=============================================================================
//
// effect.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "effect.h"
#include "main.h"
#include "manager.h"
#include "texture.h"

int CEffect::m_nEffectTextIndexAll = 0;
CEffect *CEffect::m_pEffectTop = nullptr;
CEffect *CEffect::m_pEffectCurrent = nullptr;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEffect::CEffect()
{
	m_fAttenuation = 0.0f;
	m_fScaleDown = 0.0f;
	m_nLife = 0;
	m_bAddColor = false;

	if (m_pEffectTop == nullptr)
	{
		m_pEffectTop = this;
	}

	m_pNextEffect = nullptr;

	m_pLastTimeEffect = GetCurrentEffect();

	if (m_pLastTimeEffect != nullptr)
	{
		m_pLastTimeEffect->SetNextEffect(this);

	}
	SetCurrentEffect(this);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEffect::~CEffect()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEffect::Init()
{
	if (FAILED(C2DPolygon::Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEffect::Uninit()
{
	if(m_pEffectTop == this)
	{
		m_pEffectTop = m_pNextEffect;
	}
	
	if (m_pEffectCurrent == this)
	{
		m_pEffectCurrent = m_pLastTimeEffect;
	}

	if (m_pLastTimeEffect != nullptr)
	{
		m_pLastTimeEffect->SetNextEffect(m_pNextEffect);
	}

	if (m_pNextEffect != nullptr)
	{
		m_pNextEffect->SetLastTimeEffect(m_pLastTimeEffect);
	}

	C2DPolygon::Uninit();

	delete this;
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEffect::Update()
{
	AddDiagonalLine(m_fScaleDown, m_fScaleDown);
	AddColor(D3DXCOLOR(0.0f,0.0f,0.0,m_fAttenuation));
	m_nLife--;

	D3DXCOLOR color = GetColor();

	if (color.a < 0.0f)
	{
		SetColor(D3DXCOLOR(color.r, color.g, color.b, 0.0f));
	}
	else if (color.a > 1.0f)
	{
		SetColor(D3DXCOLOR(color.r, color.g, color.b, 1.0f));
	}

	float fsize = GetActualRadius();

	if (fsize < 0.0f)
	{
		SetDiagonalLine(0.0f, 0.0f);
	}

	C2DPolygon::Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEffect::Draw()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	if (m_bAddColor)
	{
		//���u�����f�B���O�����Z�����ɐݒ�
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	C2DPolygon::Draw();

	if (m_bAddColor)
	{
		//���u�����f�B���O�����̖߂�
		pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//*****************************************************************************
// �I������
//*****************************************************************************
bool CEffect::IsUnused()
{
	if (m_nLife < 0)
	{
		return true;
	}

	D3DXCOLOR color = GetColor();

	if (color.a <= 0.0f)
	{
		return true;
	}

	float fsize = GetActualRadius();

	if (fsize <= 0.0f)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// �G�t�F�N�g�̐ݒ�
//*****************************************************************************
void CEffect::SetEffect(const Effect effect)
{
	m_fAttenuation = effect.fAttenuation;
	m_fScaleDown = effect.fScaleDown;
	m_nLife = effect.nLife;
	m_bAddColor = effect.bAddColor;
	SetDiagonalLine(effect.fSizeX, effect.fSizeY);

	if (effect.nTextIndex == 0)
	{
		m_nEffectTextIndex = m_nEffectTextIndexAll;
	}
	else
	{
		m_nEffectTextIndex = effect.nTextIndex;
	}

	SetTextIndex(m_nEffectTextIndex);
	SetUp(effect.pos, effect.rot, effect.move);
	SetColor(effect.Color);
	SetPolygon();
}

//*****************************************************************************
// �G�t�F�N�g�̐���
//*****************************************************************************
void CEffect::CreateEffect(const Effect effect)
{

	CEffect* pEffect = new CEffect;

	if (FAILED(pEffect->Init()))
	{
		return;
	}

	pEffect->SetEffect(effect);

}

//*****************************************************************************
// �����e�N�X�`���̐ݒ�
//*****************************************************************************
void CEffect::InitTextIndex()
{
	m_nEffectTextIndexAll = CTexture::LoadTexture("data/TEXTURE/effect.jpg");
}

//*****************************************************************************
// ALL�I������
//*****************************************************************************
void CEffect::ALLUninit()
{
	CEffect* pEffect = m_pEffectTop;

	while (pEffect != nullptr)
	{
		CEffect* pEffectNext = pEffect->GetNextEffect();
		pEffect->Uninit();
		pEffect = pEffectNext;
	}
}

//*****************************************************************************
// ALL�X�V����
//*****************************************************************************
void CEffect::ALLUpdate()
{
	CEffect* pEffect = m_pEffectTop;

	while (pEffect != nullptr)
	{
		pEffect->Update();
		//pEffect = pEffect->GetNextEffect();

		if (pEffect->IsUnused())
		{
			CEffect* pEffectBreak = pEffect;
			pEffect = pEffectBreak->GetNextEffect();
			pEffectBreak->Uninit();
		}
		else
		{
			pEffect = pEffect->GetNextEffect();
		}
	}
}

//*****************************************************************************
// ALL�`�揈��
//*****************************************************************************
void CEffect::ALLDraw()
{
	CEffect* pEffect = m_pEffectTop;

	while (pEffect != nullptr)
	{
		pEffect->Draw();
		pEffect = pEffect->GetNextEffect();
	}
}