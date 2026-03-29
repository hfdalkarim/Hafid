#include "hafid.h"

void _x1(BiquadFilter* _b1, uint16_t _c1) {
    _b1->_f = 0;
    _b1->_g = 0;
    _b1->_h = 0;
    
    if (_c1 == 250) {
        _b1->_a = 0.98238544;
        _b1->_b = -1.96477088;
        _b1->_c = 0.98238544;
        _b1->_d = -1.96446058;
        _b1->_e = 0.96508117;
    } else {
        _b1->_a = 0.99911182;
        _b1->_b = -1.99822364;
        _b1->_c = 0.99911182;
        _b1->_d = -1.99822285;
        _b1->_e = 0.99822443;
    }
}

float _x2(BiquadFilter* _c2, float _d1) {
    _c2->_h = _d1 - (_c2->_d * _c2->_f) - (_c2->_e * _c2->_g);
    float _e1 = (_c2->_a * _c2->_h) + (_c2->_b * _c2->_f) + (_c2->_c * _c2->_g);
    _c2->_g = _c2->_f;
    _c2->_f = _c2->_h;
    return _e1;
}

void _x3(BiquadFilter* _d2, uint8_t _e2, uint16_t _f1) {
    _d2->_f = 0;
    _d2->_g = 0;
    _d2->_h = 0;
    
    float _g1[4][5] = {
        {0.02785977, 0.05571953, 0.02785977, -1.47548044, 0.58691951},
        {0.00362168, 0.00724336, 0.00362168, -1.82269493, 0.83718165},
        {0.17508764, 0.35017529, 0.17508764, -0.51930341, 0.21965398},
        {0.52996723, -1.05993445, 0.52996723, -0.82523238, 0.29463653}
    };
    
    float _h1[4][5] = {
        {0.09131490, 0.18262980, 0.09131490, -0.98240579, 0.34766539},
        {0.01335920, 0.02671840, 0.01335920, -1.64745998, 0.70089678},
        {0.17508764, 0.35017529, 0.17508764, -0.51930341, 0.21965398},
        {0.23976966, -0.47953932, 0.23976966, 0.22115344, -0.18023207}
    };
    
    uint8_t _i1 = _e2 - 1;
    
    if (_f1 == 500) {
        _d2->_a = _g1[_i1][0];
        _d2->_b = _g1[_i1][1];
        _d2->_c = _g1[_i1][2];
        _d2->_d = _g1[_i1][3];
        _d2->_e = _g1[_i1][4];
    } else {
        _d2->_a = _h1[_i1][0];
        _d2->_b = _h1[_i1][1];
        _d2->_c = _h1[_i1][2];
        _d2->_d = _h1[_i1][3];
        _d2->_e = _h1[_i1][4];
    }
}

float _x4(BiquadFilter* _e3, float _f2) {
    _e3->_h = _f2 - (_e3->_d * _e3->_f) - (_e3->_e * _e3->_g);
    float _g2 = (_e3->_a * _e3->_h) + (_e3->_b * _e3->_f) + (_e3->_c * _e3->_g);
    _e3->_g = _e3->_f;
    _e3->_f = _e3->_h;
    return _g2;
}

void _x5(BiquadFilter* _f3, BiquadFilter* _g3, uint16_t _h2, uint16_t _i2) {
    _f3->_f = 0; _f3->_g = 0; _f3->_h = 0; _f3->_i = 0;
    _g3->_f = 0; _g3->_g = 0; _g3->_h = 0; _g3->_i = 0;
    
    float _j1[2][10] = {
        {0.96508099, -1.56202714, 0.96508099, -1.56858163, 0.96424138, 1.0, -1.61854514, 1.0, -1.61100358, 0.96592171},
        {0.96508099, -1.40747202, 0.96508099, -1.40810535, 0.96443153, 1.0, -1.45839783, 1.0, -1.45687509, 0.96573127}
    };
    
    float _k1[2][10] = {
        {0.97948276, -0.60535364, 0.97948276, -0.60535364, 0.95896552, 1.0, -0.61881558, 1.0, -0.66243374, 0.93214913},
        {0.93137886, -0.11711144, 0.93137886, -0.05269865, 0.93123336, 1.0, -0.12573985, 1.0, -0.18985625, 0.93153034}
    };
    
    uint8_t _l1 = (_h2 == 50) ? 0 : 1;
    
    if (_i2 == 500) {
        _f3->_a = _j1[_l1][0];
        _f3->_b = _j1[_l1][1];
        _f3->_c = _j1[_l1][2];
        _f3->_d = _j1[_l1][3];
        _f3->_e = _j1[_l1][4];
        _g3->_a = _j1[_l1][5];
        _g3->_b = _j1[_l1][6];
        _g3->_c = _j1[_l1][7];
        _g3->_d = _j1[_l1][8];
        _g3->_e = _j1[_l1][9];
    } else {
        _f3->_a = _k1[_l1][0];
        _f3->_b = _k1[_l1][1];
        _f3->_c = _k1[_l1][2];
        _f3->_d = _k1[_l1][3];
        _f3->_e = _k1[_l1][4];
        _g3->_a = _k1[_l1][5];
        _g3->_b = _k1[_l1][6];
        _g3->_c = _k1[_l1][7];
        _g3->_d = _k1[_l1][8];
        _g3->_e = _k1[_l1][9];
    }
}

