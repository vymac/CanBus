// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13
// 2018-10-07 Kitos bibliotekos pritaikymas ODBII jungciai adapteris padarytas su CS=10
// 2018-10-09 Išbandyta su CanSheld+ArduinoNano kartu su tokiu pat siūstuvu - panašu, kad veikia
#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

unsigned long time;

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
    Serial.println("Get data from");
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN.getCanId();

        time = millis();
        
//        Serial.println("-----------------------------");
        Serial.print("Time ms: ");
        Serial.print(time,DEC);
        Serial.print("\t ID: 0x");
        Serial.print(canId, HEX);
        Serial.print("\t Len:\t");
        Serial.print(len,DEC);
        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print("\t0x");
            if (buf[i]<0x10) Serial.print("0");
            Serial.print(buf[i], HEX);
        }
            Serial.print("\t");

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print((char)buf[i]);
        }
        Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
