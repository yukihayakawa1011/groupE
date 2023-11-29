//==========================================================
//
// ���̏p [air.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLETASK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SAMPLETASK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CAir : public CTask
{
private:

	// ���\����
	struct SInfo
	{
		D3DXVECTOR3 pos;	// ���W
		D3DXVECTOR3 rot;	// ����
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		float fRange;		// ���a
	};

public:	// �N�ł��A�N�Z�X�\

	CAir();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CAir();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CAir *Create(const D3DXVECTOR3& pos, const int nId);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	int GetId(void) { return m_nId; }

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3& pos) { m_Info.pos = pos; }
	void Collision(void);
	void BindId(int nId) { m_nId = nId; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	int m_nId;	// �g�p��ID
	SInfo m_Info;	// ���
};

#endif
