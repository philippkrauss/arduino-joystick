#include <RF24.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(39, 16, 2);

RF24 radio(9, 10);
const byte address[6] = "00001";

#define X_AXIS A0
#define Y_AXIS A1
#define BUTTON_JOSYSTICK 8
#define BUTTON_A 2
#define BUTTON_B 3
#define BUTTON_C 4
#define BUTTON_D 5
#define BUTTON_E 6
#define BUTTON_F 7

typedef struct {
  signed int x;
  signed int y;
  bool axis;
  bool a;
  bool b;
  bool c;
  bool d;
  bool e;
  bool f;
} JoystickValues;
int x, y;

long count = 0;

JoystickValues joystickValues;

void setup() {
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
    radio.setRetries(15, 15);
    radio.openWritingPipe(address);
    radio.enableDynamicPayloads();
    radio.enableAckPayload();
    radio.setAutoAck(true);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();

    lcd.init();
    lcd.backlight(); 
}

void readJoystick() {
  x = analogRead(X_AXIS);
  joystickValues.x = x - 517;
  y = analogRead(Y_AXIS);
  joystickValues.y = y - 511;
  joystickValues.axis = digitalRead(BUTTON_JOSYSTICK) == false;
  joystickValues.a = digitalRead(BUTTON_A);
  joystickValues.b = digitalRead(BUTTON_B);
  joystickValues.c = digitalRead(BUTTON_C);
  joystickValues.d = digitalRead(BUTTON_D);
  joystickValues.e = digitalRead(BUTTON_E);
  joystickValues.f = digitalRead(BUTTON_F);
}

char receivedData[33];

bool newData = false;

void sendAndReceive() {
  bool result;
  result = radio.write(&joystickValues, sizeof(JoystickValues));
  if (result) {
    lcd.setCursor(0, 0);
    if (radio.isAckPayloadAvailable()) {
      radio.read(receivedData, sizeof(receivedData));
      receivedData[32] = 0;
      newData = true;
    } else {
      sprintf(receivedData, "NO ACKDATA                      ");
      newData = true;
    }
  } else {
    sprintf(receivedData, "ERROR           NO CONNECTION   ");
    newData = true;
  }
  radio.txStandBy();
}

int counttt = 0;
void updateLcd() {
  if (!newData) {
    return;
  }
  newData = false;
  lcd.setCursor(0, 0);
  lcd.print(receivedData);
  lcd.setCursor(0, 1);
  lcd.print(&receivedData[16]);
}

long lastTime = 0;

void loop() {
    long currentTime = millis();
    if (currentTime - lastTime <= 150) {
      return;
    }
    lastTime = currentTime;

    readJoystick();
    sendAndReceive();
    updateLcd();
}