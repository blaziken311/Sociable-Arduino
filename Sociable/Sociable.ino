#include <NewPing.h>
#include <LiquidCrystal.h>

#define ECHO_PIN_ONE     13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_ONE  12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_TWO     11
#define TRIGGER_PIN_TWO  10 
#define MAX_DISTANCE     100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DEBUG            true
#define TIME_SEC         300
boolean isPhoneThere1;
boolean isPhoneThere2;
int timer1 = TIME_SEC;
int timer2 = TIME_SEC;
int lastRecordedTime = 0;

NewPing sonar_one(TRIGGER_PIN_ONE, ECHO_PIN_ONE, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_two(TRIGGER_PIN_TWO, ECHO_PIN_TWO, MAX_DISTANCE);
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Left       Right");
}

void loop() {
  delay(500);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS1 = sonar_one.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int uS2 = sonar_two.ping();
  Serial.print("Ping 1: ");
  Serial.print(double(uS1) / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print("cm  ");
  Serial.print("Ping 2: ");
  Serial.print(double(uS2) / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print("cm ");
  Serial.print(String(millis()/ 1000.0));
  Serial.print(" ");
  Serial.println(String(lastRecordedTime));
  isPhoneThere1 = isPhone(double(uS1) / US_ROUNDTRIP_CM);
  isPhoneThere2 = isPhone(double(uS2) / US_ROUNDTRIP_CM); 
    if (millis() / 1000.0 - lastRecordedTime >= 1){
      lastRecordedTime += 1;
      if (!isPhoneThere1)
        timer1 = timer1 - 1;
      if (!isPhoneThere2)
        timer2 = timer2 - 1;
    }
    lcd.setCursor(0,1);
    lcd.print(String(timer1) + "          " + String(timer2));
}

boolean isPhone(double distance){
  if (distance < 5.0 && !0.0){
    return true;
  }
    return false;
}

