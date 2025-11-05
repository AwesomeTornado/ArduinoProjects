String INPUt = "w";
int ending = 10;
int input = 9;
int output;
bool correct;
int i;
int ram;
bool Break;
bool flip;
int generation;
int prelearn = 10000;
int scuffed[500];
int select[6];
int loops = 10;
int graph;
String path[100];
void setup() {
Serial.begin(2000000);
randomSeed(analogRead(0));
}
void add(){
  if(Break != 1){
    if(path[generation] == 1){
  input = input + 1;
  Break = 1;
    }
  }
}
void subtract(){
  if(Break != 1){
    if(path[generation] == "2"){
  input = input - 1;
  Break = 1;
    }
  }
}
void multiply(){
  if(Break != 1){
    if(path[generation] == "3"){
  input = input * 2;
  Break = 1;
    }
  }
}
void divide(){
  if(Break != 1){
    if(path[generation] == "4"){
  input = input / 2;
  Break = 1;
    }
  }
}
void Null(){
  if(Break != 1){
    if(path[generation] == "5"){
  Break = 1;
    }
  }
}
void loop() {
 //:::::::::::::::::::::::::::::::::::::::::::::::::
 retry:
 ram = input;
 if(path[0] == "1"){
  generation = 1;
 for(i = loops;i >= 1;i = i - 1){

  add();

  subtract();

  multiply();

  divide();

  Null();

  Break = 0;
  generation = generation + 1;
 }
 }else{
  path[0] = 1;
  path[1] = random(1,5);
  path[2] = random(1,5);
  path[3] = random(1,5);
  path[4] = random(1,5);
  path[5] = random(1,5);
  path[6] = random(1,5);
  path[7] = random(1,5);
  path[8] = random(1,5);
  path[9] = random(1,5);
  path[10] = random(1,5);
  goto retry;
 }
 //:::::::::::::::::::::::::::::::::::::::::::::::::
if(input == ((((ram * 8) + 1) / 2) - 1)){
  correct = 1;
}else{
  correct = 0;
}
if(correct == 1){
 path[0] = 1;
 graph = graph + 1;
}else{
  path[0] = "0";
  graph = graph - 1;
}
Serial.println(graph);
}
