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
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CEntryIcon *Create(void);
	static CEntryIcon *Create(D3DXVECTOR3 Pos, const int nIdx, const float fPolyWidth, const float fPolyHeight);
	CObject2D *GetObjectBill(void) { return m_pObject; }
	void SetbEntry(bool bEntry) { m_Info.bEntry = bEntry; }
	void Entryed(void);
	void NoEntry(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetPolySize(const float fWidth, const float fHeight);

	// �����o�ϐ�
	Info m_Info;                        // ���
	CObject2D *m_pObject;	            // �I�u�W�F�N�g2D�̃|�C���^
	int m_nIdxPlayer;                   // �v���C���[�̔ԍ�
	bool m_bChangeTex;                  // �e�N�X�`�����ς���Ă���
};

#endif