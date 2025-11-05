
int top = 100;//the top wall as an int
int bottom = -100;//the bottom wall as an int
int ALG;//the algorithem number in int form
int chancea[5] = {50,50,50};//the actual brain that holds the decitions for the addition
int chanceb[5] = {50,50,50};//the actual brain that holds the decitions for the subtraction
int chancec[5] = {50,50,50};//the actual brain that holds the decitions for the multiplication
int AI = 0;
int scorenew;
int scoreold;
int path;
bool correct;
bool Break;
int i;
int x;
bool FAIL;
int graph;
int t;
bool swap;
void setup() {
  Serial.println(0);
Serial.begin(2000000);
randomSeed(analogRead(0)+ analogRead(1));
  for (i = 0; i < 1000; i = i + 1){
delay(1);
 Serial.println("0");
  }
  
}

void loop() {
if(Break != 1){
  if(random(0,100) <= chancea[ALG]){
  AI = AI + 1;
  Break = 1;
  path = 1;
  }
}
if(Break != 1){
  if(random(0,100) <= chanceb[ALG]){
  AI = AI - 1;
  Break = 1;
  path = 2;
  }
}
if(Break != 1){
  if(random(0,100) <= chancec[ALG]){
  AI = -AI;
  Break = 1;
  path = 3;
  }
}
Break = 0;
//))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
scoreold = scorenew;
scorenew = abs(AI);
if(scorenew < scoreold){
  correct = 1;
}else{
  correct = 0;
}
if(correct == 1){
  if(path == 1){
    chancea[ALG] = chancea[ALG] + 2;
     chanceb[ALG] = chanceb[ALG] - 1;
      chancec[ALG] = chancec[ALG] - 1;
  }
  if(path == 2){
     chancea[ALG] = chancea[ALG] - 1;
     chanceb[ALG] = chanceb[ALG] + 2;
      chancec[ALG] = chancec[ALG] - 1;
  }
  if(path == 3){
  chancea[ALG] = chancea[ALG] - 1;
     chanceb[ALG] = chanceb[ALG] - 1;
      chancec[ALG] = chancec[ALG] + 2;
  }
}
if(AI > 0){
  ALG = 0;
}else if(AI < 0){
  ALG = 1;
}else{
  ALG = 2;
}
//))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
delayMicroseconds(20);
  Serial.print("\t");
  Serial.print(100);
    Serial.print("\t");
      Serial.print(AI);
        Serial.print("\t");
          Serial.println(-100);
}
