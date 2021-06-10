/*
  Melody
 */
#define NOTE_C3  131
#define NOTE_D3  147
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

// notes in the melody:
int melody[] = {
  NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, 
  NOTE_A3, NOTE_B3, NOTE_C4, NOTE_A3, NOTE_G3, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 2, 2, 2, 4, 4, 4, 4, 2, 4
};


int latchPin = 8;
int clockPin = 12;
int dataPin =11;

int button = 2;
int buttonread;
byte buttonPrev = 1, buttonPresent = 1; 
int buttonflag=0;

int thisnote=-1,noteDuration=0;
long presentTime=0,previousTime=0,pauseBetweenNote=0;

byte colDataMatrix[8] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};//這掃描

byte rowDataMatrix[8] = {
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
};//選圖案 心

byte rowDataMatrix2[8] = {
  B01111110,
  B01100011,
  B01100000,
  B00110000,
  B00011000,
  B00011000,
  B00000000,
  B00011000
};//選圖案 ?


void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(button, INPUT_PULLUP);
}

void checktoplay(){
  presentTime=millis();
  if(presentTime-previousTime>=pauseBetweenNote){
    thisnote+=1;
  if(thisnote>=10){
  thisnote=-1;
   pauseBetweenNote=100;
    previousTime=millis();
  }
    else{
      noteDuration=500/noteDurations[thisnote];
      tone(9,melody[thisnote], noteDuration);
      pauseBetweenNote= noteDuration*1.2;
       previousTime=millis();
    }
}
}

void loop()
{ 
  buttonPresent = digitalRead(button);
  if(buttonPresent == 0 && buttonPrev ==1)
  {
  	buttonflag = !buttonflag;
  }
  //buttonread=digitalRead(button);
  //if(buttonread==0){buttonflag=!buttonflag;}
  
  if(buttonflag==1){
  for(int i = 0; i < 8; i++){
   digitalWrite(latchPin,LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
   shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
   digitalWrite(latchPin, HIGH);
   checktoplay();
   delay(1);
   }
  }
  else if(buttonflag==0){
  for(int i = 0; i < 8; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix2[i]);
      digitalWrite(latchPin, HIGH);
      checktoplay();
      delay(1);
    }
  }
  
  buttonPrev = buttonPresent;
}

