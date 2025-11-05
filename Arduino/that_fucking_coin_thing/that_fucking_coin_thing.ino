void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10000);
}

int coin_1 = 0;
int coin_2 = 0;
int coin_3 = 0;
int coin_4 = 0;
int coin_5 = 0;

int data_displayed = 0;

void set_coins(int v1, int v2, int v3, int v4, int v5) {
  coin_1 = v1;
  coin_2 = v2;
  coin_3 = v3;
  coin_4 = v4;
  coin_5 = v5;
}

void eval_coin() {

  int coin_uses = 0;
  int value_two = 0;

  for (int value = 0; value < 100; value++) {

    value_two = value;

    while (value_two - coin_5 > 0) {
      coin_uses = coin_uses + 1;
      value_two = value_two - coin_5;
    }

    while (value_two - coin_4 > 0) {
      coin_uses = coin_uses + 1;
      value_two = value_two - coin_4;
    }

    while (value_two - coin_3 > 0) {
      coin_uses = coin_uses + 1;
      value_two = value_two - coin_3;
    }

    while (value_two - coin_2 > 0) {
      coin_uses = coin_uses + 1;
      value_two = value_two - coin_2;
    }

    while (value_two - coin_1 > 0) {
      coin_uses = coin_uses + 1;
      value_two = value_two - coin_1;
    }

  }
if(data_displayed == 100000){
  delay(100000);
  data_displayed = 0;
}
  Serial.println(coin_uses);
data_displayed = data_displayed + 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int a = 1; a <= 100; a = a + 1) {
    for (int b = 1; b <= a; b = b + 1) {
      for (int c = 1; c <= b; c = c + 1) {
        for (int d = 1; d <= c; d = d + 1) {
          set_coins(1, d, c, b, a);
          eval_coin();
        }
      }
    }
  }
  Serial.println("done");
delay(1000000);
}
