#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
const int trigPin = 2;
const int echoPin = 3;
int green=5;
int yellow=6;
int red=7;
int len=100;
#define speaker A0
double c=len-(len/3); // green lower limit
double b=len-((len*2)/3);// red lower limit 
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode (green,OUTPUT);
pinMode (yellow,OUTPUT);
pinMode (red,OUTPUT);
pinMode (speaker,OUTPUT);
digitalWrite(green, LOW);
digitalWrite(yellow, LOW);
digitalWrite(red, LOW);
digitalWrite(speaker, LOW);
}
void loop() {
// put your main code here, to run repeatedly:
long duration, inches, cm;
pinMode(trigPin,OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
cm = microsecondsToCentimeters(duration);
Serial.print(cm); Serial.print(" cm"); Serial.println(); delay(100);
//reach the upper limit
if(cm == 4){
digitalWrite(green, LOW);
digitalWrite(yellow, LOW);
digitalWrite(red, LOW);
tone(speaker, NOTE_CS7, 3000);
delay(2000);
noTone(speaker);
  } 
  else {
if ((cm < b)&& (cm>4)){  // reach green limit 
digitalWrite (green,HIGH);
digitalWrite (yellow,LOW); 
digitalWrite (red,LOW); 
delay(500);
tone(speaker, NOTE_CS8, 2000);
delay(2000);
noTone(speaker);
}
else if((cm>=b)&&(cm<c)){ // reach yellow limit 
digitalWrite (green,LOW);
digitalWrite (yellow,HIGH); 
digitalWrite (red,LOW); 
tone(speaker, NOTE_DS8, 2000);
delay(2000);
noTone(speaker);
  }
else if ((cm>=c)&&(cm <=len)){ // reach red limit
  digitalWrite (green,LOW);
  digitalWrite (yellow,LOW); 
  digitalWrite (red,HIGH);  
  tone(speaker, NOTE_D8, 2000);
  delay(2000);
  noTone(speaker);
  }
  }
}
long microsecondsToInches(long microseconds) {
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
return (microseconds / 74) / 2;
}
long microsecondsToCentimeters(long microseconds) {
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return (microseconds / 29) / 2;
}
