#define F_CPU 16000000L //defines clock frequency

#include <avr/io.h> // Call in the AVR/IO library
#include <avr/delay.h> //Call in the AVR/delay library
#include <Arduino.h> //Call in the Arduino library

int incomingByte = 0;
int incoming[3];

int command = 0;
int ActivePump = 1;
int error = 0;

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
  PORTB = 0xF0;
  PORTC = 0;
  PORTD = 0;
  PORTE = 0;
  PORTG = 0;
  PORTH = 0x73;
  PORTJ = 0x03;
  PORTL = 0;
}

/*int ReadFlowRate(SensorNum) {
  SIGNAL(TIMER0_COMPA_vect){
    
  }

}*/

int ActivatePump(){
  if((PINB4 && ActivePump == 1) || (PINB5 && ActivePump == 2)){

    error = 1;
    return 1;
  }

  if(ActivePump == 1){
    PORTE += 0x10;
    return 0;
  } else {
    PORTE += 0x20;
    return 0;
  }
}

void StopPump(){
  if(ActivePump == 1){
    PORTE -= 0x10;
  } else {
    PORTE -= 0x20;
  }
}

void OpenMains(){
  PORTG += 0x20;
  PORTE += 0x08;
  PORTH += 0x08;
}

void CloseMains(){
  PORTG -= 0x20;
  PORTE -= 0x08;
  PORTH -= 0x08;
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

    int commandClass = command/100;
    int SubCommand = command-(commandClass*100);

    if(commandClass == 1){

      //1xx commands turn on digital pins

      switch(SubCommand){
        case 02:
          PORTE += 0x10;
          command = 0;
          break;
        case 03:
          PORTE += 0x20;
          command = 0;
          break;
        case 04:
          PORTG += 0x20;
          command = 0;
          break;
        case 05:
          PORTE += 0x08;
          command = 0;
          break;
        case 06:
          PORTH += 0x08;
          command = 0;
          Serial.println("Received");
          break;
        //Skipping 107-117 because those are input pins
        case 18:
          PORTD += 0x08;
          command = 0;
          break;
        case 19:
          PORTD += 0x04;
          command = 0;
          break;
        case 20:
          PORTD +=0x02;
          command = 0;
          break;
        case 21:
          PORTD += 0x01;
          command = 0;
          break;
        case 22:
          PORTA += 0x01;
          command = 0;
          break;
        case 23:
          PORTA +=0x02;
          command = 0;
          break;
        case 24:
          PORTA += 0x04;
          command = 0;
          break;
        case 25:
          PORTA += 0x08;
          command = 0;
          break;
        case 26:
          PORTA += 0x10;
          command = 0;
          break;
        case 27:
          PORTA += 0x20;
          command = 0;
          break;
        case 28:
          PORTA += 0x40;
          command = 0;
          break;
        case 29:
          PORTA += 0x80;
          command = 0;
          break;
        case 30:
          PORTC += 0x80;
          command = 0;
          break;
        case 31:
          PORTC += 0x40;
          command = 0;
          break;
        case 32:
          PORTC += 0x20;
          command = 0;
          break;
        case 33:
          PORTC += 0x10;
          command = 0;
          break;
        case 34:
          PORTC += 0x08;
          command = 0;
          break;
        case 35:
          PORTC += 0x04;
          command = 0;
          break;
        case 36:
          PORTC +=0x02;
          command = 0;
          break;
        case 37:
          PORTC += 0x01;
          command = 0;
          break;
        case 38:
          PORTD += 0x80;
          command = 0;
          break;
        case 39:
          PORTG += 0x04;
          command = 0;
          break;
        case 40:
          PORTG +=0x02;
          command = 0;
          break;
        case 41:
          PORTG += 0x01;
          command = 0;
          break;
        case 42:
          PORTL += 0x80;
          command = 0;
          break;
        case 43:
          PORTL += 0x40;
          command = 0;
          break;
        case 44:
          PORTL += 0x20;
          command = 0;
          break;
        case 45:
          PORTL += 0x10;
          command = 0;
          break;
        case 46:
          PORTL += 0x08;
          command = 0;
          break;
        case 47:
          PORTL += 0x04;
          command = 0;
          break;
        case 48:
          PORTL +=0x02;
          command = 0;
          break;
        case 49:
          PORTL += 0x01;
          command = 0;
          break;
        case 50:
          PORTB += 0x08;
          command = 0;
          break;
        case 51:
          PORTB += 0x04;
          command = 0;
          break;
        case 52:
          PORTB +=0x02;
          command = 0;
          break;
        case 53:
          PORTB += 0x01;
          command = 0;
          break;
      }
    } else if(commandClass==2){

      //2xx commands turn off digital pins

      switch(SubCommand){
        case 02:
          PORTE -= 0x10;
          command = 0;
          break;
        case 03:
          PORTE -= 0x20;
          command = 0;
          break;
        case 04:
          PORTG -= 0x20;
          command = 0;
          break;
        case 05:
          PORTE -= 0x08;
          command = 0;
          break;
        case 06:
          PORTH -= 0x08;
          command = 0;
          break;
        //Skipping 207-217 because those are input pins
        case 18:
          PORTD -= 0x08;
          command = 0;
          break;
        case 19:
          PORTD -= 0x04;
          command = 0;
          break;
        case 20:
          PORTD -=0x02;
          command = 0;
          break;
        case 21:
          PORTD -= 0x01;
          command = 0;
          break;
        case 22:
          PORTA -= 0x01;
          command = 0;
          break;
        case 23:
          PORTA -=0x02;
          command = 0;
          break;
        case 24:
          PORTA -= 0x04;
          command = 0;
          break;
        case 25:
          PORTA -= 0x08;
          command = 0;
          break;
        case 26:
          PORTA -= 0x10;
          command = 0;
          break;
        case 27:
          PORTA -= 0x20;
          command = 0;
          break;
        case 28:
          PORTA -= 0x40;
          command = 0;
          break;
        case 29:
          PORTA -= 0x80;
          command = 0;
          break;
        case 30:
          PORTC -= 0x80;
          command = 0;
          break;
        case 31:
          PORTC -= 0x40;
          command = 0;
          break;
        case 32:
          PORTC -= 0x20;
          command = 0;
          break;
        case 33:
          PORTC -= 0x10;
          command = 0;
          break;
        case 34:
          PORTC -= 0x08;
          command = 0;
          break;
        case 35:
          PORTC -= 0x04;
          command = 0;
          break;
        case 36:
          PORTC -=0x02;
          command = 0;
          break;
        case 37:
          PORTC -= 0x01;
          command = 0;
          break;
        case 38:
          PORTD -= 0x80;
          command = 0;
          break;
        case 39:
          PORTG -= 0x04;
          command = 0;
          break;
        case 40:
          PORTG -=0x02;
          command = 0;
          break;
        case 41:
          PORTG -= 0x01;
          command = 0;
          break;
        case 42:
          PORTL -= 0x80;
          command = 0;
          break;
        case 43:
          PORTL -= 0x40;
          command = 0;
          break;
        case 44:
          PORTL -= 0x20;
          command = 0;
          break;
        case 45:
          PORTL -= 0x10;
          command = 0;
          break;
        case 46:
          PORTL -= 0x08;
          command = 0;
          break;
        case 47:
          PORTL -= 0x04;
          command = 0;
          break;
        case 48:
          PORTL -=0x02;
          command = 0;
          break;
        case 49:
          PORTL -= 0x01;
          command = 0;
          break;
        case 50:
          PORTB -= 0x08;
          command = 0;
          break;
        case 51:
          PORTB -= 0x04;
          command = 0;
          break;
        case 52:
          PORTB -=0x02;
          command = 0;
          break;
        case 53:
          PORTB -= 0x01;
          command = 0;
          break;
      }
    } else if(commandClass==3){

      //3xx commands control pumps (302 & 303) and activate and deactivate water change (318-389)
      switch(SubCommand){
        case 02:
          ActivePump = 1;
          command = 0;
          break;
        case 03:
          ActivePump = 2;
          break;
        case 18:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTD += 0x08;
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
          PORTD -= 0x08;
          CloseMains();
          StopPump();
          break;

      }
    } else if(commandClass == 4){

      //4xx commands read analog inputs
      switch(SubCommand){

      }
    } else if(commandClass == 5){

      //5xx commands read digital inputs
      switch(SubCommand){

      }
    }/*case 400:
        int initalRead; 
        initialRead = analogRead(A0);
        Serial.println(initialRead);
        command = 0;
        break;*/    

}
