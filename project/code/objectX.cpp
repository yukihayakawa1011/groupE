//==========================================================
//
// X�t�@�C�����f���̏����S�� [objectX.cpp]
// Author : Ibuki Okusada (�����蔻�蒲�� : Soma Ishihara)
//
//==========================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "Xfile.h"

// �ÓI�����o�ϐ��錾
CObjectX *CObjectX::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CObjectX *CObjectX::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_nIdxModel = -1;

	m_pNext = NULL;
	m_pPrev = NULL;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CObjectX::~CObjectX()
{

}

//==========================================================
//���f���̏���������
//==========================================================
HRESULT CObjectX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�e��ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//==========================================================
//���f���̏I������
//==========================================================
void CObjectX::Uninit(void)
{
	// ���X�g����O��
	ListOut();

	// �p��
	Release();
}

//==========================================================
//���f���̍X�V����
//==========================================================
void CObjectX::Update(void)
{

}

//==========================================================
//���f���̕`�揈��
//==========================================================
void CObjectX::Draw(void)
{
	//Update();

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();	// X�t�@�C�����̃|�C���^
	CXFile::FileData *pFileData = pModelFile->SetAddress(m_nIdxModel);
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);

	if (pFileData != NULL)
	{// ���f�����g�p����Ă���ꍇ
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pFileData->pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)pFileData->dwNumMat; nCntMat++)
		{
			D3DMATERIAL9 mat = pMat[nCntMat].MatD3D;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&mat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->SetAddress(pFileData->pIdexTexture[nCntMat]));

			//���f��(�p�[�c)�̕`��
			pFileData->pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);
}

//==========================================================
// ����
//==========================================================
CObjectX *CObjectX::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, const char *pFileName, const int nPriority)
{
	CObjectX *pObjectX = NULL;
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != NULL)
	{// �����ł����ꍇ
		// ����������
		pObjectX->Init();

		// ���W
		pObjectX->SetPosition(pos);

		// ����
		pObjectX->SetRotation(rot);

		// ��ސݒ�
		pObjectX->SetType(TYPE_MODEL);

		// �ǂݍ��݊m�F
		pObjectX->BindFile(pModelFile->Regist(pFileName));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObjectX;
}

//==========================================================
// ���f���̃t�@�C���ݒ�
//==========================================================
void CObjectX::BindFile(int nIdx)
{
	m_nIdxModel = nIdx;	//�g�p���郂�f���̐ݒ�
}

//==========================================================
// ���W�̐ݒ�
//==========================================================
void CObjectX::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos; 
}

//==========================================================
// �����̐ݒ�
//==========================================================
void CObjectX::SetRotation(const D3DXVECTOR3 rot)
{ 
	m_rot = rot;

	if (m_rot.z < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += D3DX_PI * 2;
	}
	else if (m_rot.z > D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += -D3DX_PI * 2;
	}

	if (m_rot.x < -D3DX_PI)
	{// x���W�p�x���E
		m_rot.x += D3DX_PI * 2;
	}
	else if (m_rot.x > D3DX_PI)
	{// x���W�p�x���E
		m_rot.x += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{// x���W�p�x���E
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{// x���W�p�x���E
		m_rot.y += -D3DX_PI * 2;
	}
}

//==========================================================
// �����蔻��
//==========================================================
bool CObjectX::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, float fRefMulti)
{
	CObjectX *pObj = m_pTop;	// �擪�擾
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	bool bLand = false;	// ���n�������ۂ�

	//���u��
	D3DXVECTOR3 posTemp = posOld;

	//Y
	posTemp.y = pos.y;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CObjectX* pObjNext = pObj->m_pNext;
		D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (pObj->CollisionCheck(posTemp, posOld, move, vtxMin, vtxMax, fRefMulti))
		{
			bLand = true;
		}

		pObj = pObjNext;
	}

	//Z
	posTemp.z = pos.z;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CObjectX* pObjNext = pObj->m_pNext;
		D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pObj->CollisionCheck(posTemp, posOld, move, vtxMin, vtxMax, fRefMulti);

		pObj = pObjNext;
	}

	//X
	posTemp.x = pos.x;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CObjectX *pObjNext = pObj->m_pNext;
		D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pObj->CollisionCheck(posTemp, posOld, move, vtxMin, vtxMax, fRefMulti);

		pObj = pObjNext;
	}

	pos = posTemp;

	return bLand;
}

