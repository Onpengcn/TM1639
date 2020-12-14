#include "tm1639.h"

#define STB_PIN   10
#define CLK_PIN   11
#define DIO_PIN   12
//        (STB,    CLK,    DIO) 
Tm1639 dis(STB_PIN,CLK_PIN,DIO_PIN);
void setup() {
  Serial.begin(9600);
  //initial tm1639
  dis.Initial_Tm1639();

  for (int i=1;i<=8;i++){
    for (int j=0;j<=9;j++){
    //dis.Display(Witch,Number);
    dis.Display(i,j);
    delay(500);
    }
  }
}

void loop() {
  
}
