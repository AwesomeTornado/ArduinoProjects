int a;
bool Switch = 0;
int b;
int z;
int y = 1000;//change this to change the size of the logo. sorry for the lack of comments, but even I dont entirely understand how this works
int x;
int i;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
x = -sqrt(y);
b = (sqrt(y)/2) * (sqrt(y)/2);
a = -(sqrt(b));
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(i);
Serial.println(-i);
i = sqrt(y-sq(x));
x = x + 1;
while(x > sqrt(y)){}
if(a < sqrt(b)/2){
  if(a > -sqrt(b)/2){
    if(Switch == 0){
 Serial.println(sqrt(b)/7);
Serial.println(-(sqrt(b)/7)); 
    }else if(a < (sqrt(b)/7)){
      if(a > -(sqrt(b)/7)){
    Serial.println(sqrt(b)/2);
Serial.println(-(sqrt(b)/2)); 
      }else{
         Serial.println(sqrt(b)/7);
Serial.println(-(sqrt(b)/7)); 
      }
    }else{
       Serial.println(sqrt(b)/7);
Serial.println(-(sqrt(b)/7)); 
    }
  }else{
    Serial.println(0);
Serial.println(0); 
  }
}else if(a < -(sqrt(b)/1.5)){
}else{
  Serial.println(0);
Serial.println(0);  
}
Serial.println(z);
Serial.println(-z);
z = sqrt(b - sq(a));
a = a + 1;
if(a > sqrt(b)){
a = a - 1;
a = -a;
Switch = 1; 
}
}
