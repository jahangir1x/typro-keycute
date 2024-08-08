#pragma region[pin declaration]
const uint8_t _D2 = 2;
const uint8_t _D3 = 3;
const uint8_t _D4 = 4;
const uint8_t _D5 = 5;
const uint8_t _D6 = 6;
const uint8_t _D7 = 7;
const uint8_t _D8 = 8;
const uint8_t _D9 = 9;
const uint8_t _D10 = 10;
const uint8_t _D11 = 11;
const uint8_t _D12 = 12;
const uint8_t _D13 = 13;
const uint8_t _A0 = 14;
const uint8_t _A1 = 15;
const uint8_t _A2 = 16;
const uint8_t _A3 = 17;
const uint8_t _A4 = 18;
const uint8_t _A5 = 19;
const uint8_t _A6 = 20;
const uint8_t _A7 = 21;
#pragma endregion

const uint8_t OUTPUT_PIN_COUNT = 10;
const uint8_t INPUT_PIN_COUNT = 9;

const uint8_t INPUT_PINS[INPUT_PIN_COUNT] = {_D12, _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7};
const uint8_t OUTPUT_PINS[OUTPUT_PIN_COUNT] = {_D2, _D3, _D4, _D5, _D6, _D7, _D8, _D9, _D10, _D11};

const uint16_t startupDelayCycle = 500;
uint16_t currentDelayCycle = 0;

enum SwitchState {
    PRESSED = 0,
    RELEASED = 1,
};

void setup() {
    randomSeed(analogRead(0));
    for (uint8_t i = 0; i < OUTPUT_PIN_COUNT; i++) {
        pinMode(OUTPUT_PINS[i], OUTPUT);
        digitalWrite(OUTPUT_PINS[i], HIGH);
    }

    for (uint8_t i = 0; i < INPUT_PIN_COUNT; i++) {
        pinMode(INPUT_PINS[i], INPUT_PULLUP);
    }

    Serial.begin(9600);
}

bool KeyPressedMatrix[OUTPUT_PIN_COUNT][INPUT_PIN_COUNT] = {
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
    {false, false, false, false, false, false, false, false, false},
};

void loop() {
    for (uint8_t i = 0; i < OUTPUT_PIN_COUNT; i++) {
        digitalWrite(OUTPUT_PINS[i], LOW);
        delayMicroseconds(5);

        for (uint8_t j = 0; j < INPUT_PIN_COUNT; j++) {
            if (digitalRead(INPUT_PINS[j]) == LOW) {
                if (!KeyPressedMatrix[i][j]) {
                    KeyPressedMatrix[i][j] = true;
                    sendSwitchState(PRESSED, OUTPUT_PINS[i], INPUT_PINS[j]);
                }
            } else {
                if (KeyPressedMatrix[i][j]) {
                    KeyPressedMatrix[i][j] = false;
                    sendSwitchState(RELEASED, OUTPUT_PINS[i], INPUT_PINS[j]);
                }
            }
        }
        digitalWrite(OUTPUT_PINS[i], HIGH);
        delayMicroseconds(500);
    }
    if (currentDelayCycle < startupDelayCycle) {
        currentDelayCycle += 1;
    }
}

void sendSwitchState(SwitchState state, uint8_t outputPin, bool inputPin) {
    if (currentDelayCycle < startupDelayCycle) {
        return;
    }
    Serial.print(state);
    Serial.print(" ");
    Serial.print(outputPin);
    Serial.print(" ");
    Serial.print(inputPin);
    Serial.println();
}