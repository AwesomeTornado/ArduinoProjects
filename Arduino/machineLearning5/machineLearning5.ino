
int top = 100;//the top wall as an int
int bottom = -100;//the bottom wall as an int
int ALG;//the algorithem number in int form
byte chancea[] = {};//the actual brain that holds the decitions for the addition
byte chanceb[] = {};//the actual brain that holds the decitions for the subtraction
byte chancec[] = {};//the actual brain that holds the decitions for the multiplication
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
Serial.begin(9600);
randomSeed(analogRead(0)+ analogRead(1));
  for (i = 0; i < 1000; i = i + 1){
delay(1);
 Serial.println("0");
  }
  
}

void loop() {
  //----------
  delayMicroseconds(20);
  if(chancea[ALG] == 0){
    delayMicroseconds(20);
    chancea[ALG] = 50;
    Serial.println(-100);
    Serial.println(100);
    Serial.println(-100);
       delayMicroseconds(20);
  }
  if(chanceb[ALG] == '\0'){
    delayMicroseconds(20);
    chanceb[ALG] = 50;
      delayMicroseconds(20);
  }
  if(chancec[ALG] == '\0'){
    delayMicroseconds(20);
    chancec[ALG] = 50;
       delayMicroseconds(20);
  }
  //----------
  delayMicroseconds(20);
  if(swap == 1){
if(Break != 1){
   
if(random(0,100) < chancea[ALG]){
   delayMicroseconds(40);
  if(AI < 98){
  
  AI = AI + 1;
   delayMicroseconds(40);
path = 1;

  Break = 1;
  }
  }
}
delayMicroseconds(20);
//----------
if(Break != 1){
 
if(random(0,100) < chanceb[ALG]){
 delayMicroseconds(40);
  if(AI > -98){
    delayMicroseconds(40);
    AI = AI - 1;
path = 2;
  Break = 1;
  }
  }
}

//----------
if(Break != 1){
 delayMicroseconds(40);
if(random(0,100) < chancec[ALG]){
 delayMicroseconds(40);
  if(abs(AI) < 49){
    
    AI = AI * 2;
     delayMicroseconds(40);
path = 3;
 Break = 1;
  }
  }
}
 delayMicroseconds(20);
//----------
if(Break != 1){
  
   if(abs(AI) > 2){
  FAIL = 1;
   }
}else{
 delayMicroseconds(40);
  FAIL = 0;
}
  }else{
      //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INVERTED SECTION DOWN BELOW
delayMicroseconds(20);
//----------
if(Break != 1){
  
if(random(0,100) < chanceb[ALG]){
  if(AI > -98){
    
    AI = AI - 1;
     
path = 2;
  delayMicroseconds(40);
  Break = 1;
  }
  }
}
 delayMicroseconds(20);
    if(Break != 1){
       delayMicroseconds(40);
if(random(0,100) < chancea[ALG]){
  if(AI < 98){
    
  AI = AI + 1;
   delayMicroseconds(40);
path = 1;
 delayMicroseconds(40);
  Break = 1;
  }
  }
}
delayMicroseconds(20);
//----------
if(Break != 1){
if(random(0,100) < chancec[ALG]){
  if(abs(AI) < 49){
    
    AI = AI * 2;
     delayMicroseconds(40);
path = 3;
  Break = 1;
  }
  }
}
delayMicroseconds(20);
  }
 delayMicroseconds(20);
//----------
if(Break != 1){
  FAIL = 1;
}else{
  delayMicroseconds(20);
  FAIL = 0;
}
delayMicroseconds(20);
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  if(FAIL == 0){
    delayMicroseconds(20);
if(scoreold < scorenew){
  correct = 0;
 delayMicroseconds(20);
  graph = graph - 1;
}else{
   delayMicroseconds(20);
  correct = 1;
   delayMicroseconds(40);
  graph = graph + 1;
}
  }else{
    correct = 0;
     delayMicroseconds(20);
  }
  delayMicroseconds(20);
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  if(correct == 1){
    if(path == 1){
      chancea[ALG] = chancea[ALG] + 4;
    delayMicroseconds(20);
      chanceb[ALG] = chancea[ALG] - 2;
      delayMicroseconds(20);
      chancec[ALG] = chancea[ALG] - 2;
    }else if(path == 2){
      chancea[ALG] = chancea[ALG] - 2;
      delayMicroseconds(20);
      chanceb[ALG] = chancea[ALG] + 4;
    delayMicroseconds(20);
      chancec[ALG] = chancea[ALG] - 2;
    }else if(path == 3){
      chancea[ALG] = chancea[ALG] - 2;
 delayMicroseconds(20);
      chanceb[ALG] = chancea[ALG] - 2;
    delayMicroseconds(20);
      chancec[ALG] = chancea[ALG] + 4;
    }else{}
  }
   delayMicroseconds(30);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ALG = ((top*100) - (AI*100)) + abs(bottom + AI);//A = (B * 100) + C
 // if((top - AI) > abs(bottom - AI)){
 //  ALG = 1;
//}else{
 ///   ALG = 0;
 // }
 delayMicroseconds(40);
scoreold = scorenew;
delayMicroseconds(20);
scorenew = abs((top - AI) - abs(bottom - AI));
delayMicroseconds(200);
 Break = 0;
  path = 0;
delayMicroseconds(20);
  swap = !swap;
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
delayMicroseconds(20);
  Serial.print("\t");
  Serial.print(100);
    Serial.print("\t");
      Serial.print(AI);
        Serial.print("\t");
          Serial.println(-100);

}
