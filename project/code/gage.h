//==========================================================
//
// �Q�[�W [gage.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GAGE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GAGE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

// �O���錾
class CObjectBillboard;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGage : public CTask
{
public:

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_FRAME = 0,	// �g
		TYPE_CONTENT,		// ���g
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGage();		// �R���X�g���N�^
	~CGage();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGage *Create(D3DXVECTOR3* pPos, const float fUpHeight, const float fPolyWidth, const float fPolyHeight);

	// �����o�֐�(�擾)
	void SetParent(D3DXVECTOR3 *pPos) { m_pPos = pPos; }
	void SetUpHeight(const float fHeight) { m_fUpHeight = fHeight; }
	void SetRate(const float fRate);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetPolySize(const float fWidth, const float fHeight);
	void SetMixPosition(void);

	// �����o�ϐ�
	D3DXVECTOR3 *m_pPos;	// �e�̍��W
	float m_fUpHeight;	// �グ�鍂��
	float m_fPolyWidth;	// �I�u�W�F�N�g�̕�
	float m_fPolyHeight;	// �I�u�W�F�N�g�̍���
	float m_fRate;		// ����
	CObjectBillboard *m_apObject[TYPE_MAX];	// �I�u�W�F�N�g�̔z��
};

#endif

