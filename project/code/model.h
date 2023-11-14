//==========================================================
//
// �K�w�\���̃��f������ [model.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MODEL_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MODEL_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

//**********************************************************
// �K�w�\�����f���N���X
//**********************************************************
class CModel : public CObject
{
public:	// �N�ł��A�N�Z�X�\

	CModel();	// �R���X�g���N�^
	~CModel();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel *Create(const char *pFileName);
	void SetParent(D3DXMATRIX *pMtx);
	void SetCharaParent(D3DXMATRIX *pMtx) { m_pCharacterMtx = pMtx; }
	void BindModelFile(int nIdx);
	void SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetCurrentPosition(void) { return m_CurPos; }
	D3DXVECTOR3 GetCurrentRotation(void) { return m_CurRot; }
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
	int GetId(void) { return m_nIdxModel; }

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);
	void SetCurrentPosition(const D3DXVECTOR3 pos);
	void SetCurrentRotation(const D3DXVECTOR3 rot);
	void SetDraw(bool bDraw = true) { m_bDraw = bDraw; }
	void SetShadow(bool bShadow = false) { m_bShadow = bShadow; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	int m_nIdxModel;		// ���f���ԍ�
	bool m_bChangeCol;		// �F�ύX�����邩�ǂ���
	bool m_bDraw;
	D3DMATERIAL9 m_ChangeMat;
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_CurPos;	// ���݂̈ʒu
	D3DXVECTOR3 m_CurRot;	// ���݂̌���
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXMATRIX *m_pParentMtx;	// �e�̃��[���h�}�g���b�N�X
	D3DXMATRIX *m_pCharacterMtx;	// �܂Ƃ߂Ă���e�̃}�g���b�N�X
	bool m_bShadow;		// �e���`�悷�邩�ۂ�
};

#endif
