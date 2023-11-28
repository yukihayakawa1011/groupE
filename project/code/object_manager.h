//==========================================================
//
// �I�u�W�F�N�g�Ǘ��̏��� [object_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _OBJECT_MANAGER_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT_MANAGER_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

// �}�N����`
#define NUM_PRIORITY	(8)		// �D�揇�ʊǗ���

// �O���錾
class CObject;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CObjectManager
{
private:
	CObjectManager();	// �R���X�g���N�^
	~CObjectManager();	// �f�X�g���N�^

public:
	enum TYPE
	{
		TYPE_ALL = 0,
		TYPE_3DONLY,
	};

	// ���X�g�Ǘ������o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Draw(void);
	void DrawAll(TYPE type = TYPE_ALL);
	void ListIn(CObject *pObject);
	CObject *GetTop(const int nPriority) { return m_apTop[nPriority]; }
	int GetNumAll(void) { return m_nNumAll; }
	int GetPriNumAll(int nPriority) { return m_aPriNumAll[nPriority]; }

	// �V���O���g��
	static CObjectManager* GetInstance(void);
	static void Release(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void ReleaseAll(void);
	void DeathCheck(void);

	// �����o�ϐ�
	CObject *m_apTop[NUM_PRIORITY];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_apCur[NUM_PRIORITY];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static CObjectManager *m_pInstance;
	int m_aPriNumAll[NUM_PRIORITY];	// �e�D�揇�ʂ��Ƃ̑���
	int m_nNumAll;	// �I�u�W�F�N�g����
};

#endif
