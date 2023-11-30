//==========================================================
//
// ���b�V���V�����_�[�̏��� [meshcylinder.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESHCYLINDER_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESHCYLINDER_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "mesh.h"

//**********************************************************
// ���b�V���V�����_�[�N���X�̒�`(�h���N���X)
//**********************************************************
class CMeshCylinder : public CObjectMesh
{
public:		// �N�ł��A�N�Z�X�\

	//CMeshCylinder();	// �R���X�g���N�^
	CMeshCylinder(int nPriority = 2);
	~CMeshCylinder();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetVtxInfo(void);
	static CMeshCylinder *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength,
		float fHeight, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);
	void SetLength(const float fLength);
	float GetLength(void) { return m_fLength; }
	void SetCol(D3DXCOLOR col);

protected:

	// �����o�֐�
	float m_fHeight;	// ����
	float m_fLength;	//����
	float m_fRot;		//�꒸�_�̊p�x

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetSize(float fLength, float fHeight);

};

//**********************************************************
// ���b�V�����N���X�̒�`(�h���N���X)
//**********************************************************
class CMeshSmake : public CMeshCylinder
{
public:		// �N�ł��A�N�Z�X�\

	CMeshSmake(int nPriority = 5);	// �R���X�g���N�^
	~CMeshSmake();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshSmake *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength,
		float fHeight, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetSize(float fLength, float fHeight);
	void SetCol(D3DXCOLOR col);
	void SetHeight(float fHeight);

	// �����o�֐�
	D3DXCOLOR m_col;	// �F
	D3DXVECTOR2 m_tex;	// �e�N�X�`�����W

};

#endif
