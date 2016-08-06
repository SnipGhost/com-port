//-----------------------------------------------------------------------------
//                         COM-monitor for Arduino                           //
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <tchar.h>
#include <string>
#include "SerialClass.h" // ���������� ��� ������ � COM ������ � arduino.cc
//-----------------------------------------------------------------------------
#define DEBUG 0          // ���/���� ����� ���������� ����������
//-----------------------------------------------------------------------------
#define COM_PORT "\\\\.\\COM10"  // ����� COM-����� ����������
#define BUF_SIZE 256             // ������ ������ ���������� ������
#define UPD_TIME 200             // ����� ���������� ������
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	Serial* SP = new Serial(COM_PORT); // ������������� ����������

	if (SP->IsConnected())
		printf("We're connected\n\n");
	else
		printf("Connection refused\n\n");

	char incomingData[BUF_SIZE] = ""; // ������ ��� ������� (������)
	int readResult = 0;               // ����� ������ ����� �������

	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, BUF_SIZE-1);
		// ���� ������ ��� readResult ����� ����� -1
		if (DEBUG) printf("Bytes read: %i\n",readResult);
		// ������� ��� ������� ���-�� ���� ���������� ������ (��� -1)
		incomingData[readResult] = 0;
		// ���������� ����� ������ ����� ���� ������ ������
		if (readResult > 0) printf("%s",incomingData);
		// E��� � ������� ���-�� ���� (� ��� ����), �� ������� ��
		Sleep(UPD_TIME);
		// �������� ����, ����� �� ������� ���� � ���� ��������� ���
	}

    delete SP;
    Sleep(2000);
	return 0;
}                                                    // By SnipGhost 06.08.2016
//-----------------------------------------------------------------------------
