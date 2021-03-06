#define F_CPU 16000000L //defines clock frequency

#include <avr/io.h> // Call in the AVR/IO library
#include <avr/delay.h> //Call in the AVR/delay library
#include <Arduino.h> //Call in the Arduino library

//int incomingByte = 0;
//int incoming[3];

int command = 0;
int ActivePump = 1;
int error = 0;

//Variables for FlowMeters
volatile uint16_t pulse=0;
volatile uint8_t lastState;
volatile uint32_t lastTimer=0;
volatile float flowrate;

SIGNAL(TIMER0_COMPA_vect){
  uint8_t x = digitalRead(13);
  
  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }
  
  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // in hertz
  lastflowratetimer = 0;
}


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
  if((!PINH4 && ActivePump == 1) || (!PINH5 && ActivePump == 2)){

    error = 1;
    return 1;
  }

  if(ActivePump == 1){
    PORTE |= _BV(4);
    return 0;
  } else {
    PORTE |= _BV(5);
    return 0;
  }
}

void StopPump(){
  if(ActivePump == 1){
    PORTE &= ~_BV(4);
  } else {
    PORTE &= ~_BV(5);
  }
}

void OpenMains(){
  PORTG |= _BV(5);
  PORTE |= _BV(3);
  PORTH |= _BV(3);
}

void CloseMains(){
  PORTG &= ~_BV(5);
  PORTE &= ~_BV(3);
  PORTH &= ~_BV(3);
}

void readFlowMeter(){


}

void startInterrupt(boolean s){
  if(s){
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
  }
}

