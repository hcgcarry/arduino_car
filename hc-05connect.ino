
#include <SoftwareSerial.h>   // 引用程式庫




// 定義連接藍牙模組的序列埠
SoftwareSerial BT(11, 12); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數

int motor_right_1 = 4;
int motor_right_2 = 5;
int motor_left_1 = 8;
int motor_left_2 = 9;
int Enable_right = 6;
int Enable_left = 10;
void setup() {
  pinMode(motor_left_1, OUTPUT);
  pinMode(motor_left_2, OUTPUT);
  pinMode(motor_right_1, OUTPUT);
  pinMode(motor_right_2, OUTPUT);
  pinMode(Enable_right, OUTPUT);
  pinMode(Enable_left, OUTPUT);


  Serial.begin(38400);   // 與電腦序列埠連線
  Serial.println("BT is ready!");

  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(9600);
}

void loop() {

  bluetoothRecieve();
}

void bluetoothRecieve() {
  if (BT.available() > 0) {
    unsigned char charReceived = BT.read();
    switch (charReceived) {

      case '1':
        BT.println("straight1");
        Serial.println("straight1");
        goStraight();

        break;
      case '2':
        BT.println("left2");
        Serial.println("left2");
        goLeft();
        break;

      case '3':
        BT.println("right3");
        Serial.println("right3");
        goRight();
        break;
       case '4':
        BT.println("back4");
        Serial.println("back4");
        goBack();
        break;
       case '5':
        BT.println("stop5");
        Serial.println("stop5");
        goStop();
        break;

    }
  }
  BT.flush();
  delay(500);
}



void goLeft() {
analogWrite(Enable_right, 250);
  digitalWrite(motor_right_1, HIGH);
  digitalWrite(motor_right_2, LOW);
  analogWrite(Enable_left, 80);
  digitalWrite(motor_left_1, HIGH);
  digitalWrite(motor_left_2, LOW);

}

void goStraight() {
  analogWrite(Enable_right, 250);
  digitalWrite(motor_right_1, HIGH);
  digitalWrite(motor_right_2, LOW);
  analogWrite(Enable_left, 220);
  digitalWrite(motor_left_1, HIGH);
  digitalWrite(motor_left_2, LOW);

  Serial.println("goStraight");
}

void goRight() {

  analogWrite(Enable_right, 80);
  digitalWrite(motor_right_1, HIGH);
  digitalWrite(motor_right_2, LOW);
  analogWrite(Enable_left, 250);
  digitalWrite(motor_left_1, HIGH);
  digitalWrite(motor_left_2, LOW);
}

void goBack() {
analogWrite(Enable_right, 190);
  digitalWrite(motor_right_1, LOW);
  digitalWrite(motor_right_2, HIGH);
  analogWrite(Enable_left, 250);
  digitalWrite(motor_left_1, LOW);
  digitalWrite(motor_left_2, HIGH);
 
}
void goStop() {
analogWrite(Enable_right, 250);
  digitalWrite(motor_right_1, LOW);
  digitalWrite(motor_right_2, LOW);
  analogWrite(Enable_left, 250);
  digitalWrite(motor_left_1, LOW);
  digitalWrite(motor_left_2, LOW);

}

void commadMode() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();

    BT.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();


    Serial.print(val);
  }
}
