#include <iostream>

#include "SerialClass.h"

#define COM_PORT "COM1"

#define BUF_SIZE 256

int main()
{
        Serial com1(COM_PORT);
        // обнуляем буфер
        char buf[BUF_SIZE];
        for(int i=0;i<BUF_SIZE;i++)
                        buf[i]='\0';
        // считываем и выводим данные из порта
        com1.ReadData(buf,BUF_SIZE-1);
        std::cout <<buf<< std::endl;
        return 0;
}
