long frontLeftEcho = 2;
long frontRightEcho = 4;
long leftLeftEcho = 14;
long leftRightEcho = 16;
long backLeftEcho = 10;
long backRightEcho = 12;
long rightLeftEcho = 6;
long rightRightEcho = 8;

long frontLeftTrigger = 3;
long frontRightTrigger = 5;
long leftLeftTrigger = 15;
long leftRightTrigger = 17;
long backLeftTrigger = 11;
long backRightTrigger = 13;
long rightLeftTrigger = 7;
long rightRightTrigger = 9;

long frontLeftDistance = 0;
long frontRightDistance = 0;
long leftLeftDistance = 0;
long leftRightDistance = 0;
long backLeftDistance = 0;
long backRightDistance = 0;
long rightLeftDistance = 0;
long rightRightDistance = 0;

void setup() {
  Serial.begin (9600);

  pinMode(frontLeftTrigger,OUTPUT);
  pinMode(frontLeftEcho,INPUT);
  
  pinMode(frontRightTrigger,OUTPUT);
  pinMode(frontRightEcho,INPUT);
  
  pinMode(leftLeftTrigger,OUTPUT);
  pinMode(leftLeftEcho,INPUT);
  
  pinMode(leftRightTrigger,OUTPUT);
  pinMode(leftRightEcho,INPUT);
  
  pinMode(backLeftTrigger,OUTPUT);
  pinMode(backLeftEcho,INPUT);

  pinMode(backRightTrigger,OUTPUT);
  pinMode(backRightEcho,INPUT);

  pinMode(rightLeftTrigger,OUTPUT);
  pinMode(rightLeftEcho,INPUT);
  
  pinMode(rightRightTrigger,OUTPUT);
  pinMode(rightRightEcho,INPUT);
  
  
}

void trigger(int pin){
  digitalWrite(pin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(pin, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(pin, LOW);
  
}

long getDistance(int pin){

  long duration = pulseIn(pin, HIGH);
  long distance = duration/58.2;
  return distance;
  
}

void updateFrontLeftDistance(){
  trigger(frontLeftTrigger);
  frontLeftDistance = getDistance(frontLeftEcho);
}

void updateFrontRightDistance(){
  trigger(frontRightTrigger);
  frontRightDistance = getDistance(frontRightEcho);
}

void updateLeftLeftDistance(){
  trigger(leftLeftTrigger);
  leftLeftDistance = getDistance(leftLeftEcho);
}

void updateLeftRightDistance(){
  trigger(leftRightTrigger);
  leftRightDistance = getDistance(leftRightEcho);
}

void updateBackLeftDistance(){
  trigger(backLeftTrigger);
  backLeftDistance = getDistance(backLeftEcho);
}

void updateBackRightDistance(){
  trigger(backRightTrigger);
  backRightDistance = getDistance(backRightEcho);
}

void updateRightLeftDistance(){
  trigger(rightLeftTrigger);
  rightLeftDistance = getDistance(rightLeftEcho);
}

void updateRightRightDistance(){
  trigger(rightRightTrigger);
  rightRightDistance = getDistance(rightRightEcho);
}

void updateSensors(){
  updateFrontLeftDistance();
  updateFrontRightDistance();
  updateLeftLeftDistance();
  updateLeftRightDistance();
  updateBackLeftDistance();
  updateBackRightDistance();
  updateRightLeftDistance();
  updateRightRightDistance();
}

void reportSensors(){
  reportSensor('F','L',frontLeftDistance);
  reportSensor('F','R',frontRightDistance);
  reportSensor('L','L',leftLeftDistance);
  reportSensor('L','R',leftRightDistance);
  reportSensor('B','L',backLeftDistance);
  reportSensor('B','R',backRightDistance);
  reportSensor('R','L',rightLeftDistance);
  reportSensor('R','R',rightRightDistance);
}

void reportSensor(char location, char place, int distance){
  String report = "S";
  report += location;
  report += place;
  report += distance;
  report += ";\r\n";

  Serial.print(report);
}

void loop() {
  updateSensors();
  reportSensors();
  delay(200);
}