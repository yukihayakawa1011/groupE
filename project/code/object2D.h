//==========================================================
//
// �I�u�W�F�N�g(2D)�̏��� [object2D.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _OBJECT2D_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT2D_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

#define DEF_2DPRI	(3)	// 2D��{�D�揇��

// �O���錾
class CMultiBg;

//==========================================================
// �I�u�W�F�N�g(2D)�̃N���X��`(�h���N���X)
//==========================================================
class CObject2D : public CObject
{
public:	// �N�ł��A�N�Z�X�\

	//CObject2D();	// �R���X�g���N�^
	CObject2D(const D3DXVECTOR3 pos);	// �R���X�g���N�^(�I�[�o�[���[�h)
	CObject2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority = 3);	// �R���X�g���N�^(�I�[�o�[���[�h)
	CObject2D(int nPriority = DEF_2DPRI);	// �f�t�H���g�����R���X�g���N�^
	virtual ~CObject2D();	// �f�X�g���N�^
	
	// �����o�֐�
	virtual HRESULT Init(void);
	HRESULT Init(const char *pFileName);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static CObject2D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority = 3);
	static CObject2D *Create(const int nPriority = 3);
	void BindTexture(int nIdx);

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);
	void SetLength(const float fLength);
	void SetAngle(const float fAngle);
	void SetLength(float fWidth, float fHeight);
	void SetSize(float fWidth, float fHeight);
	void SetWidth(float fWidth);
	void SetHeight(float fHeight);
	void SetIdxTex(int nIdx);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetLength(void) { return m_fLength; }
	float GetAngle(void) { return m_fAngle; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	CObject2D *GetObject2D(void) { return this; }
	int GetIdxTex(void) { return m_nIdxTexture; }

	// �����o�֐�
	void SetVtx(void);
	void SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight);
	void SetVtx(const float fTexU, const float fTexV, const float fWidth, const float fHeight);
	void SetTex(const float fTexU = 0.0f, const float fTexV = 0.0f, const float fWidth = 1.0f, const float fHeight = 1.0f);
	void SetPlayerVtx(void);
	void SetCol(const D3DXCOLOR col);

protected:	// �h���N���X������A�N�Z�X�\
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void) { return m_pVtxBuff; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	float m_fWidth;		// ��
	float m_fHeight;		// ����
	float m_fLength;		// �Ίp���̒���
	float m_fAngle;		// �Ίp���̊p�x
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXCOLOR m_col;		// �F
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
};

#endif