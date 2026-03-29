#include "hafid.h"

// --- HAFID_ECG, HAFID_EMG, HAFID_EEG,HAFID_EOG ---
const uint8_t SELECTED_FEATURE = HAFID_ECG;
const uint16_t NOTCH_HZ = 50; 
const uint16_t SAMPLING_RATE = 250; //500

// --- Arduino ---
const int ANALOG_INPUT_PIN = A0;     
const int ANALOG_INPUT_INA = A1;
const uint8_t ADC_BITS = 10;         
const float VREF = 5.0;              
// -------------------------------

// --- ESP32 C3 Mini ---
// const int ANALOG_INPUT_PIN = 0;     
// const int ANALOG_INPUT_INA = 1;
// const uint8_t ADC_BITS = 12;         
// const float VREF = 3.3;              
// -------------------------------

const unsigned long SAMPLE_INTERVAL_MS = 4; 
unsigned long lastSampleTime = 0;
const int MA_WINDOW_SIZE = 5;
float maBuffer[MA_WINDOW_SIZE];
int maIndex = 0;
bool maBufferFilled = false;
float movingAverageFilter(float newSample) {
    maBuffer[maIndex] = newSample;
    maIndex = (maIndex + 1) % MA_WINDOW_SIZE;
    if (maIndex == 0) maBufferFilled = true;
    float sum = 0;
    int count = maBufferFilled ? MA_WINDOW_SIZE : maIndex;
    for (int i = 0; i < count; i++) sum += maBuffer[i];
    return sum / count;
}
const float KALMAN_PROCESS_NOISE = 12.32;    
const float KALMAN_MEASUREMENT_NOISE = 39.0; 
BiquadFilter highPassFilter;
BiquadFilter exgFilter;
BiquadFilter notchFilter1;
BiquadFilter notchFilter2;
KalmanFilter kalmanFilter;

void setup() {
    Serial.begin(115200);
    pinMode(ANALOG_INPUT_PIN, INPUT);
    pinMode(ANALOG_INPUT_INA, INPUT);
    initHighPassFilter(&highPassFilter, SAMPLING_RATE);
    initExgFilter(&exgFilter, SELECTED_FEATURE, SAMPLING_RATE);
    initNotchFilter(&notchFilter1, &notchFilter2, NOTCH_HZ, SAMPLING_RATE);
    initKalmanFilter(&kalmanFilter, KALMAN_PROCESS_NOISE, KALMAN_MEASUREMENT_NOISE, 0);
    for (int i = 0; i < MA_WINDOW_SIZE; i++) maBuffer[i] = 0;
    lastSampleTime = millis();
}

void loop() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_MS) {
        lastSampleTime = currentTime;
        int adcRaw = analogRead(ANALOG_INPUT_PIN);
        int adcRawina = analogRead(ANALOG_INPUT_INA);
        float voltageRaw = (adcRaw / (pow(2, ADC_BITS) - 1.0)) * VREF * 1000.0;
        float voltageRawina = (adcRawina / (pow(2, ADC_BITS) - 1.0)) * VREF * 1000.0;
        float afterHPF = processHighPass(&highPassFilter, voltageRaw);
        float afterNotch = processNotchFilter(&notchFilter1, &notchFilter2, afterHPF);
        float filteredVoltage = processExgFilter(&exgFilter, afterNotch);
        float maFiltered = movingAverageFilter(filteredVoltage);
        float kalmanFiltered = processKalmanFilter(&kalmanFilter, maFiltered);
        Serial.print("INA:");
        Serial.print(voltageRawina, 2);
        Serial.print(" ");
        Serial.print("RAW:");
        Serial.print(voltageRaw, 2);
        Serial.print(" ");
        Serial.print("LPF:");
        Serial.print(filteredVoltage, 6);
        Serial.print(" ");
        Serial.print("MA:");
        Serial.print(maFiltered, 6);
        Serial.print(" ");
        Serial.print("KALMAN:");
        Serial.println(kalmanFiltered, 6); 
    }
}