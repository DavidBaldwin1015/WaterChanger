#define F_CPU 16000000L //defines clock frequency

#include <avr/io.h> // Call in the AVR/IO library
#include <avr/delay.h> //Call in the AVR/delay library

int incomingByte = 0;
byte incoming[3];

int command = 0;

void setup() {
  Serial.begin(9600);
  DDRH = 0xFF;
  PORTH = 0;
}

void loop() {
  if(Serial.available()){

    char First = Serial.read();
    // Serial.println(First); Debugging for serial communication
    if(First >= '0' && First <= '9'){
        command = (command*10)+(First-48);
      } /* code for debugging the serial communication
      
      else if(First == 10){ 

        Serial.print("Command received: ");
        Serial.println(command);      
        }

    Serial.print("Command received: ");
    Serial.println(command);
   */
    }

    switch(command){
      case 108:
        PORTH = 0x20;
        // Serial.println("recognized"); For debugging, making sure the command is recognized
        command = 0;
        break;
      case 112:
        PORTB = 0x10;
        command = 0;
        break;
      case 110:
        PORTB += 4;
        command = 0;
        break;
      case 208:
        PORTH -= 0x20;
        command = 0;
        break;
      case 210:
        PORTB -= 4;
        command = 0;
        break;
      case 212:
        PORTB -= 0x10;
        command = 0;
        break;
      case 312:
        for(int i = 0; i <= 5; i++){
            PORTB = 0x10;
            _delay_ms(1000);
            PORTB -= 0x10;
            _delay_ms(1000);
          }
        command = 0;
        break; 
      }

}
