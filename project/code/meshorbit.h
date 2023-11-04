//==========================================================
//
//���b�V���\���̋O�Տ��� [meshorbit.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "mesh.h"

// �}�N����`
#define ORBIT_EDGE	(2)	// �p�ӂ���[�̐�

// �O�ՃN���X�̒�`(�h���N���X)
class CMeshOrbit : public CObjectMesh
{
public:		// �N�ł��A�N�Z�X�\

	// �O�Ճ^�C�v
	typedef enum
	{
		TYPE_NONE = 0,		// �����Ȃ�
		TYPE_PLAYER,		// �v���C���[
		TYPE_BULLET,		// �e
		TYPE_MAX
	}TYPE;

	CMeshOrbit();	// �R���X�g���N�^
	~CMeshOrbit();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	static CMeshOrbit *Create(D3DXMATRIX *pMtx, D3DXVECTOR3 UpSet, D3DXVECTOR3 DownSet, TYPE type = TYPE_NONE);

	// �����o�֐�(�ݒ�)
	void SetVtxInfo(void);
	void SetParent(D3DXMATRIX *pMtx) { m_pMtxParent = pMtx; }
	void SetOffSet(D3DXVECTOR3 Up, D3DXVECTOR3 Down) { m_aOffSet[0] = Up; m_aOffSet[1] = Down; }
	static int Get(void) { return m_nNumAll; }
	void Reset(void);
	void SetNor(D3DXVECTOR3 nor) { m_nor = nor; }
	void SetCol(D3DXCOLOR col);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetPlayer(void);
	void SetBullet(void);
	void SetNone(void);

	// �����o�ϐ�
	D3DXMATRIX *m_pMtxParent;			// �e�̃}�g���b�N�X�̃|�C���^
	D3DXVECTOR3 m_aOffSet[ORBIT_EDGE];	// ���[�̃I�t�Z�b�g
	D3DXCOLOR m_aCol[ORBIT_EDGE];		// ���[�̊�F
	D3DXVECTOR3 *m_pPos;				// �ʒu
	D3DXCOLOR *m_pCol;					// �F
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_nor;					// �ړ�����
	float m_fTimer;						// �^�C�}�[
	static int m_nNumAll;				// ����
	float m_fRadius;					// ���a
	TYPE m_type;						// ���
	D3DXMATRIX m_aMtxWorldPoint[ORBIT_EDGE];	// ���[�̃��[���h�}�g���b�N�X
};

#endif
