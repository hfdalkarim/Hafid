#ifndef HAFID_H
#define HAFID_H

#include <Arduino.h>

#define _ECG 1
#define _EOG 2
#define _EEG 3
#define _EMG 4

#define HAFID_ECG _ECG
#define HAFID_EOG _EOG
#define HAFID_EEG _EEG
#define HAFID_EMG _EMG

struct BiquadFilter {
    float _a, _b, _c;
    float _d, _e;
    float _f, _g;
    float _h;
    float _i;
};

struct KalmanFilter {
    float _j;
    float _k;
    float _l;
    float _m;
    float _n;
};

// Obfuscated internal functions
void _x1(BiquadFilter* _p, uint16_t _q);
float _x2(BiquadFilter* _r, float _s);
void _x3(BiquadFilter* _t, uint8_t _u, uint16_t _v);
float _x4(BiquadFilter* _w, float _x);
void _x5(BiquadFilter* _y, BiquadFilter* _z, uint16_t _aa, uint16_t _ab);
float _x6(BiquadFilter* _ac, BiquadFilter* _ad, float _ae);
void _x7(KalmanFilter* _af, float _ag, float _ah, float _ai);
float _x8(KalmanFilter* _aj, float _ak);
float _x9(int16_t _al, uint8_t _am, float _an);

// Public API wrappers (maintain original function names)
void initHighPassFilter(BiquadFilter* f, uint16_t samplingRate);
float processHighPass(BiquadFilter* f, float input);
void initExgFilter(BiquadFilter* f, uint8_t feature, uint16_t samplingRate);
float processExgFilter(BiquadFilter* f, float input);
void initNotchFilter(BiquadFilter* f1, BiquadFilter* f2, uint16_t notchFreq, uint16_t samplingRate);
float processNotchFilter(BiquadFilter* f1, BiquadFilter* f2, float input);
void initKalmanFilter(KalmanFilter* kf, float processNoise, float measurementNoise, float initialEstimate);
float processKalmanFilter(KalmanFilter* kf, float measurement);
float adcToMilliVolts(int16_t adcValue, uint8_t adcBits, float vref);

#endif