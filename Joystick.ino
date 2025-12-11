
#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // RX, TX

#define ANALOG_X_PIN A2 
#define ANALOG_Y_PIN A3 
#define ANALOG_BUTTON_PIN A4 
	 
//Default values when axis not actioned 
#define ANALOG_X_CORRECTION 128 
#define ANALOG_Y_CORRECTION 128 

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PUSH 5

struct button { 
	 byte pressed = 0; 
}; 
	 
struct analog { 
	 short x, y; 
	 
	 button button; 
}; 



void setup() 
{ 
		Serial.begin(9600); 
		pinMode(ANALOG_BUTTON_PIN, INPUT_PULLUP); 

		mySerial.begin(2400);   // UART communication
} 
	 
void loop() 
{ 

	 analog analog; 
	 
	 analog.x = readAnalogAxisLevel(ANALOG_X_PIN); 
	 analog.y = readAnalogAxisLevel(ANALOG_Y_PIN); 
	 
	 analog.button.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN); 
	 
	//  Serial.print("X:"); 
	//  Serial.println(analog.x); 
	 
	//  Serial.print("Y:"); 
	//  Serial.println(analog.y); 
	// // mySerial.write('A');
	// Serial.println("Test OK");
  // delay(500);
	
			if(analog.x==255 && (analog.y>66 && analog.y<186)){
				Transmit(UP); 
			}
			else if(analog.x==0 && (analog.y>66 && analog.y<186)){
				Transmit(DOWN);
			}
			else if(analog.y==255 && (analog.x>66 && analog.x<186)){
				Transmit(RIGHT);
			}		
			else if(analog.y==0 && (analog.x>66 && analog.x<186)){
				Transmit(LEFT);
			}
			else if (analog.button.pressed){
    		Transmit(PUSH);
	 		}
			delay(50);
} 	 
	 
byte readAnalogAxisLevel(int pin) 
{ 
	 return map(analogRead(pin), 0, 1023, 0, 255); 
} 
	 
bool isAnalogButtonPressed(int pin) 
{ 
	 return digitalRead(pin) == 0; 
} 
void Transmit(int a){
		Serial.println(a);
		//mySerial.write(255);
		mySerial.write(a+48);
}