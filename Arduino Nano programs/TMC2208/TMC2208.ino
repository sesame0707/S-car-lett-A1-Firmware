//The DIY Life
//Michael Klements
//30 April 2020

int stepPin = 3;          //Define travel stepper motor step pin
int dirPin = 4;           //Define travel stepper motor direction pin
int motSpeed = 5;         //Initial motor speed (delay between pules, so a smaller delay is faster)

void setup() 
{
  pinMode(stepPin, OUTPUT);                 //Define pins and set direction
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
}

void loop() 
{
  motSpeed = map(analogRead(A0),0,1023,50,1);           //Read in potentiometer value from A0, map to a delay between 1 and 50 milliseconds
  digitalWrite(stepPin, HIGH);                          //Step the motor with the set delay
  // delay(motSpeed);
  digitalWrite(stepPin, LOW);
  // delay(motSpeed);
}
