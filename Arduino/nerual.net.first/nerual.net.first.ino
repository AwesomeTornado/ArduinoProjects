String INPUt = "w";
int ending = 10;
int input = -5;
int output;
int zero = 50;
int one = 50;
bool remember;
int ram;
bool Break;
bool flip;
int generation;
int prelearn = 1000;
void setup() {
Serial.begin(250000);
randomSeed(analogRead(0));
if(32 % 2){
  
}
}

void loop() {
  //***********************************************************************************************
   
  if(generation > prelearn){
    generation = generation + 1;
while(Break != 1){
  INPUt = Serial.readStringUntil(ending);
 if(INPUt.toInt() == 2){
 Break = 1;
 input = 1;
 break;
 }
 if(INPUt.toInt() == 1){
 Break = 1;
 input = 0;
 break;
 }
}
//***********************************************************************************************

 }else{
    generation = generation + 1;
 if(flip == 1){
  flip = !flip;
  Break = 1;
 input = 0;
 }else{
  flip = !flip;
  Break = 1;
 input = 1;
 }
 }
//***********************************************************************************************
//***********************************************************************************************
if(input == 1){
  remember = 1;
  ram = random(0,100);
  if(ram < one){//increase "one" to make it more likley to get the right awenswer
    output = 0;
  }else{//this is the wrong awenswer section, but both parts need code
    output = 1;
  }
}
//***********************************************************************************************
//***********************************************************************************************
if(input == 0){
  remember = 0;
  ram = random(0,100);
  if(ram < zero){//increase "zero" to make it more likley to get the right awenswer
    output = 1;
  }else{//this is the wrong awenswer section, but both parts need code
    output = 0;
  }
}
//***********************************************************************************************
//***********************************************************************************************
if(remember == 0){
  if(output == 1){
    if(ram < one){
      one = one + 1;
    }else{
      one = one - 1;
    }
  }else{
    if(ram < one){
      one = one - 1;
    }else{
      one = one + 1;
    }
  }
}else{
  if(output == 0){
    if(ram < zero){
      zero = zero + 1;
    }else{
      zero = zero - 1;
    }
  }else{
    if(ram < zero){
      zero = zero - 1;
    }else{
      zero = zero + 1;
    }
  }
}
//***********************************************************************************************
Serial.print(input);
Serial.print(" becomes ");
Serial.println(output);
input = -5;
Break = 0;
}
