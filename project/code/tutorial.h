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
class CPlayer;
class CObject3D;

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

	bool EndCheck(void);

	CPlayer **m_ppPlayer;			// �v���C���[�̃|�C���^
	CFileLoad *m_pFileLoad;			// �t�@�C���ǂݍ��݂̃|�C���^
	CObject3D *m_pObject3D;         // �I�u�W�F�N�g3D�̃|�C���^
	bool m_bEnd;
};

#endif