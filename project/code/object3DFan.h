//==========================================================
//
// 3D��̏��� [object3DFan.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _OBJECT3D_FAN_H_	 // ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT3D_FAN_H_	 // ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

//**********************************************************
// �I�u�W�F�N�g3D�N���X�̒�`
//**********************************************************
class CObject3DFan : public CObject
{
public:	// �N�ł��A�N�Z�X�\

	//���_�ύX��ޗ񋓁i�����g�p��AND���Z���ē���āj
	enum CHANGE
	{
		CHANGE_POS = 0x0001,
		CHANGE_NOR = 0x0010,
		CHANGE_COL = 0x0100,
		CHANGE_TEX = 0x1000,
		CHANGE_ALL = 0x1111
	};

	CObject3DFan(int nPriority = 6);	// �R���X�g���N�^
	~CObject3DFan();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Draw(void);
	static CObject3DFan *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength, float fRadius, int nDivision);
	void SetpVtx(const int nChangeVtx);

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetLength(const float fLength);
	void SetRadius(const float fRadius);
	void SetDivision(const int nDiv);
	void SetColor(const D3DXCOLOR col);
	void SetMtx(void);
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetLength(void) { return m_fLength; }

private:	// �����������A�N�Z�X�\
	//�����o�֐�
	HRESULT ResetpVtx(void);

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;		//�F
	float m_fLength;		//����
	float m_fRadius;		//�p�x
	int m_nDivision;		//������
};

#endif
