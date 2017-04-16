
// Patterned Line Solving Algorithm
// Written By Dheeraj Allamaneni and Chatti Vamshi Krishna.
// This work is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
// Adaptations of this work are allowed.
// Commercial usage of this work is restricted.
// Fork updations to this code to the main github repository. *(GITHUB LINKS BELOW)*
// Any feedback or improvements are appreciated.




//Initializing the pins which we are going to use on the arduino
int lm1=A0;
int lm2=A1;
int rm1=A2;
int rm2=A3;
int ss1=6;
int ss2=7;
int ss3=8;
int ss4=9;
int ss5=10;
int ss6=11;
int ss7=12;
int ss8=13;
#define trigPin 2
#define echoPin 3
int a,b,c,d,e,f,g,h,p,k,i;
char path[100];
int pathLength=0;
int readLength=0;
int replaystage=0;
int switchPin=4;
int LED=A5;
int v=0;
long distance,duration;


//Setting up the pin modes for all the pins we wish to use
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(ss1,INPUT);
  pinMode(ss2,INPUT);
  pinMode(ss3,INPUT);
  pinMode(ss4,INPUT);
  pinMode(ss5,INPUT);
  pinMode(ss6,INPUT);
  pinMode(ss7,INPUT);
  pinMode(ss8,INPUT);
  pinMode(switchPin, INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  
}



// The function reads the vaules of all the sensors and updates their values from its previous ones
void readsensors(){
  a=digitalRead(ss1);
  b=digitalRead(ss2);
c=digitalRead(ss3);
  d=digitalRead(ss4);
  e=digitalRead(ss5);
  f=digitalRead(ss6);
  g=digitalRead(ss7);
  h=digitalRead(ss8);
}


//The code which is repeated over the course of runtime
// The rover stores the path that it travelled through and sends it to the shortest path function.
void loop()
{
  //Initializing a starting point to refer back to incase of change in sensor values.
  WELCOME :
  //Checks the distance of obstacle from the ultrasonic sensor. ( USED TO DETERMINE END POINT )
  distance=check_distance();
  //Reads all the values of sensors to update their properties
  readsensors();

  //Conditions and their respective responses
if(a==LOW && h==LOW && ( d==HIGH || e==HIGH ) && (distance>12 && digitalRead(switchPin)==LOW && v==0))
{
  //Functions are described below
  straight();
}

else if( (a==HIGH || b==HIGH) && (d==HIGH || e==HIGH) && (g==HIGH || h==HIGH) && ( distance>12  && digitalRead(switchPin)==LOW && v==0) )
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(20);
  if( (digitalRead(ss1)==HIGH && digitalRead(ss2)==HIGH) && ( digitalRead(ss4)==HIGH && digitalRead(ss5)==HIGH ) && ( digitalRead(ss7)==HIGH && digitalRead(ss8)==HIGH )&& ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) ){

  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80);
 if(replaystage==0){
  path[pathLength]='L';
  pathLength++;
  if(path[pathLength-2]=='B'){
  //Path reducing algorithm, more on it below.
  shortPath();
    }}
    //Functions are described below
    leftturn();
  }
  else{
    //The reference point we initialized above
    goto WELCOME;
    }
}

else if((a==HIGH || b==HIGH) && (e==HIGH || d==HIGH) && (h==LOW || g==LOW) && ( distance>12   && digitalRead(switchPin)==LOW && v==0 ) )
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(25);
  if( (digitalRead(ss1)==HIGH && digitalRead(ss2)==HIGH) && ( digitalRead(ss4)==HIGH || digitalRead(ss5)==HIGH ) && ( digitalRead(ss7)==LOW && digitalRead(ss8)==LOW ) && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) ){

  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(90);
  if(replaystage==0){
  path[pathLength]='L';
  pathLength++;
  if(path[pathLength-2]=='B'){
  shortPath();
    }}
  leftturn();
  }
  else{
    goto WELCOME;
    }
}

else if( a==LOW && (g==HIGH || h==HIGH) && (e==HIGH || d==HIGH) && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ))
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(25);

  
  
  if( (digitalRead(ss1)==LOW && digitalRead(ss2)==LOW) && ( digitalRead(ss4)==HIGH && digitalRead(ss5)==HIGH ) && ( digitalRead(ss7)==HIGH || digitalRead(ss8)==HIGH ) && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) ){
  
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80); 
  
  if ( ( digitalRead(ss4)==HIGH || digitalRead(ss5)==HIGH ) && ( digitalRead(ss8)==LOW ) && (digitalRead(ss1)==LOW ) && ( distance>12  && digitalRead(switchPin)==LOW && v==0 )){
if(replaystage==0){
  path[pathLength]='S';
  pathLength++;
  if(path[pathLength-2]=='B'){
  shortPath();
    }}
    straight();
  }

  else if( (digitalRead(ss1)==LOW && digitalRead(ss2)==LOW) && ( digitalRead(ss4)==LOW && digitalRead(ss5)==LOW ) && ( digitalRead(ss7)==LOW && digitalRead(ss8)==LOW ) && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) ) {
if(replaystage==0){
  path[pathLength]='R';
  pathLength++;
  if(path[pathLength-2]=='B'){
  shortPath();
    }}
       rightturn();
    }
  
  }

    else if( (digitalRead(ss1)==HIGH && digitalRead(ss2)==HIGH) && ( digitalRead(ss4)==HIGH && digitalRead(ss5)==HIGH ) && ( digitalRead(ss7)==HIGH && digitalRead(ss8)==HIGH ) && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) ){
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80);
 if(replaystage==0){
  path[pathLength]='L';
  pathLength++;
  if(path[pathLength-2]=='B'){
  shortPath();
    }}
    leftturn();
    }

  else{
    goto WELCOME;
    }
}

