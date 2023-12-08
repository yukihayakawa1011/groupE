//===============================================
//
// �����S�ʂ̏��� [number.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _NUNBER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _NUNBER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CObject2D;

//===============================================
// �i���o�[�N���X�̒�`
//===============================================
class CNumber
{
public:	// �N�ł��A�N�Z�X�\

	CNumber();	// �R���X�g���N�^
	~CNumber();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber *Create(void);
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	CObject2D *GetObject2D(void) { return m_pObject2D; }
	void PolygonDelete(void);
	void SetPosition(const D3DXVECTOR3& pos);
	
	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //�e�N�X�`�����o�C���h

	// �����o�֐�(�ݒ�)
	void SetIdx(const int nIdx);

	// �����o�֐�(�擾)
	int GetIdx(void) { return m_nIdx; }

private:	// �����������A�N�Z�X�\
	
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;        //�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D;	// 2D�I�u�W�F�N�g�̃|�C���^
	int m_nIdx;	// �����̔ԍ�
	int m_nIdxTexture;
};

#endif

