//==========================================================
//
// �V���{���ʂ̏��� [meshballoon.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESH_BALLOON_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESH_BALLOON_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "mesh.h"

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CMeshBalloon : public CObjectMesh
{
public:	// �N�ł��A�N�Z�X�\

	//CMeshBalloon();	// �R���X�g���N�^
	CMeshBalloon(int nPriOrity = 4);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CMeshBalloon();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtxInfo(void);
	void SetColor(float fDiff);
	static CMeshBalloon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetSize(float fLength);

	// �����o�ϐ�
	float m_fLength;	// ����
	float m_fRot;		// �꒸�_�̊p�x
	float m_fHeightRot;	// y���p�x
};

#endif

