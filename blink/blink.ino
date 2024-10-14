#define LED (9)

#define FADE (2)
#define FADE_BOOST (10)
#define FADE_BOOST_THRESHOLD (60)
#define FADE_STEP_DELAY (40)
#define FADE_LIGHT_MIN_DELAY (800)
#define FADE_LIGHT_MAX_DELAY (200)

int brightness = 0;
int fade_amount = FADE;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  int delay_amount = FADE_STEP_DELAY;

  if (brightness <= 0) {
    brightness = 0;
    fade_amount = FADE;
    delay_amount = FADE_LIGHT_MIN_DELAY;
  } else if (brightness >= 255) {
    brightness = 255;
    fade_amount = -FADE;
    delay_amount = FADE_LIGHT_MAX_DELAY;
  }
  
  analogWrite(LED, brightness);
  
  if (brightness < FADE_BOOST_THRESHOLD)
    brightness += fade_amount;
  else
    brightness += fade_amount * FADE_BOOST;
  
  delay(delay_amount);
}
