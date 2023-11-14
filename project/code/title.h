//===============================================
//
// �^�C�g����ʂ̊Ǘ����� [title.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _TITLE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TITLE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

class CFileLoad;
class CObject2D;

//===============================================
// �^�C�g���N���X�̒�`(�h���N���X)
//===============================================
class CTitle : public CScene
{
public:

	// �����o�֐�
	CTitle();	// �R���X�g���N�^
	~CTitle();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	CFileLoad *m_pFileLoad;			// �t�@�C���ǂݍ��݂̃|�C���^
	int m_nTimer;	// �����J�ڃ^�C�}�[
	bool m_bClick;
	CObject2D *m_pEnter;
	D3DXCOLOR m_col;
	float m_fMoveCol;
	int m_nCounter;
	bool m_bPush;
};

#endif