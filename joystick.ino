#include <RF24.h>
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden

LiquidCrystal_I2C lcd(63, 20, 4); //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)" 

RF24 radio(9, 10);

#define X_AXIS A0
#define Y_AXIS A1
#define BUTTON_JOSYSTICK 8
#define BUTTON_A 2
#define BUTTON_B 3
#define BUTTON_C 4
#define BUTTON_D 5
#define BUTTON_E 6
#define BUTTON_F 7


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(X_AXIS, INPUT);
  pinMode(Y_AXIS, INPUT);
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_C, INPUT);
  pinMode(BUTTON_D, INPUT);
  pinMode(BUTTON_E, INPUT);
  pinMode(BUTTON_F, INPUT);
  pinMode(BUTTON_JOSYSTICK, INPUT);

  radio.begin();
  if (radio.isChipConnected()) { 
    Serial.println("Chip is connected");
  } else {
    Serial.println("connection error!");
  }
  lcd.init();
  lcd.backlight();

}

void printButton(char* button, int value) {
  lcd.print(button);
  lcd.print(": ");
  lcd.print(value);
  lcd.print(" ");
}
void loop() {
  int x = analogRead(X_AXIS);
  int y = analogRead(Y_AXIS);
  lcd.setCursor(0,0);
  lcd.print("Stick: ");
  if (x < 1000) {
    lcd.print(" ");
  } 
  if (x < 100) {
    lcd.print(" ");
  }
  if (x < 10) {
    lcd.print(" ");
  }
  lcd.print(x);
  lcd.print(",");
  if (y < 1000) {
    lcd.print(" ");
  }
  if (y < 100) {
    lcd.print(" ");
  }
  if (y < 10) {
    lcd.print(" ");
  }
  lcd.print(y);
  lcd.print(" / ");
  lcd.print(digitalRead(BUTTON_JOSYSTICK));
  lcd.setCursor(0,1);
  printButton("A", digitalRead(BUTTON_A));
  printButton("B", digitalRead(BUTTON_B));
  printButton("C", digitalRead(BUTTON_C));
  printButton("D", digitalRead(BUTTON_D));
  lcd.setCursor(0,2);
  printButton("E", digitalRead(BUTTON_E));
  printButton("F", digitalRead(BUTTON_F));
  lcd.setCursor(0,3);  
}