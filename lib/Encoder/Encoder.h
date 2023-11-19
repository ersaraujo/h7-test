#include <mbed.h>
#include <utils.h>

class Encoder {
public:
    Encoder(int pulsesPerRev, int tsample, TIM_TypeDef* timer);

    void init();
    void resetPulses();
    void update();
    double getFrequency();
    double getSpeed();
    int getPulses();

private:
    static void init_enc_timer(TIM_TypeDef *timer);
    static void init_enc_timer1();  // PE_9 PA_9 - Encoder of M1
    static void init_enc_timer8();  // PC_6 PC_7 - Encoder of M2
    static void init_enc_timer2();  // PA_5 PB_3 - Encoder of M3
    static void init_enc_timer3();

    TIM_TypeDef  *_timer;
    int _pulsesPerRev;
    volatile int _pulses;
    volatile double _frequency;
    int _tsample;

    Ticker _controlTicker;
};