//==========================================================
//
// ���b�V���h�[���̏��� [meshcylinder.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESHDOME_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESHDOME_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "mesh.h"

//**********************************************************
// ���b�V���h�[���N���X�̒�`(�h���N���X)
//**********************************************************
class CMeshDome : public CObjectMesh
{
public:		// �N�ł��A�N�Z�X�\

	CMeshDome();	// �R���X�g���N�^
	~CMeshDome();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtxInfo(void);
	void SetColor(float fDiff);
	static CMeshDome *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength, float fHeight, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetSize(float fLength, float fHeight);

	// �����o�֐�
	float m_fHeight;	// ����
	float m_fLength;	// ����
	float m_fRot;		// �꒸�_�̊p�x
	float m_fHeightRot;	// y���p�x
};

#endif