//==========================================================
// �����蔻��
//==========================================================
void CObjectX::SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot)
{
	//�����ɂ���ĕύX����
	if (fRot == 0.0f || fRot == -0.0f)
	{//������
		//�ő�l���f
		SetMax.x = vtxMax.x;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = vtxMax.z;	//z���W

		//�ŏ��l���f
		SetMin.x = vtxMin.x;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = vtxMin.z;	//z���W
	}
	if (fRot == D3DX_PI * 0.5f)
	{//������
		//�ő�l���f
		SetMax.x = vtxMax.z;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = -vtxMin.x;	//z���W

		//�ŏ��l���f
		SetMin.x = vtxMin.z;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = -vtxMax.x;	//z���W
	}
	else if (fRot == -D3DX_PI * 0.5f)
	{//�E����
		//�ő�l���f
		SetMax.x = -vtxMin.z;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = vtxMax.x;	//z���W

		//�ŏ��l���f
		SetMin.x = -vtxMax.z;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = vtxMin.x;	//z���W
	}
	else if (fRot == -D3DX_PI || fRot == D3DX_PI)
	{//���]���Ă���ꍇ
		//�����ȊO�̍ő�l���ŏ��l�ɂ���
		SetMax.x = -vtxMin.x;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = -vtxMin.z;	//z���W

		//�����ȊO�̍ŏ��l���ő�l�ɂ���
		SetMin.x = -vtxMax.x;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = -vtxMax.z;	//z���W
	}
	else
	{//����ȊO�̏ꍇ
		//�ő�l���f
		SetMax.x = vtxMax.x;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = vtxMax.z;	//z���W

		//�ŏ��l���f
		SetMin.x = vtxMin.x;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = vtxMin.z;	//z���W
	}
}

