//==========================================================
//
// �G�ړ��|�C���g [point.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _POINT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _POINT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

//==========================================================
// �G�ړ��|�C���g�̃N���X��`
//==========================================================
class CPoint : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CPoint();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CPoint();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CPoint *Create(void);

	// �����o�֐�(�擾)
	int GetRegistPointNum(void) { return m_nRegistPointNum; }
	D3DXVECTOR3 GetPoint(const int nNum) { return m_pPosPoint[nNum % m_nRegistPointNum]; }
	static CPoint* GetTop(void) { return m_pTop; }
	static int GetNumAll(void) { return m_nNumAll; }
	CPoint* GetNext(void) { return m_pNext; }

	// �����o�֐�(�ݒ�)
	void SetNum(const int nNum);
	void AddPoint(const D3DXVECTOR3 pos);

private:	// �����������A�N�Z�X�\
	// �����o�ϐ�
	//���X�g
	static CPoint* m_pTop;
	static CPoint* m_pCur;
	CPoint* m_pPrev;
	CPoint* m_pNext;
	static int m_nNumAll;	//����

	//�f�[�^
	D3DXVECTOR3* m_pPosPoint;	//�ړ��|�C���g�i���I�m�ہj
	int m_nPointNum;			//�ړ��|�C���g��
	int m_nRegistPointNum;		//�o�^�ς݈ړ��|�C���g��
};

#endif