else if(a==LOW && b==LOW && c==LOW && d==LOW && e==LOW && f==LOW && g==LOW && h==LOW && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) )
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(25);
  if(a==LOW && b==LOW && c==LOW && d==LOW && e==LOW && f==LOW && g==LOW && h==LOW && ( distance>12  && digitalRead(switchPin)==LOW && v==0 ) ){

  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(70);
if(replaystage==0){
  path[pathLength]='B';
  pathLength++;
}
  turnover();
  }
  else {
    goto WELCOME;
    }
}

else if( (distance<12) && v==0 ){
  v++;
  digitalWrite(lm1,LOW);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,LOW);
  digitalWrite(LED,HIGH);
  replaystage=1;
  path[pathLength]='D';
  delay(5000);
  while(digitalRead(switchPin)==LOW){
    delay(10);
    }
if(digitalRead(switchPin)==HIGH){
  delay(1000);
replay();
}
  
  }



}  


// USAGE OF ALL FUNCTIONS USED ABOVE
void straight()
{
  // Moves the robot straight along the line without being diverted from the disturbances.
  if( digitalRead(ss5)==LOW || digitalRead(ss3)==HIGH ){
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    analogWrite(rm1, 180);
    digitalWrite(rm2, LOW);
    delay(1);
    return;
  }
  if(digitalRead(ss4)==LOW || digitalRead(ss6)==HIGH ){
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
    delay(1);
    analogWrite(lm1, 180);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(1);
    return;
  }
 
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
    delay(1);
    
  }

//Manuevers the rover to turn left and to adjust to the straight line
void leftturn(){
  while(digitalRead(ss1)==LOW){
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, HIGH);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(1);
    }
    while(digitalRead(ss3)==LOW || digitalRead(ss4)==LOW){
    digitalWrite(lm1, LOW);
    analogWrite(lm2, 180);
    analogWrite(rm1, 180);
    digitalWrite(rm2, LOW);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(3);
    }
    if(digitalRead(ss5)==HIGH){
      analogWrite(lm1, 150);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
      analogWrite(rm2, 150);
      delay(2);
      
      digitalWrite(lm1, LOW);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
      digitalWrite(rm2, LOW);
      delay(2);
      }
      
  }


// Turns the rover around and follows the path that it came from
void turnover(){
  while(digitalRead(ss8)==LOW){
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, HIGH);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(1);
    }

    while(digitalRead(ss5)==LOW || digitalRead(ss6)==LOW){
    analogWrite(lm1, 180);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    analogWrite(rm2, 180);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(3);
    }
    if(digitalRead(ss4)==HIGH){
      digitalWrite(lm1, LOW);
      analogWrite(lm2, 150);
      analogWrite(rm1, 150);
      digitalWrite(rm2, LOW);
      delay(2);
      digitalWrite(lm1, LOW);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
      digitalWrite(rm2, LOW);
      delay(3);
      }
      
  }

//Manuevers the rover to turn right and to adjust to the straight line
void rightturn(){
    while(digitalRead(ss8)==LOW){
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, HIGH);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(1);
    }

    while(digitalRead(ss5)==LOW || digitalRead(ss6)==LOW){
    analogWrite(lm1, 180);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    analogWrite(rm2, 180);
    delay(1);
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
    delay(3);
    }
    if(digitalRead(ss4)==HIGH){
      digitalWrite(lm1, LOW);
      analogWrite(lm2, 150);
      analogWrite(rm1, 150);
      digitalWrite(rm2, LOW);
      delay(1);
      digitalWrite(lm1, LOW);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
      digitalWrite(rm2, LOW);
      delay(2);
      }
      
}


//  THE ALGORITHM TO DETERMINE THE SHORTEST POSSIBLE COMBINATION
// The function takes the input of the path travelled by the rover and determines the shortest possible path using the possible combinations
void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  }



  // To manueveur through the calculated shortest combination, the function checks the bot at every turn to travel in the right direction.
  void replay(){
    for(i=0;i<=pathLength;i++)
    {
      Serial.println(path[i]);
    }
   readsensors();
  if(a==LOW && h==LOW && ( d==HIGH || e==HIGH )){
    straight();
  }
  else{
    if(path[readLength]=='D'){
     digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80); 
    digitalWrite(lm1,LOW);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80);
      leftturn();
    }
    if(path[readLength]=='R'){
    digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80); 
  rightturn();
    }
    if(path[readLength]=='S'){
      digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
  delay(80); 
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}


// TO completely stop the moment of the robot.
void endMotion()
{
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
  endMotion();
}

long check_distance()
{
  int i=0;
  //peche :
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
    return distance;
  }



//
