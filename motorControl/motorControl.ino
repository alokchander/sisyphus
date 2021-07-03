#include <math.h>
int timer = 0;

typedef struct StepMotor{
  int pins[4];
  int currentAng;
  int stepNum = 0;
  int stepSpeed;
  
  }StepMotors;

// Split instr according to things that happen at once
// If one happens faster than other then faster one stops and slower keeps repeating
// Can't move to next instr unless steps for both motors are done
// instr are for change in angle not final angle(Get the difference ;))
static int angleInstrM1 = [90];
static int dirInstrM1 = [true];
static int angleInstrM2 = [90];
static int dirInstrM2 = [true];
static StepMotors M1,M2;



void setup() {


  TCCR0A=(1<<WGM01);    //Set the CTC mode   
  OCR0A=0xF9; //Value for ORC0A for 1ms 
  
  TIMSK0|=(1<<OCIE0A);   //Set the interrupt request
  sei(); //Enable interrupt
  
  TCCR0B|=(1<<CS01);    //Set the prescale 1/64 clock
  TCCR0B|=(1<<CS00);
  
  // Pinmode setup
  M1.pins[0] = 9;
  M1.pins[1] = 10;
  M1.pins[2] = 11;
  M1.pins[3] = 12;

  M2.pins[0] = 4;
  M2.pins[1] = 5;
  M2.pins[2] = 6;
  M2.pins[3] = 7;
  Serial.begin(9600);
  
  pinMode(M1.pins[0], OUTPUT);
  pinMode(M1.pins[1], OUTPUT);
  pinMode(M1.pins[2], OUTPUT);
  pinMode(M1.pins[3], OUTPUT);
  
  pinMode(M2.pins[0], OUTPUT);
  pinMode(M2.pins[1], OUTPUT);
  pinMode(M2.pins[2], OUTPUT);
  pinMode(M2.pins[3], OUTPUT);
  

}

  void OneStep(StepMotors *Motor,bool dir){
    if(dir){
switch((*Motor).stepNum){
  case 0:
  digitalWrite((*Motor).pins[0], HIGH);
  digitalWrite((*Motor).pins[1], LOW);
  digitalWrite((*Motor).pins[2], LOW);
  digitalWrite((*Motor).pins[3], LOW);
  break;
  case 1:
  digitalWrite((*Motor).pins[0], LOW);
  digitalWrite((*Motor).pins[1], HIGH);
  digitalWrite((*Motor).pins[2], LOW);
  digitalWrite((*Motor).pins[3], LOW);
  break;
  case 2:
  digitalWrite((*Motor).pins[0], LOW);
  digitalWrite((*Motor).pins[1], LOW);
  digitalWrite((*Motor).pins[2], HIGH);
  digitalWrite((*Motor).pins[3], LOW);
  break;
  case 3:
   digitalWrite((*Motor).pins[0], LOW);
  digitalWrite((*Motor).pins[1], LOW);
  digitalWrite((*Motor).pins[2], LOW);
  digitalWrite((*Motor).pins[3], HIGH);
  break;
} 
  }else{
    switch((*Motor).stepNum){
  case 0:
  digitalWrite((*Motor).pins[0], LOW);
  digitalWrite((*Motor).pins[1], LOW);
  digitalWrite((*Motor).pins[2], LOW);
  digitalWrite((*Motor).pins[3], HIGH);
  break;
  case 1:
    digitalWrite((*Motor).pins[0], LOW);
  digitalWrite((*Motor).pins[1], LOW);
  digitalWrite((*Motor).pins[2], HIGH);
  digitalWrite((*Motor).pins[3], LOW);
  break;
  case 2:
  digitalWrite((*Motor).pins[0], LOW);
  digitalWrite((*Motor).pins[1], HIGH);
  digitalWrite((*Motor).pins[2], LOW);
  digitalWrite((*Motor).pins[3], LOW);
  break;
  case 3:
  digitalWrite((*Motor).pins[0], HIGH);
  digitalWrite((*Motor).pins[1], LOW);
  digitalWrite((*Motor).pins[2], LOW);
  digitalWrite((*Motor).pins[3], LOW);
 
  
} 
  }
  Serial.println("B");
  Serial.println((*Motor).stepNum);
(*Motor).stepNum = (*Motor).stepNum + 1;
Serial.println("A");
Serial.println((*Motor).stepNum);

  if((*Motor).stepNum > 3){
    
    (*Motor).stepNum = 0;
  }
  //works Serial.println(M1.stepNum);
}


  
  
  
  
void loop() {
  // For loop to go through all the instructions
  for(int j = 0; j < 1;j++  )
  {
  
 // Convert angle to steps
  stepsM1 = (anglrInstrM1[j]/360)*2048;
  stepsM2 = (anglrInstrM2[j]/360)*2048;
  // can include delay as well by adding and tick =  some number
  // Runs loop again and again until required number of steps has been completed
  while(stepsM1Counter < stepsM1 && stepsM2Counter < stepsM2 )
    if(stepsM1Counter < stepsM1){
      Onestep(&M1, dirInstrM1[j]);
      stepM1Counter++;
    }
    if(stepsM2Counter < stepsM2){
      Onestep(&M2, dirInstrM2[j]);
      stepM2Counter++;
    }
  }
}
  }

  ISR(TIMER0_COMPA_vect){    //This is the interrupt request
  timer++;
}
