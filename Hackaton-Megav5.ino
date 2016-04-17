#include <Servo.h>

#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define RST_PIN         48     
#define SS_PIN          49
Servo myservo;

String passIvo = "12346A";
String lockIvo = "12346B";
String pass;
int flag = 0;

int x = 0;
int y = 0;

LiquidCrystal_I2C lcd (0x27,2,1,0,4,5,6,7,3,POSITIVE);

MFRC522 mfrc522(SS_PIN, RST_PIN);

String readRfid;
String okRfid_1="a431ece2";
String okRfid_2="55ae675";
String okRfid_3="8ba88e1";

int lock=26;
int unlock = 27;  


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
    pinMode(unlock,  OUTPUT);



    lcd.begin(16,2);
    Wire.begin(); 

    myservo.attach(28);
}



void dump_byte_array(byte *buffer, byte bufferSize) {
    readRfid="";
    for (byte i = 0; i < bufferSize; i++) {
        readRfid=readRfid + String(buffer[i], HEX);
    }
}
void loop() {
  lcd.setBacklight(HIGH);
  
   
  
  if ( ! mfrc522.PICC_IsNewCardPresent())
        return;
  if ( ! mfrc522.PICC_ReadCardSerial())
        return;

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  
for(int i = 0; i < 6; i){
  char pKey = kl.getKey();
  if (pKey != NO_KEY){
    i++;
    pass = pass + pKey;
    Serial.println(pass);
    
  }
  if(readRfid == okRfid_1) {
    lcd.setCursor(0,0);
    lcd.print("Hello, Ivo!");
  }
}



  
  if (readRfid==okRfid_1 && pass == passIvo) {
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Unlocked");
      myservo.write(0);
      delay(2000);
      lcd.clear();
          
      }

  if (readRfid==okRfid_1 && pass == lockIvo) {
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Locked");
      myservo.write(120);
      delay(2000);
      lcd.clear();
      }


  if (readRfid != okRfid_1 && (pass == passIvo || pass == lockIvo) && pass != "") {
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Don`t match");
      delay(1000);
      lcd.clear();
          
      }


  if (readRfid==okRfid_1) {
    if(pass != lockIvo){
      if(pass != passIvo){
        lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Don`t Match");
      delay(1000);
      lcd.clear();
      }
    }
    
    
          
      }
     
  pass = "";
  lcd.clear();

  
      
}
