#include <DFRobot_TFmini.h>
#include <SoftwareSerial.h>
#define BUZ 11
#define BT_RXD 5
#define BT_TXD 4
SoftwareSerial mySerial(8, 7); // RX, TX
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

DFRobot_TFmini  TFmini;
int buzzer = 11;
uint16_t distance, strength;   // 거리와 강도를 담는 변수

void setup() {
  
  Serial.begin(9600);
  bluetooth.begin(9600);
  TFmini.begin(mySerial);
  pinMode(BUZ, OUTPUT);
  pinMode(2, OUTPUT);
  

}

void loop() {
   if(bluetooth.available()){
    Serial.write(bluetooth.read());
  }
  if (Serial.available()){
    bluetooth.write(Serial.read());
  }
  if (TFmini.measure()) {                  // 거리와 신호의 강도를 측정합니다. 성공하면 을 반환하여 if문이 작동합니다.
    distance = TFmini.getDistance();       // 거리값을 cm단위로 불러옵니다.
    strength = TFmini.getStrength();       // 신호의 강도를 불러옵니다. 측정 대상이 넓으면 강도가 커집니다.
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println("cm");
    Serial.print("Strength = ");
    Serial.println(strength);
    bluetooth.write(distance);
    if (distance < 50){
      digitalWrite(buzzer, HIGH);
      digitalWrite(2, HIGH);
    }else{
      digitalWrite(buzzer, LOW);
      digitalWrite(2, LOW);
    }
    
  }
  delay(1000);
}
