//===============================================
//
// �I�u�W�F�N�g�̏��� [object.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _OBJECT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CObject2D;
class CMultiBg;
class CEnemy;

//===============================================
// �I�u�W�F�N�g�N���X�̒�`(���ۃN���X)
//===============================================
class CObject
{
public:	// �N�ł��A�N�Z�X�\

	// ��ޗ񋓌^�̒�`
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_BG,		// �w�i
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,	// �G
		TYPE_BULLET,	// �e
		TYPE_ITEM,	// �A�C�e��
		TYPE_EXPLOSION,	// ����
		TYPE_EFFECT,	// �G�t�F�N�g
		TYPE_BLOCK,	// �u���b�N
		TYPE_MODEL,	// 3D���f��
		TYPE_MAX
	}TYPE;

	//CObject();			// �R���X�g���N�^
	CObject(int nPriority = 3);	// �R���X�g���N�^(�I�[�o�[���[�h)�f�t�H���g����
	virtual ~CObject();	// �f�X�g���N�^

	// �������z�֐��֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Draw(void) = 0;

	// �����o�֐�(�ݒ�)
	virtual void SetPosition(const D3DXVECTOR3 pos) {}
	virtual void SetRotation(const D3DXVECTOR3 rot) {}

	// �����o�֐�(�擾)
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	virtual D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	virtual CObject2D *GetObject2D(void) { return NULL; }
	virtual int GetModelType(void) { return -1; }
	virtual D3DXMATRIX *GetMtx(void) { return NULL; }
	virtual CEnemy *GetEnemy(void) { return NULL; }
	virtual bool GetDeath(void) { return m_bDeath; }

	// �����o�֐�
	virtual void Hit(float fDamage){ }
	void SetDraw(bool bUse = true) { m_bDraw = bUse; }

	// �����o�֐�(�擾
	TYPE GetType(void) { return m_type; }
	int GetPri(void) { return m_nPriority; }
	CObject *GetNext(void) { return m_pNext; }
	CObject *GetPrev(void) { return m_pPrev; }

	// �����o�֐�(�ݒ�)
	void SetType(const TYPE type);
	void SetPriOrity(int nPriority) { m_nPriority = nPriority; }
	void SetNext(CObject *pNext) { m_pNext = pNext; }
	void SetPrev(CObject *pPrev) { m_pPrev = pPrev; }

protected:	// �h���N���X������A�N�Z�X�\

	// �����o�֐�
	void Release(void);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	CObject *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;	// ���S�t���O
	bool m_bDraw;		// �`��t���O
	int m_nPriority;	// �D�揇�ʂ̈ʒu
	TYPE m_type;		// ���
};

#endif