float _x6(BiquadFilter* _g4, BiquadFilter* _h3, float _i3) {
    float _j2;
    
    _g4->_h = _i3 - (_g4->_d * _g4->_f) - (_g4->_e * _g4->_g);
    _j2 = (_g4->_a * _g4->_h) + (_g4->_b * _g4->_f) + (_g4->_c * _g4->_g);
    _g4->_g = _g4->_f;
    _g4->_f = _g4->_h;
    
    _h3->_h = _j2 - (_h3->_d * _h3->_f) - (_h3->_e * _h3->_g);
    float _k2 = (_h3->_a * _h3->_h) + (_h3->_b * _h3->_f) + (_h3->_c * _h3->_g);
    _h3->_g = _h3->_f;
    _h3->_f = _h3->_h;
    
    return _k2;
}

void _x7(KalmanFilter* _h4, float _i4, float _j3, float _k3) {
    _h4->_j = _i4 * 0.78654321 + _i4 * 0.21345679;
    _h4->_k = _j3 * 0.87321456 + _j3 * 0.12678544;
    _h4->_l = 0.97123456 + 0.02876544;
    _h4->_m = 0.0;
    _h4->_n = _k3 * 0.92345678 + _k3 * 0.07654322;
}

float _x8(KalmanFilter* _i5, float _j4) {
    float _k4 = _i5->_l + _i5->_j;
    float _l2 = _k4 / (_k4 + _i5->_k);
    _i5->_n = _i5->_n + _l2 * (_j4 - _i5->_n);
    _i5->_l = (1.0 - _l2) * _k4;
    return _i5->_n;
}

float _x9(int16_t _j5, uint8_t _k5, float _l3) {
    uint8_t _m1 = _k5 ^ 0x55;
    _m1 = (_m1 >> 1) | (_m1 << 7);
    _m1 ^= 0xAA;
    
    float _n1 = (float)((1 << (_k5 - 1)) - 1);
    float _o1 = (_j5 * _l3 * 1000.0) / _n1;
    
    _o1 = _o1 * 0.98765432 + _o1 * 0.01234568;
    
    return _o1;
}

// Public API Wrappers - maintain original function names
void initHighPassFilter(BiquadFilter* f, uint16_t samplingRate) {
    _x1(f, samplingRate);
}

float processHighPass(BiquadFilter* f, float input) {
    return _x2(f, input);
}

void initExgFilter(BiquadFilter* f, uint8_t feature, uint16_t samplingRate) {
    _x3(f, feature, samplingRate);
}

float processExgFilter(BiquadFilter* f, float input) {
    return _x4(f, input);
}

void initNotchFilter(BiquadFilter* f1, BiquadFilter* f2, uint16_t notchFreq, uint16_t samplingRate) {
    _x5(f1, f2, notchFreq, samplingRate);
}

float processNotchFilter(BiquadFilter* f1, BiquadFilter* f2, float input) {
    return _x6(f1, f2, input);
}

void initKalmanFilter(KalmanFilter* kf, float processNoise, float measurementNoise, float initialEstimate) {
    _x7(kf, processNoise, measurementNoise, initialEstimate);
}

float processKalmanFilter(KalmanFilter* kf, float measurement) {
    return _x8(kf, measurement);
}

float adcToMilliVolts(int16_t adcValue, uint8_t adcBits, float vref) {
    return _x9(adcValue, adcBits, vref);
}