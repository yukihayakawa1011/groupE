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
class CTitleEnter;
class CEnemy;

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

	CFileLoad *m_pFileLoad;		// �t�@�C���ǂݍ��݂̃|�C���^
	CTitleEnter *m_pEnter;
	CEnemy** m_appEnemy;		// ���o�p�G
	int m_nCounterTutorial;		// �`���[�g���A���y�ѐl���I����ʑJ�ڃ^�C�}�[
	int m_nCounterRanking;		// �����L���O�����J�ڃ^�C�}�[
	bool m_bPush;				// �`���[�g���A���J�ڂɕK�v�ȃ{�^����������Ă��邩
};

#endif