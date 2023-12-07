//==========================================================
//
// �̂Ă�A�C�e�� [throwitem.h]
// Author : Ryosuke Ohhra
//
//==========================================================
#ifndef _THROWITEM_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _THROWITEM_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

// �O���錾
class CObjectBillboard;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CThrowItem : public CTask
{
public:

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_ARROW = 0,         // ���
		TYPE_ITEM,  // �A�C�e���̃A�C�R��
		TYPE_FRAME,         // �g
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CThrowItem();		// �R���X�g���N�^
	~CThrowItem();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	CObjectBillboard *GetObjectBillBoard(void) { return m_apObject[0]; }
	static CThrowItem *Create(D3DXVECTOR3* pPos, const float fUpHeight, const float fPolyWidth, const float fPolyHeight);

	// �����o�֐�(�擾)
	void SetParent(D3DXVECTOR3 *pPos) { m_pPos = pPos; }
	void SetUpHeight(const float fHeight) { m_fUpHeight = fHeight; }
	void SetItem(int nThrowItemID);


private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetPolySize(const float fWidth, const float fHeight);
	void SetMixPosition(void);

	// �����o�ϐ�
	D3DXVECTOR3 *m_pPos;	// �e�̍��W
	int m_nBeforeID;        // ���ݑI�����Ă���ԍ��̑O�̔ԍ�
	int m_nNowID;           // ���ݑI�����Ă���ԍ�
	int m_nNextID;          // ���ݑI�����Ă���ԍ��̎��̔ԍ�
	float m_fUpHeight;	    // �グ�鍂��
	float m_fPolyWidth;	    // �I�u�W�F�N�g�̕�
	float m_fPolyHeight;	// �I�u�W�F�N�g�̍���
	float m_fRate;		    // ����
	CObjectBillboard *m_apObject[TYPE_MAX];	// �I�u�W�F�N�g�̔z��
};

#endif