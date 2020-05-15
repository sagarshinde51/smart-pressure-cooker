#include<LiquidCrystal.h>
#include<Servo.h>
#include <Keypad.h>

Servo myservo;
int servoPin=11;
LiquidCrystal lcd(A5,A4,A3,A2,13,4);
const int hallPin = 12 ;     
long hallState, hallState_count, count;  
int num;        
volatile int test=0;        
volatile int test_prev = 0;
int buzzer = 10;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte colPins[COLS] = {7,8,9}; //connect to the column pinouts of the keypad

byte rowPins[ROWS] = {3,5,2,6}; //connect to the row pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   pinMode ( hallPin , INPUT ) ;        
   lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Pressor cooker"); 
  lcd.setCursor(0,1);
  lcd.print("with Display");                
  delay(5000);
  lcd.clear();
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  myservo.attach(servoPin);
  myservo.write(140);
}
void loop()
{
    char key = keypad.getKey();
    num = key-'0';
    lcd.setCursor(0,0);
    lcd.print("Enter the Count");
    lcd.setCursor(0,1);
  if (key){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("count till");
    lcd.setCursor(0,1);
    lcd.print(num);
    delay(2000);
    lcd.clear();
    while(1){
    sensor();
    }
  }
}
void sensor(){
  
  hallState = digitalRead (hallPin) ;   
//Serial.println(hallState);
//Serial.print("state");
test=hallState;
if(test == 1 && test_prev==0)
{ 
hallState_count++;
count = hallState_count -1;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("whistles count");
lcd.setCursor(14,0);
lcd.print(count);
 lcd.setCursor(0,1);
lcd.print("count till");
lcd.setCursor(14,1);
lcd.print(num);
delay(4000);
//lcd.clear();
if (count>=3)
{
  lcd.clear();
  tone(buzzer, 1000);
lcd.print("whistles counted  ");
lcd.setCursor(0,1);
lcd.print(count);
  delay(7000);
  noTone(buzzer);
//  lcd.clear();
 if(count == num )
{
myservo.write(20);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Food is Ready");  
lcd.setCursor(0,1);
lcd.print("Gas is off");  
delay(50000);
//lcd.clear();
}
}
}
test_prev=test;
}
