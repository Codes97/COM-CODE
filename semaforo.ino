/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define RED_LIGHT 0
#define YELLOW_LIGHT 1
#define GREEN_LIGHT 2

#define STATE_TIME 4000

#define RED_PIN 12
#define YELLOW_PIN 11
#define GREEN_PIN 10

int actual_light = 0;
int actual_time = 0;
int last_change = 0;
int wait_time = 0;

bool ascending = false;

bool demand = false;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(4800);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  actual_time = millis();
  
  if(wait_time-actual_time <= 0 && !demand){
    last_change = actual_time;
    switchColor();
  }
  printState();
}

void ledOn(int color){
  switch(color){
    case RED_LIGHT:
      wait_time = STATE_TIME+last_change;
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      break;
    case YELLOW_LIGHT:
      wait_time = (STATE_TIME/2)+last_change;
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      break;
    case GREEN_LIGHT: 
      wait_time = STATE_TIME+last_change;
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      break;
  }
}

void switchColor(){
  checkAscending();

  if(ascending) actual_light++;
  else actual_light--;
  
  ledOn(actual_light);
}

void checkAscending(){
  if(ascending && actual_light+1 > 2){
    ascending = false;
  }
  else if(!ascending && actual_light-1 <0){
    ascending = true;
  }
}

void printState(){
  Serial.println("----------------------------------------");
  Serial.print("Actual light: ");
  Serial.println(actual_light);
  Serial.print("Actual time: ");
  Serial.println(actual_time);
  Serial.print("Last change: ");
  Serial.println(last_change);
  Serial.print("Wait time: ");
  Serial.println(wait_time);
  Serial.print("Next change: ");
  Serial.println(last_change+wait_time);
}
