//-----------------------------------------------------------------------------
//                         COM-monitor for Arduino                           //
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <tchar.h>
#include <string>
#include "SerialClass.h" // Библиотека для работы с COM портом с arduino.cc
//-----------------------------------------------------------------------------
#define DEBUG 0          // Вкл/Выкл вывод отладочной информации
//-----------------------------------------------------------------------------
#define COM_PORT "\\\\.\\COM10"  // Адрес COM-порта устройства
#define BUF_SIZE 256             // Размер буфера получаемых данных
#define UPD_TIME 200             // Время обновления канала
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	Serial* SP = new Serial(COM_PORT); // Инициализация соединения

	if (SP->IsConnected())
		printf("We're connected\n\n");
	else
		printf("Connection refused\n\n");

	char incomingData[BUF_SIZE] = ""; // Строка для посылки (данных)
	int readResult = 0;               // Каков размер нашей посылки

	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, BUF_SIZE-1);
		// Если ничего нет readResult будет равно -1
		if (DEBUG) printf("Bytes read: %i\n",readResult);
		// Выводим для отладки кол-во байт переданных данных (или -1)
		incomingData[readResult] = 0;
		// Записываем конец строки после всех нужных данных
		if (readResult > 0) printf("%s",incomingData);
		// Eсли в посылке что-то было (и она была), то выводим ее
		Sleep(UPD_TIME);
		// Подождем пока, чтобы не вывести одно и тоже несколько раз
	}

    delete SP;
    Sleep(2000);
	return 0;
}                                                    // By SnipGhost 06.08.2016
//-----------------------------------------------------------------------------
