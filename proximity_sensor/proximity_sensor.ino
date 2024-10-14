/* Pins */
#define HC_ECHO 2 /* HC-SR04 sensor */
#define HC_TRIG 3 /* HC-SR04 sensor */
#define LED 8

#define SOUND_VELOCITY 34000 /* in cm/sec */

/* Distance considered far enough */
#define DIST_BASELINE 15 /* in cm */

#define LOOP_CYCLE_DELAY 200 /* in ms */

double dist; /* distance in cm */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(HC_ECHO, INPUT);
  pinMode(HC_TRIG, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  Serial.println("[proximity_sensor.ino]");
}

void loop() {
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(50);
  digitalWrite(HC_TRIG, LOW);
  
  dist = pulseIn(HC_ECHO, HIGH); /* round-trip time in microsec */
  dist = dist * SOUND_VELOCITY
       / 2                       /* half because of round-trip of sound */
       / 1000000;                /* convert microsec to sec */

  Serial.print(String("dist: ") + dist);
  
  int blink_delta;
  if (dist/DIST_BASELINE < 1) {
    blink_delta = dist/DIST_BASELINE * 500;
    if (blink_delta/2 == 0)
      blink_delta = 2;
  } else {
    Serial.print("\n");
    delay(LOOP_CYCLE_DELAY);
    return;
  }

  Serial.println(String("; blink: ") + blink_delta);

  int time_spent = 0;
  while (time_spent < LOOP_CYCLE_DELAY) {
    digitalWrite(LED, HIGH);
    delay(blink_delta/2);
    digitalWrite(LED, LOW);
    delay(blink_delta/2);
    time_spent += blink_delta;
  }
}
