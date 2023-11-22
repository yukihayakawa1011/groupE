//==========================================================
//
// �T���v���^�X�N [sample_task.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _UI_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _UI_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

//#include "../task.h"
#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//�O���錾
class CObject2D;

//==========================================================
// UI�̃N���X��`
//==========================================================
class CUI : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	enum TYPE
	{
		TYPE_NORMAL = 0,	// �Ȃ���Ȃ�
		TYPE_LEFTUP,		// ����
		TYPE_RIGHTUP,		// �E��
		TYPE_LEFTDOWN,		// ����
		TYPE_RIGHTDOWN,		// �E��
		TYPE_MAX
	};

	CUI();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CUI();	// �f�X�g���N�^

					// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pFileFrameName, const char *pFilePIconName);
	void Uninit(void);
	void Update(void);
	static CUI *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, const char *pFileFrameName, const char *pFilePIconName,TYPE type);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	TYPE GetType(void) { return m_type; }

	// �����o�֐�(�ݒ�)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetType(TYPE type) { m_type = type; }

private:	// �����������A�N�Z�X�\

	#define NUM_OBJ			(3)			//�I�u�W�F�N�g�̐�

			// �����o�֐�

			// �����o�ϐ�
	CObject2D *m_pObject[NUM_OBJ];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	TYPE m_type;

};

#endif


