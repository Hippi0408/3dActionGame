//=============================================================================
//
// motion_parts.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _MOTION_PARTS_H_			//���̃}�N����`������Ȃ�������
#define _MOTION_PARTS_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "3dobject.h"

//*****************************************************************************
// �\����`
//*****************************************************************************
// �\����
struct MotionData
{
	int nModelPattern;//�g�p���郂�f���̃C���f�b�N
	int nParentNum;//�e�̔ԍ�
	D3DXVECTOR3 pos;//�e����̈ʒu
	D3DXVECTOR3 rot;//�e����̌���

};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMotionParts : public C3DObject
{
private:
	static const D3DXVECTOR3 INIT_POS;
	static const int MAX_MOTION = 1;
	static const int MAX_KEY = 10;
	static const int MAX_MOTION_ALL = 4;
public:

	// �\����
	struct KEY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	};

	struct KEY_SET
	{
		int nFrame[MAX_KEY];
		KEY aKey[MAX_KEY];
		int nKeyMax;
		bool bLoop;
	};

	CMotionParts();
	~CMotionParts() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	bool IsUnused();

	CMotionParts* GetNextMotionParts() { return m_pNextMotionParts; }
	CMotionParts* GetLastTimeMotionParts() { return m_pLastTimeMotionParts; }

	void SetNextMotionParts(CMotionParts* pNextMotionParts) { m_pNextMotionParts = pNextMotionParts; }
	void SetLastTimeMotionParts(CMotionParts* pLastTimeMotionParts) { m_pLastTimeMotionParts = pLastTimeMotionParts; }
	void SetMotion(int nMotionNum);
	
	void SetPartsNum(int nPartsNum) { m_nPartsNum = nPartsNum; }
	void NextMotionPosition();
	void SetMotionRarent(CMotionParts* pMotionRarent) { m_pRarent = pMotionRarent; }
	bool GetMotionParts(int nMotionNum, int nPartsNum);//�����Ƃ̈�v�����邩�ǂ���
	bool GetMotionParts(int nMotionNum);//�����Ƃ̈�v�����邩�ǂ���

	static void ALLUninit();//���ׂĂ̏I������
	static void ALLUpdate();//���ׂĂ̍X�V����
	static void ALLDraw();//���ׂĂ̕`�揈��

	static void SettingCompletion() { m_nModelMax++; }//�������̂̓o�^����
	static CMotionParts* GetMotionParts() { return m_pMotionPartsTop; }
	static CMotionParts* GetCurrentMotionParts() { return m_pMotionPartsCurrent; }
	static void SetTopMotionParts(CMotionParts* pMotionPartsTop) { m_pMotionPartsTop = pMotionPartsTop; }
	static void SetCurrentMotionParts(CMotionParts* pMotionPartsCurrent) { m_pMotionPartsCurrent = pMotionPartsCurrent; }
	static int CreateMotionObj(MotionData* pMotionData,int nPartsMax);//����OBJ�̐���
	static CMotionParts* GetMotionPartsPointer(int nMotionNum, int nPartsNum);

	static void MoveMotionModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nMotionNum);//���[�V�������f���̈ړ�
	static void SetLight(D3DXVECTOR3 vec, int nMotionNum);//���[�V�������f���̃��C�g�x�N�g��
	static void AllSetShadowPos(D3DXVECTOR3 pos, int nMotionNum);//�e�̐ݒ�
private:
	static CMotionParts* m_pMotionPartsTop;//���X�g�\���̏���
	static CMotionParts* m_pMotionPartsCurrent;//���X�g�\���̏I���
	static int m_nModelMax;//�o�^�����������̂̐�
	static int m_MotionPlayMotonNum[MAX_MOTION_ALL];//���Đ����̃��[�V�����ԍ�
	CMotionParts* m_pNextMotionParts;
	CMotionParts* m_pLastTimeMotionParts;

	CMotionParts* m_pRarent;		//�e�̃|�C���^
	KEY_SET m_MotionKey[MAX_MOTION];//�o�^���������̏��
	D3DXVECTOR3 m_RotMove;			//1�t���[��������̓�����(rot)
	D3DXVECTOR3 m_RarentPosDistance;//�e�Ƃ̋���
	int m_nModelObjNum;				//���[�V�����I�u�W�F�N�g�̔ԍ�
	int m_nFrame;					//���݂̃t���[��
	int m_nKey;						//���݂̃L�[
	int m_nPartsNum;				//�������̂̒��̔ԍ�

};

#endif