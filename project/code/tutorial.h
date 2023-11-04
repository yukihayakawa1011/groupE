//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _TUTORIAL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TUTORIAL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

// �O���錾
class CFileLoad;

//===============================================
// �Q�[���N���X�̒�`(�h���N���X)
//===============================================
class CTutorial : public CScene
{
public:

	// �����o�֐�
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����o�֐�(�|�C���^)
	CFileLoad *GetFileLoad(void);

private:

	CFileLoad *m_pFileLoad;			// �t�@�C���ǂݍ��݂̃|�C���^
};

#endif