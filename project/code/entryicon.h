//==========================================================
//
// �`���[�g���A���̃G���g���[�̃A�C�R�� [entryicon.h]
// Author : Ryosuke Ohara
//
//==========================================================
#ifndef _ENTRYICON_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ENTRYICON_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

// �O���錾
class CObject2D;

// �}�N����`
#define NUM_PLAYER (4)  // �v���C���[�̍ő�l��

//===============================================
// �i���o�[�N���X�̒�`
//===============================================
class CEntryIcon : public CTask
{
public:	// �N�ł��A�N�Z�X�\

	CEntryIcon();	// �R���X�g���N�^
	~CEntryIcon();	// �f�X�g���N�^

	enum STATE
	{
		STATE_STANDBY = 0,          // �G���g���[��t��
		STATE_ENTRY,                // �G���g���[����
		STATE_MAX
	};

	// ���
	struct Info
	{
		D3DXVECTOR3 pos;            // �ʒu
		D3DXCOLOR col;              // �F
		STATE state;                // ���
		float fPolyWidth;	        // �I�u�W�F�N�g�̕�
		float fPolyHeight;	        // �I�u�W�F�N�g�̍���
		bool bEntry;                // �G���g���[�������ǂ���
	};

	// �����o�֐�
	//HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CEntryIcon *Create(void);
	static CEntryIcon *Create(D3DXVECTOR3 * pPos, D3DXMATRIX *Matrix, const float fUpHeight, const float fPolyWidth, const float fPolyHeight);
	CObject2D *GetObjectBill(void) { return m_apObject[0]; }

	// �����o�֐�(�ݒ�)
	void SetIdx(const int nIdx);
	void SetMixPosition(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetPolySize(const float fWidth, const float fHeight);

	// �����o�ϐ�
	Info m_Info;                        // ���
	CObject2D *m_apObject[NUM_PLAYER];	// �I�u�W�F�N�g2D�̃|�C���^
	int m_nIdx;                         // �C���f�b�N�X�ԍ�
};

#endif