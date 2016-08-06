#include "SerialClass.h"

Serial::Serial(char *portName)
{
    // ���� ��� �� ������������
    this->connected = false;

    // �������� ������������ � ����� ����������� CreateFile
    this->hSerial = CreateFile(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    // ��������� � ���� �� ���������� ��������
    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        //���� �� ���� � ������� ������
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            // �������� ������
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        // ������������ � ������ ������������� ���������
        DCB dcbSerialParams = {0};

        // ��������� ������� ���������
        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            // ���� ���������� � ������� � �������
            printf("failed to get current serial parameters!");
        }
        else
        {
            // ������������� ��������� ��� ���������� � Arduino
            dcbSerialParams.BaudRate=CBR_9600;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;

             // ��������� ���������
             if(!SetCommState(hSerial, &dcbSerialParams))
             {
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 // �������! �� ������� ����������� :)
                 this->connected = true;
                 //��� ���� Arduino ��������������
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
    }

}

Serial::~Serial()
{
    // ��������� ������ �����������
    if(this->connected)
    {
        // �����������
        this->connected = false;
        // ��������� ���������� �����
        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
    // ����� ����������� ����
    DWORD bytesRead;
    // ����� ����, ������� �� ������������� ����� �������
    unsigned int toRead;

    // ���������� ClearCommError ��� ��������� ���������� � ������� ����������������� �����
    ClearCommError(this->hSerial, &this->errors, &this->status);

    // ��������� � ���� �� ���������� ��� ����������
    if(this->status.cbInQue>0)
    {
        // ���� ���������� ������ ������ ���������� � ���������
        // �������, ������� ����
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        // �������� ������� ������ ���������� ������ �
        //���������� ����� ��������� ���� ��� ������� ����������.
        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }

    }

    // ������ �� ������� ��� ���-�� ���� ������ � ���������� -1
    return -1;

}


bool Serial::WriteData(char *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    // �������� �������� �������� ������ buffer � COM-����
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        // ���� �� ���������� � �������� ��� ������ � ���������� false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool Serial::IsConnected()
{
    // ������ ���������� ������ ���������� :)
    return this->connected;
}
