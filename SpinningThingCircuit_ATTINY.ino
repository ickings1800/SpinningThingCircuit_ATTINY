#define STEPPER_POT_PIN A0
#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define LED_PIN 5
#define MICRO_SWITCH_PIN 6
#define LIGHT_BUTTON 7
#define MAX_SPEED_MS 10 // 15RPM
#define MIN_SPEED_MS 38 // 4RPM
#define ON_RATIO 0.8f
#define OFF_RATIO 0.2f

// LED configuration
const float intensity[6] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f };
byte led_state = 0;

// Stepper configuration
const int threshold = MIN_SPEED_MS - MAX_SPEED_MS; // 4RPM to 15RPM
byte stepper_state = -1;
float step_on;
float step_off;
int potVal = -1;


void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BLACK, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(STEPPER_POT_PIN, INPUT);
    pinMode(LIGHT_BUTTON, INPUT);
    pinMode(MICRO_SWITCH_PIN, INPUT);
}

void loop() {
    if (digitalRead(LIGHT_BUTTON) == HIGH){
        // switch LED state
        led_state++;
        if (led_state > 5) {
            led_state = 0;
        }
        delay(500);
        analogWrite(LED_PIN, 255 * intensity[led_state]);
    }

    if (analogRead(STEPPER_POT_PIN) != potVal) {
        potVal = analogRead(STEPPER_POT_PIN);
        float potRatio = analogRead(STEPPER_POT_PIN) / 1023.0;
        float cycle = MAX_SPEED_MS + (threshold * potRatio);
        step_off = cycle * OFF_RATIO;
        step_on = cycle * ON_RATIO;
    }
    
    // ACTIVATE STEPPER
    if (digitalRead(MICRO_SWITCH_PIN) == HIGH) {
        stepper_state++;
        if (stepper_state > 7) {
            stepper_state = 0;
        }
    } else {
        stepper_state = -1;
    }

    stepper(stepper_state);
    delay(step_on);
    stepper_off();
    delay(step_off);
}

void stepper(int state) {
    switch (state) {
        case 0:
          digitalWrite(BLACK, HIGH);
          digitalWrite(GREEN, LOW);
          digitalWrite(RED, HIGH);
          digitalWrite(BLUE, LOW);
          break;
        case 1:
          digitalWrite(BLACK, LOW);
          digitalWrite(GREEN, LOW);
          digitalWrite(RED, HIGH);
          digitalWrite(BLUE, LOW);
          break;
        case 2:
          digitalWrite(BLACK, LOW);
          digitalWrite(GREEN, HIGH);
          digitalWrite(RED, HIGH);
          digitalWrite(BLUE, LOW);
          break;
        case 3:
          digitalWrite(BLACK, LOW);
          digitalWrite(GREEN, HIGH);
          digitalWrite(RED, LOW);
          digitalWrite(BLUE, LOW);
          break;
        case 4:
          digitalWrite(BLACK, LOW);
          digitalWrite(GREEN, HIGH);
          digitalWrite(RED, LOW);
          digitalWrite(BLUE, HIGH);
          break;
        case 5:
          digitalWrite(BLACK, LOW);
          digitalWrite(GREEN, LOW);
          digitalWrite(RED, LOW);
          digitalWrite(BLUE, HIGH);
          break;
        case 6:
          digitalWrite(BLACK, HIGH);
          digitalWrite(GREEN, LOW);
          digitalWrite(RED, LOW);
          digitalWrite(BLUE, HIGH);
          break;
        case 7:
          digitalWrite(BLACK, HIGH);
          digitalWrite(GREEN, LOW);
          digitalWrite(RED, LOW);
          digitalWrite(BLUE, LOW);
          break;
        default:
          stepper_off();
          break;
    }
}

void stepper_off() {
    digitalWrite(BLACK, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
}

