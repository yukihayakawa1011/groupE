//==========================================================
//
// �I�����C���ΐ푗��M�v���g�R�� [protocol_online.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_

// �}�N����`

//**********************************************************
// ����M�p�v���g�R���񋓂��`
//**********************************************************
enum COMMAND_TYPE
{
	COMMAND_TYPE_NONE = 0,			// �������Ȃ�
	COMMAND_TYPE_SETPOSITION,		// ���W�ݒ�
	COMMAND_TYPE_SETROTATION,		// �����ݒ�
	COMMAND_TYPE_SETLIFE,			// �̗͐ݒ�
	COMMAND_TYPE_SETCHECKPOINT,	// �`�F�b�N�|�C���g�ʉ�
	COMMAND_TYPE_GOAL,			// �S�[��
	COMMAND_TYPE_START_OK,			// �J�n��������
	COMMAND_TYPE_CREATE,			// ����
	COMMAND_TYPE_DAMAGE,			// �_���[�W
	COMMAND_TYPE_DELETE,			// ����
	COMMAND_TYPE_GETID,			// ID�擾
	COMMAND_TYPE_MAX
};

#endif