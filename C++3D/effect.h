//=============================================================================
//
// effect.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _EFFECT_H_			//���̃}�N����`������Ȃ�������
#define _EFFECT_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "2dpolygon.h"

//*****************************************************************************
// �\����`
//*****************************************************************************
struct Effect
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�n�܂��POS
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�n�܂��ROT
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F
	float fSizeX = 0.0f;//�T�C�YX
	float fSizeY = 0.0f;//�T�C�YY
	float fScaleDown = 0.0f;//�k����
	float fAttenuation = 0.0f;//������
	int nLife = 0;//����
	int nTextIndex = 0;//�e�N�X�`���ԍ�
	bool bAddColor = false;//���Z����
};
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffect : public C2DPolygon
{
private:
	
public:

	CEffect();//�R���X�g���N�^
	~CEffect() override;//�f�X�g���N�^

	HRESULT Init() override;//������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	bool IsUnused() override;//�I������

	CEffect* GetNextEffect() { return m_pNextEffect; }
	CEffect* GetLastTimeEffect() { return m_pLastTimeEffect; }

	void SetNextEffect(CEffect* pNextEffect) { m_pNextEffect = pNextEffect; }
	void SetLastTimeEffect(CEffect* pLastTimeEffect) { m_pLastTimeEffect = pLastTimeEffect; }

	void SetEffect(const Effect effect);

	static void CreateEffect(const Effect effect);

	static void InitTextIndex();
	static void ALLUninit();//���ׂĂ̏I������
	static void ALLUpdate();//���ׂĂ̍X�V����
	static void ALLDraw();//���ׂĂ̕`�揈��

	static CEffect* GetTopEffect() { return m_pEffectTop; }
	static CEffect* GetCurrentEffect() { return m_pEffectCurrent; }
	static void SetTopEffect(CEffect* pEffectTop) { m_pEffectTop = pEffectTop; }
	static void SetCurrentEffect(CEffect* pEffectCurrent) { m_pEffectCurrent = pEffectCurrent; }

private:
	static int m_nEffectTextIndexAll;
	static CEffect* m_pEffectTop;//���X�g�\���̏���
	static CEffect* m_pEffectCurrent;//���X�g�\���̏I���
	CEffect* m_pNextEffect;
	CEffect* m_pLastTimeEffect;

	int m_nEffectTextIndex;
	float m_fScaleDown;//�k����
	float m_fAttenuation;//������
	int m_nLife;//����
	bool m_bAddColor;//���Z����
};

#endif