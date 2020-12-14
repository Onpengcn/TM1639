#include "tm1639.h"
/*
//1->8 segment 
u8 segment_addr1_4[8] = {0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce};
u8 segment_addr5_8[8] = {0xc1,0xc3,0xc5,0xc7,0xc9,0xcb,0xcd,0xcf};
u8 segment_number[8][16] = {
                            {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},\
                            {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0},\
              							{4,0,4,0,4,0,4,0,4,0,4,0,4,0,4,0},\
              							{8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0},\
              							{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},\
              							{0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},\
              							{0,4,0,4,0,4,0,4,0,4,0,4,0,4,0,4},\
              							{0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8}
};
// 0->9 display
u8 display_number[10][8] = {{0,1,1,1,0,1,1,1},\
                            {0,1,1,0,0,0,0,0},\
                            {0,1,0,1,1,0,1,1},\
                            {0,1,1,1,1,0,1,0},\
                            {0,1,1,0,1,1,0,0},\
                            {0,0,1,1,1,1,1,0},\
                            {0,0,1,1,1,1,1,1},\
                            {0,1,1,1,0,0,0,0},\
                            {0,1,1,1,1,1,1,1},\
                            {0,1,1,1,1,1,1,0}\
};
*/

Tm1639::Tm1639 (const int STB = 10,const int CLK = 11,const int DIO = 12,int state = 0):STB_PIN(STB),CLK_PIN(CLK),DIO_PIN(DIO){
  u8 code_1[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
  u8 code_2[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
  code_table = new u8[16];

  if(state)
    strcpy(code_table,code_1);
  else
    strcpy(code_table,code_2);
  for(int i=0;i<16;i++)
    Serial.print(code_table[i]);
}

Tm1639::~Tm1639(){
  delete[] code_table;
}

bool Tm1639::Display(u8 which=1,u8 number=0){
  u8 p = (which-1)*2;
  u8 Base_Addr[2] = {0xc0|p,0xc0|(p+1)}; //get seg addr
  //u8 Realnumber = number - 48; //use char to wirte
  u8 Ready2Write[2] = {code_table[number]&0x0f,(code_table[number]&0xf0)>>4};
  
  if (number > 9 || which >8 || number < 0 || which <1)
    return false;
  Addr_Static_Mode(Base_Addr,Ready2Write,2);
  return true;
}

bool Tm1639::Initial_Tm1639(void){
  const u8 init_data[16] = {0};
  pinMode(STB_PIN,OUTPUT);
  pinMode(CLK_PIN,OUTPUT);
  pinMode(DIO_PIN,OUTPUT);
	STB_HIGH;
	CLK_HIGH;
	DIO_HIGH;
	delay_us(1);
	Addr_Inc_Mode(init_data);
	return true;
}

bool Tm1639::Addr_Static_Mode(u8 *addr, u8 *data, u8 len=1){
  u8 i;
  STB_HIGH;
  CLK_HIGH;
  delay_us(1);
  STB_HIGH;
  send_byte(0x44);
  for(i=0;i<len;i++){
    STB_HIGH;
    send_byte(*(addr+i));
    send_byte(*(data+i));
  }
  STB_HIGH;
  send_byte(0x8f);
  STB_HIGH;
  return true;
}

bool Tm1639::Addr_Inc_Mode(u8 *data, u8 light_level = 0x8f){
	u8 i=0;
	STB_HIGH;
	CLK_HIGH;
	delay_us(1);
	STB_HIGH;
	send_byte(0x40);
	STB_HIGH;
	send_byte(0xc0);
	for(i=0;i<16;i++){
		send_byte(*(data+i));
	}
	STB_HIGH;
	send_byte(light_level);
	STB_HIGH;
	return true;
}
/*
u8 Tm1639::read_byte(void){
  u8 i,value=0;
  pinMode(DIO_PIN,INPUT);
  STB_LOW;
  for(i=0;i<8;i++){
    CLK_LOW;
    digitalRead(DIO_PIN);
    CLK_HIGH;
  }
  for(i=0;i<8;i++){
    CLK_LOW;
    digitalRead(DIO_PIN);
    CLK_HIGH;
  }
  pinMode(DIO_PIN,OUTPUT);
}
*/
void Tm1639::send_byte(u8 data){
	u8 i;
	STB_LOW;
	for(i=0;i<8;i++){
		CLK_LOW;
		if((data>>i)&0x01)
			DIO_HIGH;
		else
			DIO_LOW;
		CLK_HIGH;
	}
  delay_us(1);
}
