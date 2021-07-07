#include <math.h>
#include <stdlib.h>
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
static int angleInstrM1[] = {90};
static int dirInstrM1[] = {true};
static int angleInstrM2[] = {90};
static int dirInstrM2[] = {true};
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
  int lengthArray = sizeof(angleInstrM1)/sizeof(int);
  
  for(int j = 0; j < lengthArray;j++  )
  {
    
  int stepM1Counter = 0;
  int stepM2Counter = 0;
 // Convert angle to steps
  long stepsM1 = (angleInstrM1[j]*(long)2048)/360;
  Serial.println(stepsM1);
  long stepsM2 = (angleInstrM2[j]*(long)2048)/360;
  // can include delay as well by adding and tick =  some number
  // Runs loop again and again until required number of steps has been completed
  while(stepM1Counter < stepsM1 && stepM2Counter < stepsM2 )
 
    if(stepM1Counter < stepsM1){
      
      //OneStep(&M1, dirInstrM1[j]);
       
      stepM1Counter++;
    }
    if(stepM2Counter < stepsM2){
    OneStep(&M2, dirInstrM2[j]);
     // Serial.println("cmd");
      stepM2Counter++;
    }
  }
}
 

  ISR(TIMER0_COMPA_vect){    //This is the interrupt request
  timer++;
}
