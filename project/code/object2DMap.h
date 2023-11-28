//==========================================================
//
// �}�b�v�I�u�W�F�N�g [object2DMap.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _OBJECT_MAP_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT_MAP_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "object2D.h"

//==========================================================
// �}�b�v�̃N���X��`
//==========================================================
class CObject2DMap : public CObject2D
{

public:	// �N�ł��A�N�Z�X�\

	CObject2DMap(int nPriOrity = 3);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CObject2DMap();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Draw(void);
	static CObject2DMap *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	// �����o�֐�(�擾)
	

	// �����o�֐�(�ݒ�)
	void SetTexture(LPDIRECT3DTEXTURE9 pTexMap, LPDIRECT3DTEXTURE9 pTexUnex);

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTextureMap;	//�}�b�v�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_pTextureUnex;	//���T���e�N�X�`��
};

#endif

