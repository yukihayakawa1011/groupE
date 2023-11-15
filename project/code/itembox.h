//==========================================================
//
// �A�C�e���{�b�N�X [itembox.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _ITEMBOX_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ITEMBOX_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CItemBox : public CTask
{
public:	// �N�ł��A�N�Z�X�\

	CItemBox();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CItemBox();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CItemBox *Create(void);
	void Emission(void);

	// �����o�֐�(�擾)
	static CItemBox* GetTop(void) { return m_pTop; }
	CItemBox* GetNext(void) { return m_pNext; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	static CItemBox *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CItemBox *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CItemBox *m_pPrev;			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CItemBox *m_pNext;			// ���̃I�u�W�F�N�g�ւ̃|�C���^
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
};

#endif

