//==========================================================
//
// DirectX�̃����_���[���� [renderer.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _RENDERER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _RENDERER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �����_���[�N���X�̒�`
class CRenderer
{
public:	// �N�ł��A�N�Z�X�\

	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetWire(bool bWire);

	// �����o�ϐ�
	LPDIRECT3D9 m_pD3D;				//Direct3D�I�u�W�F�N�g�̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;	//Direct3D�f�o�C�X�ւ̃|�C���^
	bool m_bWire;					// ���C���[�t���[���ɂ��邩�ۂ�
	LPDIRECT3DTEXTURE9 pTexture;
	LPDIRECT3DSURFACE9 m_pRenderTextureSurface;
	LPDIRECT3DSURFACE9 m_pZSurface;
	LPDIRECT3DSURFACE9 m_pOrgSurface;
	LPDIRECT3DSURFACE9 m_pOrgZBuffer;
};

#endif