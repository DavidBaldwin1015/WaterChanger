#define F_CPU 16000000L //defines clock frequency

#include <avr/io.h> // Call in the AVR/IO library
#include <avr/delay.h> //Call in the AVR/delay library
#include <Arduino.h> //Call in the Arduino library

int incomingByte = 0;
int incoming[3];

int command = 0;
int ActivePump = 1;

void setup() {
  Serial.begin(9600);

  // Set data direction registers for digital pins: each bit is set to 1 for output, 0 for input
  DDRA = 0xFF;
  DDRB = 0b00001111;
  DDRC = 0xFF;
  DDRD = 0x8F;
  DDRE = 0x38;
  DDRG = 0x27;
  DDRH = 0x08;
  DDRJ = 0x00;
  DDRL = 0xFF;


  //Set inital port values for digital pins
  PORTA = 0;
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;
  PORTE = 0;
  PORTG = 0;
  PORTH = 0;
  PORTJ = 0;
  PORTL = 0;
}

/*int ReadFlowRate(SensorNum) {
  SIGNAL(TIMER0_COMPA_vect){
    
  }

}*/

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

      // 1xx commands turn on digital pins
      case 102:
        PORTE += 0x10;
        command = 0;
        break;
      case 103:
        PORTE += 0x20;
        command = 0;
        break;
      case 104:
        PORTG += 0x20;
        command = 0;
        break;
      case 105:
        PORTE += 0x08;
        command = 0;
        break;
      case 106:
        PORTH += 0x08;
        command = 0;
        break;
      //Skipping 107-117 because those are input pins
      case 118:
        PORTD += 0x08;
        command = 0;
        break;
      case 119:
        PORTD += 0x04;
        command = 0;
        break;
      case 120:
        PORTD +=0x02;
        command = 0;
        break;
      case 121:
        PORTD += 0x01;
        command = 0;
        break;

      // 2xx commands turn off digital pins
      case 202:
        PORTE -= 0x10;
        command = 0;
        break;
      case 203:
        PORTE -= 0x20;
        command = 0;
        break;
      case 204:
        PORTG -= 0x20;
        command = 0;
        break;
      case 205:
        PORTE -= 0x08;
        command = 0;
        break;
      case 206:
        PORTH -= 0x08;
        command = 0;
        break;
      //Skipping 107-117 because those are input pins
      case 218:
        PORTD -= 0x08;
        command = 0;
        break;
      case 219:
        PORTD -= 0x04;
        command = 0;
        break;
      case 220:
        PORTD -=0x02;
        command = 0;
        break;
      case 221:
        PORTD -= 0x01;
        command = 0;
        break;

      //3xx commands control pumps and activate water change cycle
      case 312:
        for(int i = 0; i <= 5; i++){
            PORTB = 0x10;
            _delay_ms(1000);
            PORTB -= 0x10;
            _delay_ms(1000);
          }
        command = 0;
        break;

      //4xx commands read analog inputs
      /*case 400:
        int initalRead; 
        initialRead = analogRead(A0);
        Serial.println(initialRead);
        command = 0;
        break;*/

      //5xx commands read digital inputs 
      }

}
