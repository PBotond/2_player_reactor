#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define plA 2 //define button pin 1
#define plB 3 //define button pin 2

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

String country[20] = {"Hungary", "USA", "Albania", "Australia", "Bolivia", "Canada", "Colombia", "Denmark","Iceland","Iran","Iraq","Moldova","New Zealand", "Peru", "Romania", "Slovenia","Uruguay","Vietnam", "Venezuela", "Germany"};
String capital[20] = {"Budapest", "Washington D.C.", "Tirana", "Canberra", "La Paz", "Ottawa", "Bogota", "Copenhagen","Reykjavik","Tehran","Baghdad","Chisinau","Wellington", "Lima", "Bucharest", "Ljubljana","Montevideo","Hanoi", "Caracas", "Berlin"};
int scA = 0; //score of player A
int scB = 0; //score of player B

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  pinMode(plA, INPUT);
  pinMode(plB, INPUT);
  Serial.begin(9600);
}

void loop()
{
  lcd.clear();
  if(play() == 1) //the answer is correct
  {
    unsigned long end = millis() + 3500;
    unsigned long current = millis();
    Serial.println(end);
    while(current <= end)
    {
      if(answer(1) == 1) break;
      current = millis(); 
    }

  }
  else
  {
    int end = millis() + 3000;
    int current = millis();
    while(current <= end)
    {
      if(answer(-1)) break;
      current = millis(); 
    }
  }
}



int play()
{
  int rnd = ran(0,20);
  int rnd3 = rnd;
  lcd.print(country[rnd]); //print out the randomly chosen country

  int rnd2 = ran(0,4);
  if (!rnd2) //print the correct capital
  {
    print_capital(rnd);
    return 1;
  }
  else //print a random capital
  { 
    while((rnd - rnd3) == 0) //making sure we are choosing an incorrect capital
    {
      rnd3 = ran(0,20);
    }
    print_capital(rnd3);
    return 0;
  } 
}



void disp() //write the score to the lcd display for 0.8 seconds
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A: ");
  lcd.setCursor(5,0);
  lcd.print(scA);
  lcd.setCursor(0,1);
  lcd.print("B: ");
  lcd.setCursor(5,1);
  lcd.print(scB);
  delay(800);
}



int ran(int a, int b){
  unsigned int seed = analogRead(0);
  randomSeed(seed);
  return random(a,b);
}

int answer(int a){
  int answer=0;
  if(digitalRead(plA) == HIGH) //player A got the correct answer
  {
    scA+=a;
    disp();
    answer=1;
  }
  else if(digitalRead(plB) == HIGH) //player B got the correct answer
  {
    scB+=a;
    disp();
    answer=1;
  }
  return answer;
}

void print_capital(int n){
    lcd.setCursor(0,1);
    lcd.print(capital[n]);
}