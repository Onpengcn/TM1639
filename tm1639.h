#ifndef __H
#define __H

#include "Arduino.h"
#include <String.h>
typedef unsigned char		u8;
typedef unsigned short		u16;

#define delay_us(a)   delayMicroseconds(a)
#define SET_PIN(a,b) 	digitalWrite(a,b)
/*
#define STB_PIN 	10
#define CLK_PIN		11
#define DIO_PIN		12
*/
#define STB_LOW 	digitalWrite(STB_PIN,LOW)
#define STB_HIGH 	digitalWrite(STB_PIN,HIGH)
#define CLK_LOW 	digitalWrite(CLK_PIN,LOW)
#define CLK_HIGH 	digitalWrite(CLK_PIN,HIGH)
#define DIO_LOW 	digitalWrite(DIO_PIN,LOW)
#define DIO_HIGH 	digitalWrite(DIO_PIN,HIGH)



class Tm1639{
  u8 *code_table;
public:
	Tm1639(const int STB = 10,const int CLK = 11,const int DIO = 12,int state = 0);
	bool Initial_Tm1639(void);
	bool Addr_Static_Mode(u8 *addr, u8 *data, u8 len=1);
	bool Addr_Inc_Mode(u8 *data, u8 light_level = 0x8f);
	bool Display(u8 which=1,u8 number=0);
	~Tm1639 ();
private:
  const int STB_PIN;
  const int CLK_PIN;
  const int DIO_PIN;
	void send_byte(u8 data);
	//u8 read_byte(void);
};


#endif 
