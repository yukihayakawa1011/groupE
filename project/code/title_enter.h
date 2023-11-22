//==========================================================
//
// �^�C�g���G���^�[ [title_enter.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TITLE_ENTER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TITLE_ENTER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

// �O���錾
class CItem;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CTitleEnter
{
public:	// �N�ł��A�N�Z�X�\
	CTitleEnter();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CTitleEnter();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)
	void SetItemParent(CItem *pItem);
	void SetPosition(D3DXVECTOR3 &pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 &rot) { m_rot = rot; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetMatrix(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
};

#endif

