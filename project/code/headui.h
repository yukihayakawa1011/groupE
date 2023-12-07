//===============================================
//
// ���̏�ɏo��UI���� [overheadui.h]
// Author : Ryosuke Ohara
//
//===============================================
#ifndef _HEADUI_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _HEADUI_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

// �}�N����`
#define NUM_DIGIT (2)  // ����

// �O���錾
class CObjectBillboard;

//===============================================
// �i���o�[�N���X�̒�`
//===============================================
class CHeadUI : public CTask
{
public:	// �N�ł��A�N�Z�X�\

	CHeadUI();	// �R���X�g���N�^
	~CHeadUI();	// �f�X�g���N�^

				// �����o�֐�
				//HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CHeadUI *Create(void);
	static CHeadUI *Create(D3DXVECTOR3 * pPos, D3DXMATRIX *Matrix, const float fUpHeight, const float fPolyWidth, const float fPolyHeight);
	CObjectBillboard *GetObjectBill(void) { return m_apObject[0]; }

	// �����o�֐�(�ݒ�)
	void SetIdx(const int nIdx);
	void SetParent(D3DXVECTOR3 *pPos) { m_pPos = pPos; }
	void SetUpHeight(const float fHeight) { m_fUpHeight = fHeight; }
	void SetMixPosition(void);

private:	// �����������A�N�Z�X�\

			// �����o�֐�
	void SetPolySize(const float fWidth, const float fHeight);
	
	void SetMtxParent(D3DXMATRIX *mtxParent);

	// �����o�ϐ�
	D3DXVECTOR3 *m_pPos;	        // �e�̍��W
	D3DXMATRIX m_mtxWorld[NUM_DIGIT];          // ���[���h�}�g���b�N�X
	D3DXMATRIX *m_mtxParent;         // �e�̃}�g���b�N�X
	float m_fUpHeight;	            // �グ�鍂��
	float m_fPolyWidth;	            // �I�u�W�F�N�g�̕�
	float m_fPolyHeight;	        // �I�u�W�F�N�g�̍���
	CObjectBillboard *m_apObject[NUM_DIGIT];	// �r���{�[�h�̃I�u�W�F�N�g�̃|�C���^
	int m_nIdx;                     // �C���f�b�N�X�ԍ�
};

#endif