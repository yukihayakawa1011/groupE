//==========================================================
//
// �^�X�N�̏��� [task.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TASK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TASK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CTask
{
protected:	// �N�ł��A�N�Z�X�\

	// ��ޗ񋓌^�̒�`
	enum TYPE
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_BG,		// �w�i
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G
		TYPE_BULLET,	// �e
		TYPE_ITEM,		// �A�C�e��
		TYPE_EXPLOSION,	// ����
		TYPE_EFFECT,	// �G�t�F�N�g
		TYPE_BLOCK,		// �u���b�N
		TYPE_MODEL,		// ���f��
		TYPE_CAR,		// �ԁ@
		TYPE_PAUSE,		// �|�[�Y���
		TYPE_MAP,		// �}�b�v�\��
		TYPE_MAX
	};

public:

	CTask();	// �R���X�g���N�^
	virtual ~CTask();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) = 0; 
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	CTask *GetNext(void) { return m_pNext; }
	CTask *GetPrev(void) { return m_pPrev; }
	void SetNext(CTask *pNext) { m_pNext = pNext; }
	void SetPrev(CTask *pPrev) { m_pPrev = pPrev; }
	bool GetDeath(void) { return m_bDeath; }

protected:	// �h���N���X������A�N�Z�X�\

	// �����o�֐�
	void Release(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	static CTask *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CTask *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CTask *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CTask *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;	// ���S�t���O
	TYPE m_type;	// ���
};

#endif


