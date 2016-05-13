    int l,u;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
    pinMode(A0, INPUT);
    //pinMode(A1,  INPUT);
    pinMode(13,OUTPUT);

   l=analogRead(A0);
   //u=analogRead(A1);
}

void loop() {
  //Serial.println(l);
  //Serial.println(u);
  // put your main code here, to run repeatedly:
if(l==200){digitalWrite(13,HIGH);}
if(l==100){digitalWrite(13, LOW);}
}
