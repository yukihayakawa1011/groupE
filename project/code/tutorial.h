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
class CEntryIcon;
class CObject3D;
class CEnemy;

// �}�N����`
#define NUM_PORI   (5)  // �����̃e�N�X�`��
#define NUM_ENEMY  (2)  // �o���G�̐�
#define NUM_PLAYER (4)  // �v���C���[�̐�

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

	CPlayer **m_ppPlayer;			    // �v���C���[�̃|�C���^
	CFileLoad *m_pFileLoad;			    // �t�@�C���ǂݍ��݂̃|�C���^
	CEntryIcon *m_apObject[NUM_PLAYER]; // �I�u�W�F�N�g2D�̃|�C���^
	CObject3D *m_pObject3D[NUM_PORI];   // �I�u�W�F�N�g3D�̃|�C���^
	CEnemy*m_apEnemy[NUM_ENEMY];        // �G�̃|�C���^
	int m_nCntRespawn;                  // �G���Ăяo��܂ł̃J�E���g
	int m_nEnemyId;                     // �G�̔ԍ�
	bool m_bEnd;                        // 
};

#endif