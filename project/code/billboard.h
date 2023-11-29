//==========================================================
//
// �r���{�[�h�̏����S�� [billboard.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include
#include "object.h"

//**********************************************************
// �r���{�[�h�N���X�̒�`
//**********************************************************
class CObjectBillboard : public CObject
{
public:

	// �������@�񋓌^
	enum FUSION
	{
		FUSION_ADD = 0,	// ���Z����
		FUSION_MINUS,		// ���Z����
		FUSION_NORMAL,	// �������Ȃ�
		FUSION_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CObjectBillboard(int nPriority = 3);	// �R���X�g���N�^
	~CObjectBillboard();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void RotFusionDraw(void);
	static CObjectBillboard *Create(D3DXVECTOR3 pos, const int nPriority = 3);
	void BindTexture(int nIdx);

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetVtx(void);
	void SetVtx(D3DXCOLOR col);
	void SetMtx(void);
	void SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight);
	void SetCol(const D3DXCOLOR col);
	void SetSize(float fWidth, float fHeight);
	float GetHeight(void) { return m_fHeight; }
	float GetWidth(void) { return m_fWidth; }
	virtual CEnemy *GetEnemy(void) { return NULL; }
	void SetFusion(FUSION fusion) { m_fusion = fusion; }
	void SetAlphaText(bool bTest) { m_bAlphatest = bTest; }
	void SetZTest(bool bTest) { m_bZtest = bTest; }
	void SetLighting(bool bTest) { m_bLighting = bTest; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	CObject2D *GetObject2D(void) { return NULL; }
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
	D3DXCOLOR GetCol(void) { return m_col; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;		// �F
	int m_nIdexTexture;	// �e�N�X�`���ԍ�
	float m_fWidth;		// ��
	float m_fHeight;	// ����
	FUSION m_fusion;	// �������@
	bool m_bZtest;	// Z�e�X�g���I���ɂ��邩
	bool m_bLighting;	// ���C�e�B���O���I�t�ɂ��邩
	bool m_bAlphatest;	// ���e�X�g���I���ɂ��邩
};


#endif
