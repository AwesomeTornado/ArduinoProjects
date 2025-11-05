String INPUt = "w";
int ending = 10;
int input = -5;
int output;
bool correct;
int ram;
bool Break;
bool flip;
int generation;
int prelearn = 10000;
int scuffed[500];
int select[6];
int path[6];
int loops;
int graph;
void setup() {
Serial.begin(2000000);
randomSeed(analogRead(0));
}

void loop() {
  error:
 delayMicroseconds(1);
  /*
  //***********************************************************************************************
  if(generation > prelearn){
    generation = generation + 1;
while(input == 0){
  INPUt = Serial.readStringUntil(ending);
input = INPUt.toInt();
}
//***********************************************************************************************
 }else{
  
 }
 */
   generation = generation + 1;
   delayMicroseconds(1);
//input = random(-5,5);
input = 20;
delayMicroseconds(1);
 ram = input;
delayMicroseconds(1);
//***********************************************************************************************
//***********************************************************************************************
if(scuffed[abs(input)] == 0){
delayMicroseconds(1);
//  scuffed[abs(input)] = random(0,10);
scuffed[abs(input)] = 1;
delayMicroseconds(1);
}
loops = scuffed[abs(input)];
delayMicroseconds(1);
if(loops > 501){
 delayMicroseconds(1);
  goto error;
}
while(loops > 0){
  if(random(0,100) < select[0]){
     if(Break == 0){
  
  delayMicroseconds(1);
    path[0] = 1;
    input = input + 1;
    Break = 1;
  }
  }
  if(random(0,100) < select[1]){
     if(Break == 0){
 
    delayMicroseconds(1);
     path[1] = 1;
     input = input - 1;
     Break = 1;
  }
  }
  if(random(0,100) < select[2]){
     if(Break == 0){
  
   delayMicroseconds(1);
     path[2] = 1;
     if(input < 1000000){
      input = input * 2;
      Break = 1;
     }
     }
     delayMicroseconds(1);
  }
 delayMicroseconds(1);
  loops = loops - 1;
delayMicroseconds(1);

Break = 0;
}
//***********************************************************************************************
//***********************************************************************************************
Break = 0;
if(input == ram*2){
  delayMicroseconds(1);
  correct = 1;
}else{
  delayMicroseconds(1);
  correct = 0;
}
//***********************************************************************************************
delayMicroseconds(1);
/*if(correct == 0){
   scuffed[ram] = 0;
  delayMicroseconds(1);
if(path[0] == 1){
  select[0] = select[0] - 1;
}else{
  select[0] = select[0] + 25;
}
delayMicroseconds(1);
if(path[1] == 1){
  select[1] = select[1] - 1;
}else{
  select[1] = select[1] + 25;
}
delayMicroseconds(1);
if(path[2] == 1){
  select[2] = select[2] - 1;
}else{
  select[2] = select[2] + 25;
}
}else{
 // scuffed[ram] = 0;
  }
  */
  if(correct == 1){
  delayMicroseconds(1);
if(path[0] == 1){
  select[0] = select[0] + 5;
}else{
  select[0] = select[0] - 1;
}
delayMicroseconds(1);
if(path[1] == 1){
  select[1] = select[1] + 5;
}else{
  select[1] = select[1] - 1;
}
delayMicroseconds(1);
if(path[2] == 1){
  select[2] = select[2] + 5;
}else{
  select[2] = select[2] - 1;
}
}else{
  scuffed[ram] = 0;
  }
  delayMicroseconds(1);
if(correct == 1){
  graph = graph + 1;
  delayMicroseconds(1);
}else{
   graph = graph - 1;
   delayMicroseconds(1);
}
Serial.println(graph);
correct = 0;
input = 0;
ram = 0;
delayMicroseconds(1);
}
