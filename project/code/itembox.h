//==========================================================
//
// �A�C�e���{�b�N�X [itembox.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _ITEMBOX_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ITEMBOX_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

//�O���錾
class CObjectX;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CItemBox : public CGimmick
{
public:	// �N�ł��A�N�Z�X�\

	CItemBox();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CItemBox();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CItemBox *Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 rot);
	void Emission(void);

	// �����o�֐�(�擾)
	static CItemBox* GetTop(void) { return m_pTop; }
	CItemBox* GetNext(void) { return m_pNext; }

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick);

	// �����o�ϐ�
	static CItemBox *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CItemBox *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CItemBox *m_pPrev;			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CItemBox *m_pNext;			// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CObjectX* m_pObj;			// �I�u�W�F�N�g

	int m_nCounter;				//�r�oCT
};

#endif

