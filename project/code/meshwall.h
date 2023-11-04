//==========================================================
//
// ���b�V���E�H�[���̏��� [meshwall.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESHWALL_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESHWALL_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "mesh.h"

//**********************************************************
// ���b�V���E�H�[���N���X�̒�`(�h���N���X)
//**********************************************************
class CMeshWall : public CObjectMesh
{
public:		// �N�ł��A�N�Z�X�\

	CMeshWall();	// �R���X�g���N�^
	~CMeshWall();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtxInfo(void);
	static CMeshWall *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		float fWidth, float fHeight, const char *pFileName, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);

	// �����o�֐�(�擾)
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	// �����o�֐�(�ݒ�)
	void SetSize(float fWidth, float fHeight);
	static void Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	static CMeshWall *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CMeshWall *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CMeshWall *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CMeshWall *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	float m_fWidth;		// ��
	float m_fHeight;	// ����
};

#endif