void loop() {
  if(Serial.available()){

    char First = Serial.read();
    Serial.println(First); //Debugging for serial communication
    if(First >= '0' && First <= '9'){
        command = (command*10)+(First-48); 
      } /*code for debugging the serial communication

      else if(First == 10){ 

        Serial.print("Command received: ");
        Serial.println(command);      
        }

    Serial.print("Command received: ");
    Serial.println(command);*/
    }

    int commandClass = command/100;
    int SubCommand = command-(commandClass*100);

    if(commandClass == 1){

      //1xx commands turn on digital pins

      switch(SubCommand){
        case 02:
          PORTE |= _BV(4);
          command = 0;
          break;
        case 03:
          PORTE |= _BV(5);
          command = 0;
          break;
        case 04:
          PORTG |= _BV(5);
          command = 0;
          break;
        case 05:
          PORTE |= _BV(3);
          command = 0;
          break;
        case 06:
          PORTH |= _BV(3);
          command = 0;
          Serial.println("Received");
          break;
        //Skipping 107-117 because those are input pins
        case 18:
          PORTD |= _BV(3);
          command = 0;
          break;
        case 19:
          PORTD |= _BV(2);
          command = 0;
          break;
        case 20:
          PORTD |= _BV(1);
          command = 0;
          break;
        case 21:
          PORTD |= _BV(0);
          command = 0;
          break;
        case 22:
          PORTA |= _BV(0);
          command = 0;
          break;
        case 23:
          PORTA |= _BV(1);
          command = 0;
          break;
        case 24:
          PORTA |= _BV(2);
          command = 0;
          break;
        case 25:
          PORTA |= _BV(3);
          command = 0;
          break;
        case 26:
          PORTA |= _BV(4);
          command = 0;
          break;
        case 27:
          PORTA |= _BV(5);
          command = 0;
          break;
        case 28:
          PORTA |= _BV(6);
          command = 0;
          break;
        case 29:
          PORTA |= _BV(7);
          command = 0;
          break;
        case 30:
          PORTC |= _BV(7);
          command = 0;
          break;
        case 31:
          PORTC |= _BV(6);
          command = 0;
          break;
        case 32:
          PORTC |= _BV(5);
          command = 0;
          break;
        case 33:
          PORTC |= _BV(4);
          command = 0;
          break;
        case 34:
          PORTC |= _BV(3);
          command = 0;
          break;
        case 35:
          PORTC |= _BV(2);
          command = 0;
          break;
        case 36:
          PORTC |= _BV(1);
          command = 0;
          break;
        case 37:
          PORTC |= _BV(0);
          command = 0;
          break;
        case 38:
          PORTD |= _BV(7);
          command = 0;
          break;
        case 39:
          PORTG |= _BV(2);
          command = 0;
          break;
        case 40:
          PORTG |= _BV(1);
          command = 0;
          break;
        case 41:
          PORTG |= _BV(0);
          command = 0;
          break;
        case 42:
          PORTL |= _BV(7);
          command = 0;
          break;
        case 43:
          PORTL |= _BV(6);
          command = 0;
          break;
        case 44:
          PORTL |= _BV(5);
          command = 0;
          break;
        case 45:
          PORTL |= _BV(4);
          command = 0;
          break;
        case 46:
          PORTL |= _BV(3);
          command = 0;
          break;
        case 47:
          PORTL |= _BV(2);
          command = 0;
          break;
        case 48:
          PORTL = PORTL | _BV(1);
          command = 0;
          break;
        case 49:
          PORTL |= _BV(0);
          command = 0;
          break;
        case 50:
          PORTB |= _BV(3);
          command = 0;
          break;
        case 51:
          PORTB |= _BV(2);
          command = 0;
          break;
        case 52:
          PORTB |= _BV(1);
          command = 0;
          break;
        case 53:
          PORTB |= _BV(0);
          command = 0;
          break;
      }
    } else if(commandClass==2){

      //2xx commands turn off digital pins

      switch(SubCommand){
        case 02:
          PORTE &= ~_BV(4);
          command = 0;
          break;
        case 03:
          PORTE &= ~_BV(5);
          command = 0;
          break;
        case 04:
          PORTG &= ~_BV(5);
          command = 0;
          break;
        case 05:
          PORTE &= ~_BV(3);
          command = 0;
          break;
        case 06:
          PORTH &= ~_BV(3);
          command = 0;
          break;
        //Skipping 207-217 because those are input pins
        case 18:
          PORTD &= ~_BV(3);
          command = 0;
          break;
        case 19:
          PORTD &= ~_BV(2);
          command = 0;
          break;
        case 20:
          PORTD &= ~_BV(1);
          command = 0;
          break;
        case 21:
          PORTD &= ~_BV(0);
          command = 0;
          break;
        case 22:
          PORTA &= ~_BV(0);
          command = 0;
          break;
        case 23:
          PORTA -=_BV(1);
          command = 0;
          break;
        case 24:
          PORTA &= ~_BV(2);
          command = 0;
          break;
        case 25:
          PORTA &= ~_BV(3);
          command = 0;
          break;
        case 26:
          PORTA &= ~_BV(4);
          command = 0;
          break;
        case 27:
          PORTA &= ~_BV(5);
          command = 0;
          break;
        case 28:
          PORTA &= ~_BV(6);
          command = 0;
          break;
        case 29:
          PORTA &= ~_BV(7);
          command = 0;
          break;
        case 30:
          PORTC &= ~_BV(7);
          command = 0;
          break;
        case 31:
          PORTC &= ~_BV(6);
          command = 0;
          break;
        case 32:
          PORTC &= ~_BV(5);
          command = 0;
          break;
        case 33:
          PORTC &= ~_BV(4);
          command = 0;
          break;
        case 34:
          PORTC &= ~_BV(3);
          command = 0;
          break;
        case 35:
          PORTC &= ~_BV(2);
          command = 0;
          break;
        case 36:
          PORTC -=_BV(1);
          command = 0;
          break;
        case 37:
          PORTC &= ~_BV(0);
          command = 0;
          break;
        case 38:
          PORTD &= ~_BV(7);
          command = 0;
          break;
        case 39:
          PORTG &= ~_BV(2);
          command = 0;
          break;
        case 40:
          PORTG -=_BV(1);
          command = 0;
          break;
        case 41:
          PORTG &= ~_BV(0);
          command = 0;
          break;
        case 42:
          PORTL &= ~_BV(7);
          command = 0;
          break;
        case 43:
          PORTL &= ~_BV(6);
          command = 0;
          break;
        case 44:
          PORTL &= ~_BV(5);
          command = 0;
          break;
        case 45:
          PORTL &= ~_BV(4);
          command = 0;
          break;
        case 46:
          PORTL &= ~_BV(3);
          command = 0;
          break;
        case 47:
          PORTL &= ~_BV(2);
          command = 0;
          break;
        case 48:
          PORTL &= ~_BV(1);
          command = 0;
          break;
        case 49:
          PORTL &= ~_BV(0);
          command = 0;
          break;
        case 50:
          PORTB &= ~_BV(3);
          command = 0;
          break;
        case 51:
          PORTB &= ~_BV(2);
          command = 0;
          break;
        case 52:
          PORTB -=_BV(1);
          command = 0;
          break;
        case 53:
          PORTB &= ~_BV(0);
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
        case 04:
          ActivatePump();
          break;
        case 05:
          StopPump();
          break;
        case 06:
          OpenMains();
          break;
        case 07:
          CloseMains();
          break;
        case 18:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTD |= _BV(3);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 19:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTD |= _BV(2);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 20:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTD |= _BV(1);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 21:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTD |= _BV(0);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 22:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(0);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 23:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(1);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 24:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(2);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 25:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(3);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 26:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(4);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 27:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(5);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 28:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(6);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 29:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTA |= _BV(7);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 30:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(7);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 31:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(6);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 32:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(5);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 33:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(4);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 34:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(3);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 35:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(2);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 36:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(1);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 37:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTC |= _BV(0);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 38:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTD |= _BV(7);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 39:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTG |= _BV(2);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 40:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTG |= _BV(1);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 41:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTG |= _BV(0);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 42:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(7);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 43:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(6);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 44:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(5);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 45:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(4);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 46:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(3);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 47:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(2);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 48:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(1);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 49:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTL |= _BV(0);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 50:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTB |= _BV(3);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 51:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTB |= _BV(2);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 52:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTB |= _BV(1);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 53:
          int errorCheck = ActivatePump();
          if(errorCheck == 0){
            OpenMains();
            PORTB |= _BV(0);
            command = 0;
            break;
          } else {
            command = 0;
            break;
          }
        case 54:
          PORTD &= ~_BV(3);
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
        case 507:
          

      }
    }
    commandClass = 0;
    SubCommand = 0;
    /*case 400:
        int initalRead; 
        initialRead = analogRead(A0);
        Serial.println(initialRead);
        command = 0;
        break;*/    

}
