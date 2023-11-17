//==========================================================
//
// ���Ƃ��� [gimmick_pitfall.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _PITFALL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PITFALL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

//�O���錾
class CModel;
class CGimmickButton;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGimmickPitFall : public CGimmick
{
private:
	enum FLOOR
	{
		FLOOR_LEFT = 0,
		FLOOR_RIGHT,
		FLOOR_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickPitFall();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickPitFall();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickPitFall *Create(const D3DXVECTOR3 pos);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)
	void IsOpen(const bool bOpen) { m_bOpen = bOpen; }
	void BindButton(CGimmickButton *pButton) { m_pButton = pButton; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick);

	// �����o�ϐ�
	CModel* m_apModel[FLOOR_MAX];		//���̏�
	CGimmickButton *m_pButton;		// �A������{�^��
	float m_fAngle;				//���̊J���
	bool m_bOpen;				//�����J���Ă��邩
};

#endif

