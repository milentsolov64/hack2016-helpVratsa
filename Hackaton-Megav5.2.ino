//#include <Servo.h>
#include <ColorLCDShield.h>
#include <Time.h>
//#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LCDShield clcd;
#define RST_PIN         49     
#define SS_PIN          53
//Servo myservo;

String passIvo = "12346A";
String lockIvo = "12346B";
String passMilen="09831A";
String lockMilen ="09831B";
String passTeo="69696A";
String lockTeo="69696B";
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
  clcd.init(EPSON);
  clcd.contrast(43);
  clcd.clear(WHITE);
    pinMode(A14, OUTPUT);
    //pinMode(A15,  OUTPUT);

analogWrite(A15,0);
//analogWrite(A15,150);

    lcd.begin(16,2);
    Wire.begin(); 

    //myservo.attach(28);
}



void dump_byte_array(byte *buffer, byte bufferSize) {
    readRfid="";
    for (byte i = 0; i < bufferSize; i++) {
        readRfid=readRfid + String(buffer[i], HEX);
    }
}
void loop() {
  lcd.setBacklight(HIGH);
    

  ident();
   analogWrite(A15,0);
  
  
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
  
  //clcd.clear(WHITE);
  if(readRfid == okRfid_1) {
    lcd.setCursor(0,0);    
    lcd.print("Hello, Ivo!");
    //clcd.clear(WHITE);
        lcd.setCursor(0,1);
     lcd.print("             ");
    clcd.setStr("Hello, Ivo!           ", 2,2,RED,WHITE);
  }

  if(readRfid == okRfid_2) {
    lcd.setCursor(0,0);
    
    lcd.print("Hello, Milen!");
        lcd.setCursor(0,1);
        lcd.print("             ");
    //clcd.clear(WHITE);
    clcd.setStr("Hello, Milen!         ", 2,2,RED,WHITE);
  }
  
  if(readRfid == okRfid_3) {
    lcd.setCursor(0,0);
    
    lcd.print("Hello, Teo!");
        lcd.setCursor(0,1);
        lcd.print("             ");
    //clcd.clear(WHITE);
    clcd.setStr("Hello, Teo!         ", 2,2,RED,WHITE);
  }
}



  
  if (readRfid==okRfid_1 && pass == passIvo) {
    analogWrite(A15, 200);
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Unlocked");
      clcd.clear(WHITE);
      clcd.setStr("Unlocked", 2,2,RED,WHITE);
      //myservo.write(0);
      
      delay(2000);
      clcd.clear(WHITE);
      lcd.clear();
          
      }

  if (readRfid==okRfid_1 && pass == lockIvo) {
   analogWrite(A15,100); 
   lcd.clear();
    clcd.clear(WHITE);
    clcd.setStr("Locked", 2,2,RED,WHITE);
    lcd.setCursor(0,0);
      lcd.print("Locked");
     // myservo.write(120);
     
      delay(2000);
      lcd.clear();
      clcd.clear(WHITE);
      
      }


  if (readRfid != okRfid_1 && (pass == passIvo || pass == lockIvo) && pass != "") {
    lcd.clear();
    clcd.clear(WHITE);
    lcd.setCursor(0,0);
      lcd.print("Don`t match");
      clcd.setStr("Don't match", 2,2,RED,WHITE);
      delay(1000);
      lcd.clear();
          
      }


  if (readRfid==okRfid_1) {
    if(pass != lockIvo){
      if(pass != passIvo){
        lcd.clear();
        clcd.clear(WHITE);
    lcd.setCursor(0,0);
      lcd.print("Don`t Match");
      clcd.setStr("Don`t Match", 2,2,RED,WHITE);
      delay(1000);
      clcd.clear(WHITE);
      lcd.clear();
      }
    }
    
    
          
      }





        if (readRfid==okRfid_3 && pass == passTeo) {
    analogWrite(A15, 200);
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Unlocked");
      clcd.clear(WHITE);
      clcd.setStr("Unlocked", 2,2,RED,WHITE);
      //myservo.write(0);
      
      delay(2000);
      clcd.clear(WHITE);
      lcd.clear();
          
      }

  if (readRfid==okRfid_3 && pass == lockTeo) {
   analogWrite(A15,100); 
   lcd.clear();
    clcd.clear(WHITE);
    clcd.setStr("Locked", 2,2,RED,WHITE);
    lcd.setCursor(0,0);
      lcd.print("Locked");
     // myservo.write(120);
     
      delay(2000);
      lcd.clear();
      clcd.clear(WHITE);
      
      }


  if (readRfid != okRfid_3 && (pass == passTeo || pass == lockTeo) && pass != "") {
    lcd.clear();
    clcd.clear(WHITE);
    lcd.setCursor(0,0);
      lcd.print("Don`t match");
      clcd.setStr("Don't match", 2,2,RED,WHITE);
      delay(1000);
      lcd.clear();
          
      }


  if (readRfid==okRfid_3) {
    if(pass != lockTeo){
      if(pass != passTeo){
        lcd.clear();
        clcd.clear(WHITE);
    lcd.setCursor(0,0);
      lcd.print("Don`t Match");
      clcd.setStr("Don`t Match", 2,2,RED,WHITE);
      delay(1000);
      clcd.clear(WHITE);
      lcd.clear();
      }
    }
    
    
          
      }
      
      
      
      
      
      
        if (readRfid==okRfid_2 && pass == passMilen) {
    analogWrite(A15, 200);
    lcd.clear();
    lcd.setCursor(0,0);
      lcd.print("Unlocked");
      clcd.clear(WHITE);
      clcd.setStr("Unlocked", 2,2,RED,WHITE);
      //myservo.write(0);
      
      delay(2000);
      clcd.clear(WHITE);
      lcd.clear();
          
      }

  if (readRfid==okRfid_2 && pass == lockMilen) {
   analogWrite(A15,100); 
   lcd.clear();
    clcd.clear(WHITE);
    clcd.setStr("Locked", 2,2,RED,WHITE);
    lcd.setCursor(0,0);
      lcd.print("Locked");
     // myservo.write(120);
     
      delay(2000);
      lcd.clear();
      clcd.clear(WHITE);
      
      }


  if (readRfid != okRfid_2 && (pass == passMilen || pass == lockMilen) && pass != "") {
    lcd.clear();
    clcd.clear(WHITE);
    lcd.setCursor(0,0);
      lcd.print("Don`t match");
      clcd.setStr("Don't match", 2,2,RED,WHITE);
      delay(1000);
      lcd.clear();
          
      }


  if (readRfid==okRfid_2) {
    if(pass != lockMilen){
      if(pass != passMilen){
        lcd.clear();
        clcd.clear(WHITE);
    lcd.setCursor(0,0);
      lcd.print("Don`t Match");
      clcd.setStr("Don`t Match", 2,2,RED,WHITE);
      delay(1000);
      clcd.clear(WHITE);
      lcd.clear();
      }
    }
    
    
          
      }
     
  pass = "";
  lcd.clear();
  clcd.clear(WHITE);

  
      
}


void ident(){
  clcd.setStr("Security System", 2,6,RED,WHITE);
   clcd.setStr("Leonardo", 40,35,RED,WHITE);
   clcd.setStr("Robotics", 56,35,RED,WHITE);
   //delay(2500);
   //lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("Leonardo");
   lcd.setCursor(4,1);
   lcd.print("Robotics");
   
}


