#include "preferences.h"

volatile bool pulseEvent = false;
volatile uint32_t counts = 0;
uint32_t resetTimestamp = 0;
float cpm;
float uSievert;

uint32_t infoTimestamp;
bool showInfo = false;

uint32_t lastRefresh;
uint8_t displayIndex = 2; // 0=uS/h, 1=cpm, 2=total counts (will select next mode at start)

bool settings = false;
uint8_t settingsIndex = 0; // 0=battery, 1=sound, 2=leds
bool hasSound = true;
bool ledsOn = true;
const char batteryChars[3][5] = {
  { 'a', 'l', 'k', 'a', 'l' },
  { 'n', 'i', 'm', 'h', 0 },
  { 'l', 'i', 't', 'h', 'i' }
};


void setup() 
{
  // set up pins
  analogReference(INTERNAL);
  pinMode(BATTERY_PIN, INPUT);

  pinMode(PULSE_PIN, INPUT);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // show boot animation, set voltage stabilize
  display.clear();
  display.setInt(88888); // all segments on
  for (uint8_t i = 0; i < 8; i++)
  {
    analogWrite(LED_RED, 255 / 8 * i);
    analogWrite(LED_GREEN, 255 / 8 * i);

    display.setBrightness(i);
    display.show();
    delay(50);
  }
  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 0);

  // read EEPROM
  _selectedBattery = constrain(EEPROM.read(0), 0, 2);
  hasSound = constrain(EEPROM.read(1), 0, 1);
  ledsOn = constrain(EEPROM.read(2), 0, 1);

  // show battery voltage at start
  updateBrightness();
  display.setInt(batteryPercent(), true);
  display.move(2);
  display.setDigit(4, 0b00011011);
  display.show();
  delay(2000);

  // attach interrupt and begin counting
  attachInterrupt(digitalPinToInterrupt(PULSE_PIN), pulseInterrupt, FALLING);
  resetCounts();
  nextMode();
}
void loop() 
{
  if (btnUp())
  {
    uint32_t started = millis();
    bool longPress = false;
    while (btnUp())
    {
      updateScreen(false);
      if (!longPress && isTimestamp(started, LONG_PRESS))
      {
        longPress = true;
        settings = !settings;
        settingsIndex = 0;
      }
    }
    
    if (!longPress)
    {
      if (settings)
      {
        if (settingsIndex == 0)
          _selectedBattery = (_selectedBattery + 1) % 3;
        else if (settingsIndex == 1)
          hasSound = !hasSound;
        else
          ledsOn = !ledsOn;
      }
      else
        resetCounts();
    }
    else if (!settings)
      saveEEPROM();
    updateScreen(true);
  }

  if (btnDown())
  {
    while (btnDown()) updateScreen(false);
    
    nextMode();
    updateScreen(true);
  }

  if (showInfo && isTimestamp(infoTimestamp, 750))
  {
    showInfo = false;
    updateScreen(true);
  }
  else
    updateScreen(false);
}

void pulseInterrupt() 
{
  counts++;
  pulseEvent = true;
  if (hasSound)
    click();
}
void updateScreen(bool force)
{
  updateWarnLED();

  if (settings)
  {
    display.clear();
    if (settingsIndex == 0)
    {
      for (uint8_t i = 0; i < 5; i++)
        display.setDigit(i, display.getCharacter(batteryChars[_selectedBattery][i]));
    }
    else if (settingsIndex == 1)
    {
      display.setDigit(0, display.getNumber(5));
      if (hasSound)
      {
        display.setDigit(3, display.getCharacter('o'));
        display.setDigit(4, display.getCharacter('n'));
      }
      else
      {
        display.setDigit(2, display.getCharacter('o'));
        display.setDigit(3, display.getCharacter('f'));
        display.setDigit(4, display.getCharacter('f'));
      }
    }
    else
    {
      display.setDigit(0, display.getCharacter('l'));
      if (ledsOn)
      {
        display.setDigit(3, display.getCharacter('o'));
        display.setDigit(4, display.getCharacter('n'));
      }
      else
      {
        display.setDigit(2, display.getCharacter('o'));
        display.setDigit(3, display.getCharacter('f'));
        display.setDigit(4, display.getCharacter('f'));
      }
    }
    display.show();
    return;
  }

  if (showInfo)
  {
    display.clear();
    if (displayIndex == 0)
    {
      display.setDigit(0, display.getCharacter('u'));
      display.setDigit(1, display.getCharacter('5'));
      display.setDigit(2, display.getCharacter('/'));
      display.setDigit(3, display.getCharacter('h'));
    }
    else if (displayIndex == 1)
    {
      display.setDigit(0, display.getCharacter('c'));
      display.setDigit(1, display.getCharacter('p'));
      display.setDigit(2, display.getCharacter('m'));
    }
    else if (displayIndex == 2)
    {
      display.setDigit(0, display.getCharacter('c'));
      display.setDigit(1, display.getCharacter('o'));
      display.setDigit(2, display.getCharacter('u'));
      display.setDigit(3, display.getCharacter('n'));
      display.setDigit(4, display.getCharacter('t'));
    }
    display.show();
  }
  else
  {
    if (pulseEvent || force || isTimestamp(lastRefresh, 1000))
    {
      pulseEvent = false;
      cpm = counts / ((millis() - resetTimestamp) / 60000.0f);
      uSievert = cpm / TUBE_FACTOR;
      
      updateBrightness();
      if (displayIndex == 0)
        display.setFloat(uSievert);
      else if (displayIndex == 1)
        display.setFloat(cpm);
      else if (displayIndex == 2)
        display.setInt(counts % 100000, true);
      display.show();
    }
  }
}
void updateWarnLED()
{
  if (uSievert < 0.5f || (uSievert < 2.5f && !ledsOn))
  {
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_RED, 0);
  }
  else if (uSievert < 1.0f && ledsOn)
  {
    analogWrite(LED_GREEN, 80);
    analogWrite(LED_RED, 0);
  }
  else if (uSievert < 2.5f && ledsOn)
  {
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_RED, 0);
  }
  else if (uSievert < 5.0f)
  {
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_RED, 255);
  }
  else if (uSievert < 10.0f)
  {
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_RED, isInterval(1000) ? 255 : 0);
  }
  else if (uSievert < 100.0f)
  {
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_RED, isInterval(500) ? 255 : 0);
  }
  else 
  {
    analogWrite(LED_GREEN, isInterval(250) ? 255 : 0);
    analogWrite(LED_RED, isInterval(250) ? 255 : 0);
  }
}
void updateBrightness()
{
  uint8_t p = batteryPercent();
  if (p < 50)
  {
    uint8_t newBrightness = (uint8_t)((7.0f / 50.0f) * p);
    if (newBrightness < display.getBrightness())
      display.setBrightness(newBrightness, false);
  }
  else
    display.setBrightness(7, false);
}

void nextMode()
{
  if (!settings)
  {
    displayIndex = (displayIndex + 1) % 3;
    showInfo = true;
    infoTimestamp = millis();
  }
  else
  {
    settingsIndex = (settingsIndex + 1) % 3;
  }
}
void saveEEPROM()
{
  EEPROM.update(0, _selectedBattery);
  EEPROM.update(1, hasSound ? 1 : 0);
  EEPROM.update(2, ledsOn ? 1 : 0);
}

void resetCounts()
{
  counts = 0;
  resetTimestamp = millis() - 5; // -5ms: avoid dividing by 0
}