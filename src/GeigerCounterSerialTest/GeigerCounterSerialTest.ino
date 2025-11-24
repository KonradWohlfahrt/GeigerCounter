#define PULSE_PIN 2
#define TUBE_FACTOR (151.0f)

volatile bool pulseEvent = false;
volatile uint32_t counts = 0;

uint32_t last;

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PULSE_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PULSE_PIN), pulseInterrupt, FALLING);

  // wait for serial connection
  while(!Serial);

  Serial.println("Time\tcounts\tcpm\tuS/h");
}
void loop() 
{
  if (millis() - last >= 1000)
  {
    float cpm = counts / (millis() / 60000.0f); // cpm
    float uSievert = cpm / TUBE_FACTOR; // uS/h

    Serial.print(millis() / 1000);
    Serial.print('\t');
    Serial.print(counts);
    Serial.print('\t');
    Serial.print(cpm);
    Serial.print('\t');
    Serial.println(uSievert);
    
    last = millis();
  }
}

void pulseInterrupt() 
{
  pulseEvent = true;
  counts++;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
}