#include <EEPROM.h>

#include "TM1637Driver.h"
#define DIO 8
#define CLK 7
TM1637 display(DIO, CLK);

// https://sites.google.com/site/diygeigercounter/technical/gm-tubes-supported
#define PULSE_PIN 2
#define TUBE_FACTOR (153.8f)

#define BUTTON_UP 10
#define BUTTON_DOWN 9
#define LONG_PRESS 1000
bool btnUp() { return digitalRead(BUTTON_UP) == 0; }
bool btnDown() { return digitalRead(BUTTON_DOWN) == 0; }

#define BUZZER_PIN 3
void click() { analogWrite(BUZZER_PIN, 255); delay(5); analogWrite(BUZZER_PIN, 0); }

#define LED_RED 6
#define LED_GREEN 5

bool isInterval(uint16_t interval) { return millis() % interval > (interval / 2); }
bool isTimestamp(uint32_t& timestamp, uint32_t interval) 
{
  if (millis() - timestamp >= interval)
  {
    timestamp = millis();
    return true;
  }
  return false;
}

// battery voltage chart: https://www.batteryskills.com/aa-battery-voltage-chart/
// --- Alkaline AA Battery:
// 100%     1.50 - 1.65V
// 50%      1.25 - 1.50V
// 0%       < 1.25V
// --- NiMH AA Battery:
// 100%     1.40 - 1.45V
// 50%      1.20 - 1.40V
// 0%       < 1.20V
// --- Lithium AA Battery (1.5V):
// 100%     1.50 - 1.80V
// 50%      1.30 - 1.50V
// 0%       < 1.30V
#define BATTERY_PIN A0
#define BATTERY_SAMPLES 10
const float highVoltage[3] = { 3.00f, 2.80f, 3.00f }; // Alkaline, NiMH, Lithium
const float lowVoltage[3] = { 2.50f, 2.40f, 2.60f }; // Alkaline, NiMH, Lithium
uint8_t _selectedBattery = 0;

float readVoltage()
{
  uint32_t avg = 0;
  for (int i = 0; i < BATTERY_SAMPLES; i++)
  {
    avg += analogRead(A0);
    delay(2);
  }
  avg /= BATTERY_SAMPLES;

  // (1.1V / 1023) * analog = (680 / (1200 + 680)) * Vbat
  // analog voltage ratio: 1.1V / 1023 = 0.001075
  // resistor ratio: 1 / (680 / (1200 + 680)) = 2.7647
  // Vbat = 0.001075 * 2.7647 * analog
  return 0.0029728f * avg;
}
uint8_t batteryPercent()
{
  float vbat = constrain(readVoltage(), lowVoltage[_selectedBattery], highVoltage[_selectedBattery]);
  float m = 100.0f / (highVoltage[_selectedBattery] - lowVoltage[_selectedBattery]);
  return m * vbat - m * lowVoltage[_selectedBattery];
}