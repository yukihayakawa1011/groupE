//==========================================================
//
// �I�u�W�F�N�g3D�̏����S�� [object3D.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _OBJECT3D_H_	 // ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT3D_H_	 // ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

// �O���錾
class CPlayer;

//**********************************************************
// �I�u�W�F�N�g3D�N���X�̒�`
//**********************************************************
class CObject3D : public CObject
{
public:	// �N�ł��A�N�Z�X�\

	CObject3D(int nPriority = 6);	// �R���X�g���N�^
	~CObject3D();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetpVtx(float fWidth, float fHeight);
	void SetTextureVtx(float fWidth, float fHeight);
	void BindTexture(int nIdx);
	void ZoomSize(CPlayer **ppPlayer, float fRadius);

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(float fWidth, float fHeight);
	float GetHeight(void) { return m_fHeight; }
	void SetCol(D3DXCOLOR col);
	float GetWidth(void) { return m_fWidth; }
	void SetMtx(void);
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	CObject2D *GetObject2D(void) { return NULL; }
	float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 &normal);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	int m_nIdxTexture;		// �e�N�X�`���ԍ�
	float m_fWidth;		// ��
	float m_fHeight;	// ����
};

#endif
