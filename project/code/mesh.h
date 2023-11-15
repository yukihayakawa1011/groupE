//==========================================================
//
// ���b�V���̊Ǘ� [mesh.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESH_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESH_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

//**********************************************************
// ���b�V���N���X�̒�`(�h���N���X)
//**********************************************************
class CObjectMesh : public CObject
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	// ���b�V�����
	enum TYPE
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_FIELD,		// ��
		TYPE_WALL,		// ��
		TYPE_DOME,		// �h�[��
		TYPE_CYLINDER,	// �V�����_�[
		TYPE_MAX
	};

public:		// �N�ł��A�N�Z�X�\

	//CMesh();	
	CObjectMesh(int nPriority = 3);	// �R���X�g���N�^
	~CObjectMesh();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void);
	virtual void Update(void) = 0;
	virtual void Draw(void);
	void NotMtxDraw(void);
	virtual void SetVtxInfo(void) = 0;
	void BindTexture(int nIdx);
	void Create(int nWidth, int nHeight);

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);
	void SetMtx(D3DXMATRIX MtxWorld) { m_mtxWorld = MtxWorld; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
	int GetVertex(void) { return m_nVertex; }
	int GetIndex(void) { return m_nIndex; }
	int GetNumWidth(void) { return m_nNumWidth; }
	int GetNumHeight(void) { return m_nNumHeight; }

protected:	// �h���N���X������A�N�Z�X�\

	// �����o�֐�
	void SetVtx(void);

	// �����o�ϐ�
	VERTEX_3D *m_pVtx;	// ���_���

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void CreateVertex(void);
	void CreateIndex(void);
	void SetIndex(void);
	void SetSlowCol(void);

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdexBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	int m_nNumHeight;	// ��������
	int m_nNumWidth;	// ������
	int m_nVertex;		// ���_��
	int m_nIndex;		// �`��ԍ���
	TYPE m_Type;		// ���
};

#endif