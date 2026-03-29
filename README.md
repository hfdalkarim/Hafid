\# Hafid



Library Arduino untuk pemrosesan sinyal biopotensial berbasis Digital Signal Processing (DSP).



Library ini dirancang untuk aplikasi biomedical seperti:

\- ECG (Electrocardiogram)

\- EMG (Electromyogram)

\- EEG (Electroencephalogram)

\- EOG (Electrooculogram)



---



\## ✨ Fitur Utama



\- High-Pass Filter (Butterworth 1.0 Hz)

\- Low-Pass Filter (ECG, EMG, EEG, EOG)

\- Notch Filter 50/60 Hz (eliminasi noise PLN)

\- Moving Average Filter

\- Kalman Filter (1D)

\- Konversi ADC ke milliVolt (mV)



---



\## 🧠 Metode yang Digunakan



Library ini berbasis teori:

\- IIR Biquad Filter (Direct Form II Transposed)

\- Butterworth Filter

\- Notch Filter (band-stop)

\- Kalman Filter (state estimation)

\- Moving Average (low-pass smoothing)



---



\## ⚙️ Struktur Filter



Pemrosesan sinyal dilakukan berurutan:

ADC → High-pass → Notch → Low-pass → Moving Average → Kalman



---



\## 🚀 Instalasi



\### Arduino IDE

1\. Download ZIP dari repository

2\. Sketch → Include Library → Add .ZIP Library



\### Manual

Letakkan folder ke:

Documents/Arduino/libraries/





