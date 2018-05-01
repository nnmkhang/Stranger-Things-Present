//make function that reads the potentiometer and then creates an array of Letters [H,E,L,L,O] 
// to make the led light up read the array and make a function that goes from Letter to LED 
// A = Led 1 B =Led 2.. etc.

#include <LiquidCrystal_I2C.h> // Using version 1.35
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Variables 
int potval; //value from pot
int but1; //button 1      "ok"                  the buttons are normally HIGH
int but2; //button 2      "back"
int but3; //button 3      "speed" 
int spd = 500; // the speed of the lights switching 
String dispWord; // creates an array for the display word 
int speeds[10] = {100,200,300,400,500,600,700,800,900,900}; // have to use this since the pots readings are skewed 
int check; 
int row;
int col;
// pins 0 and 1 cannot be used as inputs since they are used for serial input 
int rows[5] ={5,6,7,8,9}; // all rows will be set to 1 except, but the one we want to turn on will be 0
int cols[5] ={0,1,2,3,4};// all cols will be 0 except for the one we want to turn on which will be 1 
String current;
int xpos;
int wordpos;
int xypos;
  




void setup() 
{
  //Serial.begin(9600);
  lcd.begin(16,2);
  ledReset();
  //This is the begning screen 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Merry Christmas");
  lcd.setCursor(0,1);
  lcd.print("Fran! KN-2017");
  pinMode(12,INPUT_PULLUP); // for button 1     (buttons are not using resistors, pullup uses arduino's
  pinMode(13,INPUT_PULLUP); // for button 2                      internal resistance)
  for ( int i =0; i <=9; i++)
  {
    pinMode(i,OUTPUT);//sets pins 0 to 9 as outputs 
  }
}

void loop()
{
  
  //while loop with true( button1 pressed)
  //in while loop read 
  // while loop false when (button 2 pressed (word is done typing))

 
  but1 = digitalRead(12);
  but2 = digitalRead(13);
  
  //Serial.println(but1);

  
  potval = analogRead(A0);
  spd = potval;
  
  if(but2 == 0)
  {
    delay(5);
    if(but2 ==0)
    {
      delay(500);
      title();
    }
  }
 
  if ( but1 == 0) 
  {  
    delay(5);
    if( but1 ==0)
    {
      
      ledReset();
      //wordClear();
      delay(500);
      lcd.clear();
      lcd.home();
      wordpos = 0;
      xpos=0;
      // enter write mode 
      while(but2 == 1)//while back is not pressed 
      {
        but1 = digitalRead(12);
        but2 = digitalRead(13);
        potval = analogRead(A0);
        potval = potval*28/1023.0;
        Serial.print(but1);
        delay(1);
        lcd.setCursor(xpos,0);
        current = getChar(potval);
        lcd.print(getChar(potval));
        if(but1 == 0)
      {
        delay(500);
        dispWord +=current;
        xpos+=1;
        wordpos +=1;
      }
    }
    lcd.setCursor(xpos,0);
    lcd.print(".");
  }
 }
  
  delay(300);
  char  ledWord[wordpos+1];
  //Serial.print(dispWord);
  
  dispWord.toCharArray(ledWord,wordpos+1);
  for(int i = 0; i<wordpos; i++)
  {
   //Serial.println(ledWord[i]);
   printChar(ledWord[i]);    
  }

}

//_______________________________________ FUNCTIONS ________________________________________
void title()
{
  lcd.clear();
  //This is the begning screen 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Merry Christmas"); 
  lcd.setCursor(0,1);
  lcd.print("Fran! KN-2017"); 
  spd = 500; // reset to begining speed 
  // print out merry christmas 
}
String getChar(int input)
{
  String alphabet[28] ={"_","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Z"};
  return alphabet[input -1];
}
void wordClear()
{
    dispWord = "";
}



void printChar(char letter) // this function takes in a letter and flashes the led
{
  // the mutiplex used is a 5x5  = 25 leds ( a - y ) + a single LED for the letter z 
  // if the char is Z , Print right away 
  if ( letter == 'Z') 
  {
    for(int i=0; i<=4; i++)
    {
    digitalWrite(i,1);
    digitalWrite(i+5,0);
    delay(spd);
    digitalWrite(i,0);
    digitalWrite(i+5,1);
    delay(spd);
    }
  }
  else
  {
     xypos = letter - 65; // converts it from 65 to 0 ( the first char is 0 = A 
     row = xypos / 5;     // gets the row
     col = (xypos % 5) +5;     // gets the col
     
    Serial.println(xypos);
    digitalWrite(row, 0);
    digitalWrite(col,1);
    delay(spd);
    digitalWrite(row,1);
    digitalWrite(col,0);
    delay(spd);
    ledReset();
  }
  
}
/*
   if(but3==0)
  {
    lcd.clear();
    lcd.home();
    lcd.print("Delay in mili-");
    lcd.setCursor(0,1);
    lcd.print("seconds: ");
    lcd.setCursor(9,1);
    while(but2==1)
    {
      but2 = digitalRead(12);
      potval = analogRead(A0);
      potval = potval*10/1023.0;
      lcd.print(speeds[potval]); 
      lcd.setCursor(9,1);
      delay(1);
      spd = speeds[potval];
    }
  }
 */

void ledReset() // Resets all rows/cols of the LED'S
{
  for(int i = 0; i<=4; i++)
  {
    digitalWrite(i,0);// off will be 0 
    digitalWrite((i+5),1); // off will be 1 
  }
}

