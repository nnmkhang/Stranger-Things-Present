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
String dispWord[16]; // creates an array for the display word 
int speeds[10] = {100,200,300,400,500,600,700,800,900,900}; // have to use this since the pots readings are skewed 
int check; 
int row;
int col;





void setup() 
{
  Serial.begin(9600);
  lcd.begin(16,2);
  
  //This is the begning screen 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Merry Christmas");
  lcd.setCursor(0,1);
  lcd.print("Fran! KN-2017");
  pinMode(12,INPUT_PULLUP); // for button 1     (buttons are not using resistors, pullup uses arduino's
  pinMode(13,INPUT_PULLUP); // for button 2                      internal resistance)
  pinMode(2, OUTPUT); // test
}

void loop()
{
  
  //while loop with true( button1 pressed)
  //in while loop read 
  // while loop false when (button 2 pressed (word is done typing))

 
  but1 = digitalRead(12);
  but2 = digitalRead(13);
  
  //Serial.println(but1);
  int xpos = 0;
  int wordpos = 0; 
  
  potval = analogRead(A0);
  spd = potval;
  
  if(but2 == 0)
  {
    delay(5);
    if(but2 ==0)
    {
      //delay(500);
      title();
  }
}
 
  if ( but1 == 0) 
  {  
    delay(5);
    if( but1 ==0)
    {
      
    
      wordClear();
      delay(500);
      lcd.clear();
      lcd.home();
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
        dispWord[wordpos] = getChar(potval);
        lcd.print(getChar(potval));
        if(but1 == 0)
      {
        delay(500);
        xpos+=1;
        wordpos +=1;
      }
    }
  }
 }
  
  delay(100);
  // use toCharArray
  for(int i = 0; i < 16; i++)
    {
      Serial.print(dispWord[i]);
    }
printChar('Z');
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
}
String getChar(int input)
{
  String alphabet[28] ={"_","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Z"};
  return alphabet[input -1];
}
void wordClear()
{
    for(int i = 0; i < 16; i++)
    {
      dispWord[i] = "\0";
    }
}



void printChar(char letter) // this function takes in a letter and flashes the led
{
  // the mutiplex used is a 5x5  = 25 leds ( a - y ) + a single LED for the letter z 
  // if the char is Z , Print right away 
  if ( letter == "Z") 
  {
    digitalWrite(2,1);
    delay(spd);
    digitalWrite(2,0);
    delay(spd);
  }
  else
  {
     letter = letter - 65; // converts it from 65 to 0 ( the first char is 0 = A 
     row = letter / 5; // gets the row
     col = letter % 5;// gets the col

//     digitalWrite( row 
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



