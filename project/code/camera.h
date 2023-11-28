//==========================================================
//
// �J�����̏����S�� [camera.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CAMERA_H_		 // ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CAMERA_H_		 // ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

// �}�N����`
#define MAX_CAMERA_ROTZ (D3DX_PI * 0.9999f)	// �J�����ő�p�x
#define MIN_CAMERA_ROTZ (D3DX_PI * 0.0001f)	// �J�����ő�p�x

//**********************************************************
// �J�����N���X�̒�`
//**********************************************************
class CCamera
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	enum MODE
	{
		MODE_NORMAL = 0,	// �ʏ�
		MODE_SLOWGUN,		// �X���[�p�x�������
		MODE_SLOWSHW,		// �V�����[
		MODE_MAX
	};

public:	// �N�ł��A�N�Z�X�\
	CCamera();	// �R���X�g���N�^
	virtual ~CCamera();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void SetCamera(void);
	void Pursue(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void Setting(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void SetRot(const D3DXVECTOR3 rot);
	void SetMode(MODE mode) { m_mode = mode; }
	void SetOldRot(D3DXVECTOR3 rot) { m_SlowOldRot = rot; }
	void MoveV(void);
	void MouseCamera(void);
	void MoveVR(void);
	void SetPositionR(D3DXVECTOR3 pos);
	void SetPositionV(D3DXVECTOR3 pos);

	// �^�C�g���p
	void TitleRotateCamera(void);

	// �����o�֐�(�擾)
	D3DXMATRIX GetMtxView(void) { return m_mtxView; }
	D3DXMATRIX GetMtxProjection(void) { return m_mtxProjection; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetPositionV(void) { return m_posV; }
	D3DXVECTOR3 GetPositionR(void) { return m_posR; }
	D3DXVECTOR3 GetVectorU(void) { return m_vecU; }
	void SetRotation(D3DXVECTOR3 rot);
	void SetLength(float fLength) { m_fLength = fLength; }
	CCamera *GetNext(void) { return m_pNext; }
	CCamera *GetPrev(void) { return m_pPrev; }
	bool GetDraw(void) const { return m_bDraw; }

	// �����o�֐�(�ݒ�)
	D3DXMATRIX SetMtxView(D3DXMATRIX mtxView) { m_mtxView = mtxView; }
	D3DXMATRIX SetMtxProjection(D3DXMATRIX mtxProjection) { m_mtxProjection = mtxProjection; }
	void SetNext(CCamera *pNext) { m_pNext = pNext; }
	void SetPrev(CCamera *pPrev) { m_pPrev = pPrev; }
	void SetDraw(const bool bDraw) { m_bDraw = bDraw; }
	void BindId(int nId) { m_nId = nId; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void MoveR(void);
	void SetV(void);
	void SetR(void);
	void Edit(void);
	void Slow(void);

	// �����o�ϐ�
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_posV;		// ���_
	D3DXVECTOR3 m_posR;		// �����_
	D3DXVECTOR3 m_vecU;		// ������x�N�g��
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_SlowOldRot;	// �X���[�O�̌���
	MODE m_mode;				// ���[�h
	float m_fMulScore;		// �X�R�A�{��
	float m_fLength;			// ���_�ƒ����_�̋���
	CCamera *m_pNext;			// ��
	CCamera *m_pPrev;			// �O
	int m_nId;				// �g�p�R���g���[���[�ԍ�
	bool m_bDraw;				// �`��
};

//**********************************************************
// �����J�����N���X�̒�`
//**********************************************************
class CMultiCamera : public CCamera
{
public:	// �N�ł��A�N�Z�X�\
	CMultiCamera();	// �R���X�g���N�^
	~CMultiCamera();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void SetCamera(void) override;
	void SetViewPort(D3DVIEWPORT9 viewport) { m_viewport = viewport; }
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	D3DVIEWPORT9 m_viewport;		//�r���[�|�[�g
};

//**********************************************************
// �~�j�}�b�v�J�����N���X�̒�`
//**********************************************************
class CMapCamera : public CMultiCamera
{
public:	// �N�ł��A�N�Z�X�\
	CMapCamera();	// �R���X�g���N�^
	~CMapCamera();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

private:	// �����������A�N�Z�X�\

};

#endif