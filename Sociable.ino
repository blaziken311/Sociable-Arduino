// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <LiquidCrystal.h>

#define ECHO_PIN_ONE     13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_ONE  12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_TWO     11
#define TRIGGER_PIN_TWO  10 
#define MAX_DISTANCE     100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DEBUG true

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
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS1 = sonar_one.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int uS2 = sonar_two.ping();
  if (DEBUG){
  	Serial.print("Ping 1: ");
  	Serial.print(uS1 / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  	Serial.print("cm  ");
  	Serial.print("Ping 2: ");
  	Serial.print(uS2 / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  	Serial.println("cm");
    	lcd.print(uS1 / US_ROUNDTRIP_CM + "    " + uS2 / US_ROUNDTRIP_CM);
  }
}
