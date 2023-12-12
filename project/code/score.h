//===============================================
//
// �����S�ʂ̏��� [score.h]
// Author : Ryosuke Ohara
//
//===============================================
#ifndef _SCORE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SCORE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CNumber;

// �}�N����`
#define NUM_SCORE  (8)  //�X�R�A�̌���

//===============================================
// �i���o�[�N���X�̒�`
//===============================================
class CScore
{
public:	// �N�ł��A�N�Z�X�\

	CScore();	// �R���X�g���N�^
	~CScore();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, int nDesit, float fGap, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore *Create(void);
	static CScore *Create(D3DXVECTOR3 pos, int nDesit, float fGap, float fWidth, float fHeight);
	//CObject2D *GetObject2D(void) { return m_pObject2D; }
	void PolygonDelete(void);

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //�e�N�X�`�����o�C���h

	void AddScore(int nScore);  // �X�R�A���Z����
	void LowerScore(int nScore);  // �X�R�A���Z����

	// �����o�֐�(�ݒ�)
	void SetIdx(const int nIdx);
	void SetScore(int nScore);
	void SetClo(D3DXCOLOR col);
	void SetPosition(const D3DXVECTOR3& pos);

	// �����o�֐�(�擾)
	int GetIdx(void) { return m_nIdx; }
	int GetScore(void) { return m_nNumScore; }
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	CNumber *m_apNumber[NUM_SCORE];	// �i���o�[�ւ̃|�C���^
	D3DXVECTOR3 m_pos;				// �ʒu
	float m_fHeight;				// ����
	float m_fWidth;				    // ��
	float m_fGap;
	int m_nDesit;                   // ����
	int m_nIdx;					    // �����̔ԍ�
	int m_nNumScore;			    // �X�R�A
};

#endif