//==========================================================
// �ʔ���`�F�b�N
//==========================================================
bool CObjectX::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const float fRefMulti)
{
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	bool bLand = false;	// ���n�������ۂ�
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����𔽉f
	SetRotSize(vtxObjMax,
		vtxObjMin,
		pFile->GetMax(GetIdx()),
		pFile->GetMin(GetIdx()),
		m_rot.y);

	//if (pos.y + vtxMax.y > m_pos.y + vtxObjMin.y
	//	&& pos.y + vtxMin.y <= m_pos.y + vtxObjMax.y)
	//{//�v���C���[�ƃ��f�������������ɂ���
	//	if (posOld.x + vtxMin.x >= m_pos.x + vtxObjMax.x
	//		&& pos.x + vtxMin.x < m_pos.x + vtxObjMax.x
	//		&& pos.z + vtxMax.z > m_pos.z + vtxObjMin.z
	//		&& pos.z + vtxMin.z < m_pos.z + vtxObjMax.z)
	//	{//�E���獶�ɂ߂荞��
	//		move.x *= -1.0f;
	//		move.x *= fRefMulti;
	//		pos.x = m_pos.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;
	//	}
	//	else if (posOld.x + vtxMax.x <= m_pos.x + vtxObjMin.x
	//		&& pos.x + vtxMax.x > m_pos.x + vtxObjMin.x
	//		&& pos.z + vtxMax.z > m_pos.z + vtxObjMin.z
	//		&& pos.z + vtxMin.z < m_pos.z + vtxObjMax.z)
	//	{//������E�ɂ߂荞��
	//	 //�ʒu��߂�
	//		move.x *= -1.0f;
	//		move.x *= fRefMulti;
	//		pos.x = m_pos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;
	//		//move.x = 0.0f;
	//	}
	//	else if (posOld.z + vtxMin.z >= m_pos.z + vtxObjMax.z
	//		&& pos.z + vtxMin.z < m_pos.z + vtxObjMax.z
	//		&& pos.x + vtxMax.x > m_pos.x + vtxObjMin.x
	//		&& pos.x + vtxMin.x < m_pos.x + vtxObjMax.x)
	//	{//�������O�ɂ߂荞��
	//	 //�ʒu��߂�
	//		move.z *= -1.0f;
	//		move.z *= fRefMulti;
	//		pos.z = m_pos.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;
	//		//move.z = 0.0f;
	//	}
	//	else if (posOld.z + vtxMax.z <= m_pos.z + vtxObjMin.z
	//		&& pos.z + vtxMax.z > m_pos.z + vtxObjMin.z
	//		&& pos.x + vtxMax.x > m_pos.x + vtxObjMin.x
	//		&& pos.x + vtxMin.x < m_pos.x + vtxObjMax.x)
	//	{//��O���牜�ɂ߂荞��
	//	 //�ʒu��߂�
	//		move.z *= -1.0f;
	//		move.z *= fRefMulti;
	//		pos.z = m_pos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;
	//		//move.z = 0.0f;
	//	}
	//}

	//X
	if (pos.y + vtxMax.y > m_pos.y + vtxObjMin.y
		&& pos.y + vtxMin.y < m_pos.y + vtxObjMax.y
		&& pos.z + vtxMax.z > m_pos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < m_pos.z + vtxObjMax.z)
	{//�͈͓��ɂ���
		if (posOld.x + vtxMin.x >= m_pos.x + vtxObjMax.x
			&& pos.x + vtxMin.x < m_pos.x + vtxObjMax.x)
		{//�E���獶�ɂ߂荞��
			move.x *= -1.0f;
			move.x *= fRefMulti;
			pos.x = m_pos.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;
		}
		else if (posOld.x + vtxMax.x <= m_pos.x + vtxObjMin.x
			&& pos.x + vtxMax.x > m_pos.x + vtxObjMin.x)
		{//������E�ɂ߂荞��
		 //�ʒu��߂�
			move.x *= -1.0f;
			move.x *= fRefMulti;
			pos.x = m_pos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;
			//move.x = 0.0f;
		}
	}

	//Z
	if (pos.x + vtxMax.x > m_pos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < m_pos.x + vtxObjMax.x
		&& pos.y + vtxMax.y > m_pos.y + vtxObjMin.y
		&& pos.y + vtxMin.y < m_pos.y + vtxObjMax.y)
	{//�͈͓��ɂ���
		if (posOld.z + vtxMin.z >= m_pos.z + vtxObjMax.z
			&& pos.z + vtxMin.z < m_pos.z + vtxObjMax.z)
		{//�������O�ɂ߂荞��
		 //�ʒu��߂�
			move.z *= -1.0f;
			move.z *= fRefMulti;
			pos.z = m_pos.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;
			//move.z = 0.0f;
		}
		else if (posOld.z + vtxMax.z <= m_pos.z + vtxObjMin.z
			&& pos.z + vtxMax.z > m_pos.z + vtxObjMin.z)
		{//��O���牜�ɂ߂荞��
		 //�ʒu��߂�
			move.z *= -1.0f;
			move.z *= fRefMulti;
			pos.z = m_pos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;
			//move.z = 0.0f;
		}
	}

	//Y
	if (pos.x + vtxMax.x > m_pos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < m_pos.x + vtxObjMax.x
		&& pos.z + vtxMax.z > m_pos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < m_pos.z + vtxObjMax.z)
	{//�͈͓��ɂ���
		//�ォ��̔���
		if (posOld.y + vtxMin.y >= m_pos.y + vtxObjMax.y
			&& pos.y + vtxMin.y < m_pos.y + vtxObjMax.y)
		{//�ォ��߂荞��
			//��ɂ̂���
			pos.y = m_pos.y + vtxObjMax.y - vtxMin.y;
			move.y = 0.0f;
			bLand = true;
		}
	}

	return bLand;
}

//==========================================================
// ���X�g����O��
//==========================================================
void CObjectX::ListOut(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != NULL)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != NULL)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}
}

void CObjectX::CollisionLand(D3DXVECTOR3 &pos)
{
	CObjectX *pObj = m_pTop;	// �擪�擾
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	while (pObj != NULL)
	{
		CObjectX *pObjNext = pObj->m_pNext;
		D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �����𔽉f
		pObj->SetRotSize(vtxObjMax,
			vtxObjMin,
			pFile->GetMax(pObj->GetIdx()),
			pFile->GetMin(pObj->GetIdx()),
			pObj->m_rot.y);

		if (pos.x >= pObj->m_pos.x + vtxObjMin.x
			&& pos.x <= pObj->m_pos.x + vtxObjMax.x
			&& pos.z >= pObj->m_pos.z + vtxObjMin.z
			&& pos.z <= pObj->m_pos.z + vtxObjMax.z)
		{//�͈͓��ɂ���
			//�ォ��̔���
			if (pos.y < pObj->m_pos.y + vtxObjMax.y)
			{//�ォ��߂荞��
				//��ɂ̂���
				pos.y = pObj->m_pos.y + vtxObjMax.y + 4.0f;
			}
		}

		pObj = pObjNext;
	}
}