//===============================================
//
// �~�j�}�b�v�̏��� [minimap.h]
// Author : Soma Ishihara
//
//===============================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "task.h"
#include "object2DMap.h"
#include "input.h"

//�O���錾
class CMultiCamera;
class CObject2D;
class CObject2DMap;

//�~�j�}�b�v�N���X
class CMiniMap : public CTask
{
public:
	//���_�ύX��ޗ񋓁i�����g�p��AND���Z���ē���āj
	enum CHANGE
	{
		CHANGE_POS = 0b0001,
		CHANGE_RHW = 0b0010,
		CHANGE_COL = 0b0100,
		CHANGE_TEX = 0b1000,
		CHANGE_ALL = 0b1111
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CMiniMap();
	~CMiniMap();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void){}
	void DrawTexture(void);
	void Load(void);		//�f�o�C�X���X�g�΍�F���X�g����������Ăяo���ĂˁB�������ɂ��g����B
	void UnLoad(void);	//�f�o�C�X���X�g�΍�F���X�g������Ăяo���ĂˁB�I���ɂ��g����B
	void Reset(void);	//�܂����낭�낷���ɂ��ĒT�����ĂȂ����Ƃɂ���B�������ɂǂ���

	static CMiniMap* Create(const D3DXVECTOR3 posMap, const D3DXVECTOR3 rotMap, const float width, const float height, const int playerNum, 
		const int elaseWidth,const int elaseHeight);

	//�}�b�v�|���S���̐ݒ�E�擾����
	void SetPosition(const D3DXVECTOR3 pos){ m_pos = pos; }

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_pObjMap->GetRotation(); }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTextureMap;	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 m_pTextureUnex;	// ���T���ꏊ�����������e�N�X�`��
	LPDIRECT3DSURFACE9 m_pZSurface;		// �e�N�X�`���̐[�x�o�b�t�@
	CObject2DMap* m_pObjMap;			//�}�b�v�I�u�W�F
	CObject2D** m_ppPlayerIcon;
	bool** m_ppExplored;//�T���ς݃h�b�g
	D3DXVECTOR3 m_pos;	// �ʒu
	float m_fWidth;		// ��
	float m_fHeight;	// ����
	int m_nElaseWidth;	//�T���ς݂ɂ��镝
	int m_nElaseHeight;	//�T���ς݂ɂ��鍂��
	int m_nPlayerNum;	//�v���C���[�l����
};

#endif // !_MINIMAP_H_
