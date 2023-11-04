//==========================================================
//
// winsock�ʐM(�N���C�A���g)
// Author : Ibuki Okusada
//
//==========================================================
#include <stdio.h>
#include "tcp_client.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CClient::CClient()
{
	// �l���N���A����
	m_sock = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CClient::~CClient()
{

}

//==========================================================
// ����������
//==========================================================
bool CClient::Init(const char *pIPAddress, int nPortNum)
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);	//�ڑ���t�p�̃\�P�b�g�̍쐬����֐�

	if (m_sock == INVALID_SOCKET)
	{// �쐬�Ɏ��s�����ꍇ
		return FALSE;	// �I��
	}

	// �ڑ���̐ݒ�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);	// �ڑ����󂯕t����|�[�g�A�ԍ����Œ�(�ڑ���|�[�g�ԍ�)
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);	// �ڑ���IP�A�h���X������

	// �ڑ�����
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{// �ڑ��ł��Ȃ������ꍇ

		// �L�[���͑҂�
		rewind(stdin);
		getchar();

		return FALSE;	// �I��
	}
	else
	{// �ڑ��ł����Ƃ�

	}

	return TRUE;
}

//==========================================================
// �I������
//==========================================================
void CClient::Uninit(void)
{
	// �ڑ���ؒf����
	closesocket(m_sock);	// �N���C�A���g�Ƃ̐ڑ������
}

//==========================================================
// ���M����
//==========================================================
int CClient::Send(const char *pSendData, int nSendDataSize)
{
	// �f�[�^���M
	int nSendByte = send(m_sock, pSendData, nSendDataSize, 0);	// send�֐�: �f�[�^�𑗐M����

	return nSendByte;
}

//==========================================================
// ��M����
//==========================================================
int CClient::Recv(char *pRecvData, int nRecvDataSize)
{
	int nRecvByte = recv(m_sock, pRecvData, nRecvDataSize, 0);	// recv�֐�: �f�[�^����M����

	return nRecvByte;
}

//==========================================================
// �\�P�b�g�ݒ�
//==========================================================
void CClient::BindSock(SOCKET sock)
{
	m_sock = sock;
}
