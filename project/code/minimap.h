//===============================================
//
// �~�j�}�b�v�̏��� [minimap.h]
// Author : Soma Ishihara
//
//===============================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

//�O���錾
class CMultiCamera;

//�~�j�}�b�v�N���X�i���\����̂��߂�������p���Ȃ��j
class CMiniMap
{
public:
	//���_�ύX��ޗ񋓁i�����g�p��AND���Z���ē���āj
	enum CHANGE
	{
		CHANGE_POS = 0x0001,
		CHANGE_RHW = 0x0010,
		CHANGE_COL = 0x0100,
		CHANGE_TEX = 0x1000,
		CHANGE_ALL = 0x1111
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CMiniMap();
	~CMiniMap();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void DrawMap(void);
	void DrawTexture(void);
	static void Load(void);		//�f�o�C�X���X�g�΍�F���X�g����������Ăяo���ĂˁB�������ɂ��g����B
	static void UnLoad(void);	//�f�o�C�X���X�g�΍�F���X�g������Ăяo���Ă�

	//�}�b�v�|���S���̐ݒ�E�擾����
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);
	void SetSize(float fWidth, float fHeight);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	void SetpVtx(const int nChangeVtx);

private:
	//�����o�֐�
	void CulcDiagonal(void);

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	static LPDIRECT3DSURFACE9 m_pZSurface;	// �e�N�X�`���̐[�x�o�b�t�@
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	float m_fLength;	// �Ίp���̒���
	float m_fAngle;		// �Ίp���̊p�x
	float m_fWidth;		// ��
	float m_fHeight;	// ����
};

#endif // !_MINIMAP_H_
