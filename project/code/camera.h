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
#define MAX_CAMERA_ROTZ (D3DX_PI * 0.999f)	// �J�����ő�p�x
#define MIN_CAMERA_ROTZ (D3DX_PI * 0.01f)	// �J�����ő�p�x

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
		MODE_STARTDOOR,     // �X�^�[�g�h�A�����
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

	//�����蔻��
	void CollisionObj(void);

	// �^�C�g���p
	void TitleRotateCamera(void);

	// �X�^�[�g�̔��S���J�����Ƃ�
	void AllOpenCamera(int nCount);

	// �����o�֐�(�擾)
	D3DXMATRIX GetMtxView(void) { return m_mtxView; }
	D3DXMATRIX GetMtxProjection(void) { return m_mtxProjection; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetPositionV(void) { return m_posV; }
	D3DXVECTOR3 GetPositionR(void) { return m_posR; }
	D3DXVECTOR3 GetOldPositionV(void) { return m_OldposV; }
	D3DXVECTOR3 GetOldPositionR(void) { return m_OldposR; }
	D3DXVECTOR3 GetVectorU(void) { return m_vecU; }
	void SetRotation(D3DXVECTOR3 rot);
	void SetLength(float fLength) { m_fLength = fLength; }
	CCamera *GetNext(void) { return m_pNext; }
	CCamera *GetPrev(void) { return m_pPrev; }
	MODE GetMode(void) { return m_mode; }
	bool GetDraw(void) const { return m_bDraw; }
	float GetLength(void) { return m_fLength; }

	// �����o�֐�(�ݒ�)
	D3DXMATRIX SetMtxView(D3DXMATRIX mtxView) { m_mtxView = mtxView; }
	D3DXMATRIX SetMtxProjection(D3DXMATRIX mtxProjection) { m_mtxProjection = mtxProjection; }
	void SetNext(CCamera *pNext) { m_pNext = pNext; }
	void SetPrev(CCamera *pPrev) { m_pPrev = pPrev; }
	void SetDraw(const bool bDraw) { m_bDraw = bDraw; }
	void SetActive(const bool bActive) { m_bActive = bActive; }
	void BindId(int nId) { m_nId = nId; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void MoveR(void);
	void SetV(void);
	void SetR(void);
	void Edit(void);
	void Slow(void);
	void Zoom(void);

	// �����o�ϐ�
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_posV;		// ���_
	D3DXVECTOR3 m_posR;		// �����_
	D3DXVECTOR3 m_OldposV;	// �O�̎��_
	D3DXVECTOR3 m_OldposR;	// �O�̒����_
	D3DXVECTOR3 m_vecU;		// ������x�N�g��
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_Oldrot;   // �O�̌���
	D3DXVECTOR3 m_SlowOldRot;	// �X���[�O�̌���
	D3DXVECTOR3 m_GoalPos;  // �S�[���̈ʒu
	MODE m_mode;				// ���[�h
	float m_fMulScore;		// �X�R�A�{��
	float m_fLength;			// ���_�ƒ����_�̋���
	float m_fZoom;				// �Y�[����
	float m_fDestZoom;			// �ڕW�Y�[����
	CCamera *m_pNext;			// ��
	CCamera *m_pPrev;			// �O
	int m_nId;				// �g�p�R���g���[���[�ԍ�
	int m_nZoomCount;           // �X�^�[�g�h�A�����Ă��鎞��
	bool m_bDraw;				// �`��
	bool m_bActive;			// ����\���ǂ���
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