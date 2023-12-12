//===============================================
//
// �I�u�W�F�N�g(�}�b�v�̊���)�̏��� [object2D.h]
// Author : Soma Ishihara
//
//===============================================
#ifndef _OBJECT2D_SCROLL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT2D_SCROLL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object2D.h"

//==========================================================
// �I�u�W�F�N�g(�}�b�v�̊���)�̃N���X��`(�h���N���X)
//==========================================================
class CObject2DScroll : public CObject2D
{
public:	// �N�ł��A�N�Z�X�\

	CObject2DScroll();	//�f�t�H���g�R���X�g���N�^
	CObject2DScroll(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority = 3);	// �R���X�g���N�^
	virtual ~CObject2DScroll();	// �f�X�g���N�^
	
	// �����o�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static CObject2DScroll *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority = 3);
};

#endif