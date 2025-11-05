
int top = 100;//the top wall as an int
int bottom = -100;//the bottom wall as an int
int ALG;//the algorithem number in int form
byte chancea[] = {};//the actual brain that holds the decitions for the addition
byte chanceb[] = {};//the actual brain that holds the decitions for the subtraction
byte chancec[] = {};//the actual brain that holds the decitions for the multiplication
int AI = 5;
int scorenew;
int scoreold;
int path;
bool correct;
bool Break;
int i;
int x;
bool FAIL;
int graph;
bool swap;
void setup() {
  Serial.println(0);
Serial.begin(2000000);
randomSeed(analogRead(0));
  for (i = 0; i < 1000; i = i + 1){
delay(1);
 Serial.println("0");
  }
  
}

void loop() {
  //----------
  if(chancea[ALG] == '\0'){
    chancea[ALG] = 50;
  }
  if(chanceb[ALG] == '\0'){
    chanceb[ALG] = 50;
  }
  if(chancec[ALG] == '\0'){
    chancec[ALG] = 50;
  }
  //----------
  if(swap == 1){
if(Break != 1){
   delayMicroseconds(2);
if(random(0,100) < chancea[ALG]){
   delayMicroseconds(2);
  if(AI < 98){
     delayMicroseconds(2);
  AI = AI + 1;
   delayMicroseconds(2);
path = 1;
 delayMicroseconds(2);
  Break = 1;
  }
  }
}
 delayMicroseconds(2);
//----------
if(Break != 1){
   delayMicroseconds(2);
if(random(0,100) < chanceb[ALG]){
   delayMicroseconds(2);
  if(AI > -98){
     delayMicroseconds(2);
    AI = AI - 1;
path = 2;
  Break = 1;
  }
  }
}
 delayMicroseconds(2);
//----------
if(Break != 1){
   delayMicroseconds(2);
if(random(0,100) < chancec[ALG]){
   delayMicroseconds(2);
  if(abs(AI) < 49){
     delayMicroseconds(2);
    AI = AI * 2;
     delayMicroseconds(2);
path = 3;
  Break = 1;
  }
  }
}
 delayMicroseconds(2);
//----------
if(Break != 1){
   delayMicroseconds(2);
   if(abs(AI) > 2){
  FAIL = 1;
   }
}else{
   delayMicroseconds(2);
  FAIL = 0;
}
  }else{
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INVERTED SECTION DOWN BELOW

//----------
if(Break != 1){
   delayMicroseconds(2);
if(random(0,100) < chanceb[ALG]){
  if(AI > -98){
     delayMicroseconds(2);
    AI = AI - 1;
     delayMicroseconds(2);
path = 2;
 delayMicroseconds(2);
  Break = 1;
  }
  }
}
 delayMicroseconds(2);
    if(Break != 1){
       delayMicroseconds(2);
if(random(0,100) < chancea[ALG]){
  if(AI < 98){
     delayMicroseconds(2);
  AI = AI + 1;
   delayMicroseconds(2);
path = 1;
 delayMicroseconds(2);
  Break = 1;
  }
  }
}
 delayMicroseconds(2);
//----------
if(Break != 1){
if(random(0,100) < chancec[ALG]){
  if(abs(AI) < 49){
     delayMicroseconds(2);
    AI = AI * 2;
     delayMicroseconds(2);
path = 3;
  Break = 1;
  }
  }
}
 delayMicroseconds(2);
//----------
if(Break != 1){
  FAIL = 1;
}else{
  FAIL = 0;
}
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  if(FAIL == 0){
     delayMicroseconds(2);
if(scoreold < scorenew){
  correct = 0;
   delayMicroseconds(2);
  graph = graph - 1;
}else{
   delayMicroseconds(2);
  correct = 1;
   delayMicroseconds(2);
  graph = graph + 1;
}
  }else{
    correct = 0;
     delayMicroseconds(2);
  }
  }
   delayMicroseconds(2);
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  if(correct == 1){
    if(path == 1){
      chancea[ALG] = chancea[ALG] + 2;
       delayMicroseconds(2);
      chanceb[ALG] = chancea[ALG] - 1;
       delayMicroseconds(2);
      chancec[ALG] = chancea[ALG] - 1;
    }else if(path == 2){
      chancea[ALG] = chancea[ALG] - 1;
       delayMicroseconds(2);
      chanceb[ALG] = chancea[ALG] + 2;
       delayMicroseconds(2);
      chancec[ALG] = chancea[ALG] - 1;
    }else if(path == 3){
      chancea[ALG] = chancea[ALG] - 1;
       delayMicroseconds(2);
      chanceb[ALG] = chancea[ALG] - 1;
       delayMicroseconds(2);
      chancec[ALG] = chancea[ALG] + 2;
    }else{}
  }
   delayMicroseconds(2);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ALG = ((top*100) - (AI*100)) + (bottom + AI);//A = (B * 100) + C
   delayMicroseconds(2);
scoreold = scorenew;
 delayMicroseconds(2);
scorenew = abs((top - AI) - (bottom + AI));
 delayMicroseconds(2);
 Break = 0;
  path = 0;
   delayMicroseconds(2);
  swap = !swap;
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   delayMicroseconds(20);
  Serial.println(AI);
   delayMicroseconds(20);
}
