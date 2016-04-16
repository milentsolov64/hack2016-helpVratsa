#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define RST_PIN         48     
#define SS_PIN          49

LiquidCrystal_I2C lcd (0x27,2,1,0,4,5,6,7,3,POSITIVE);

MFRC522 mfrc522(SS_PIN, RST_PIN);

String readRfid;
String okRfid_1="a431ece2";
String okRfid_2="55ae675";
String okRfid_3="8ba88e1";
int lock=26;  

const byte COLS = 4;
const byte ROWS = 4;

char keys [ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rPins[ROWS] = {30, 32, 34, 36};
byte cPins[COLS] = {31, 33, 35, 37};

Keypad kl = Keypad( makeKeymap(keys), rPins, cPins, ROWS, COLS);




void setup() {
    Serial.begin(9600);
    while (!Serial);
    SPI.begin();
    mfrc522.PCD_Init();

    pinMode(lock, OUTPUT);

    lcd.begin(16,2);
    setTime(0,0,0,0,0,0);
}



void dump_byte_array(byte *buffer, byte bufferSize) {
    readRfid="";
    for (byte i = 0; i < bufferSize; i++) {
        readRfid=readRfid + String(buffer[i], HEX);
    }
}


void openLock() {
  digitalWrite(lock, HIGH);
  delay(2000);
  digitalWrite(lock,LOW);
}

void loop() {

  lcd.setBacklight(HIGH);
  
  char keyPressed = kl.getKey();
  if(keyPressed == 'A')digitalWrite(lock, HIGH);
  if(keyPressed == 'B')digitalWrite(lock, LOW);
  
  if ( ! mfrc522.PICC_IsNewCardPresent())
        return;
  if ( ! mfrc522.PICC_ReadCardSerial())
        return;

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(readRfid);

    String pass = "";
    
    if (readRfid==okRfid_1) {
    lcd.setCursor(0,0);
    lcd.print("Hello, Ivo!");
    lcd.setCursor(0,1);
    lcd.print("Enter your pass");
    setTime(0,0,0,0,0,0);
    int vreme = 0;
    int flag = 0;
    pass = "";
    while (vreme < 30 && flag <5){
      vreme = second();
      if(kl.getKey() != NO_KEY && flag < 5){
        pass = pass + kl.getKey();
        flag++;
        
      }
    }
    }
    if (pass = "12345"){
      pass = "";
      lcd.clear();
      lcd.print("Unlocked");
      digitalWrite(lock, HIGH);
      delay(1500);
      digitalWrite(lock, LOW);
      lcd.clear();
      
    }
    
    if (readRfid==okRfid_2) {
    setTime(0,0,0,0,0,0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(second());
    }

    if (readRfid==okRfid_3) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(1);
    }

    if (second() == 30){
    lcd.clear();
    readRfid = "";
    }
    
}
