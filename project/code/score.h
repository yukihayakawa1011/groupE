//===============================================
//
// �����S�ʂ̏��� [score.h]
// Author : Ryosuke Ohhara
//
//===============================================
#ifndef _SCORE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SCORE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "number.h"

//�}�N����`
#define NUM_SCORE   (8)  // �X�R�A�̌���

//===============================================
// �i���o�[�N���X�̒�`
//===============================================
class CScore : public CNumber
{
public:	// �N�ł��A�N�Z�X�\

	CScore();	// �R���X�g���N�^
	~CScore();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore *Create(void);
	static CScore *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	CNumber *GetObject2D(void) { return m_apNumber[0]; }
	void PolygonDelete(void);

	// �����o�֐�(�ݒ�)
	void SetIdx(const int nIdx);

	// �����o�֐�(�擾)
	int GetIdx(void) { return m_nIdx; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	CNumber *m_apNumber[NUM_SCORE];	// 2D�I�u�W�F�N�g�̃|�C���^
	int m_nIdx;	// �����̔ԍ�
};

#endif