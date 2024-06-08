#include <mbed.h>
#include <Motor.h>
#include <utils.h>
#include <Encoder.h>

static BufferedSerial serial_port(USBTX, USBRX, 230400);
FileHandle *mbed::mbed_override_console(int fd) { return &serial_port; }

Motor M1(M1_PWM, M1_DIR, M1_RST, M1_MODE, M1_CST, M1_BRK);
Motor M2(M2_PWM, M2_DIR, M2_RST, M2_MODE, M2_CST, M2_BRK);
Motor M3(M3_PWM, M3_DIR, M3_RST, M3_MODE, M3_CST, M3_BRK);
Motor M4(M4_PWM, M4_DIR, M4_RST, M4_MODE, M4_CST, M4_BRK);

Encoder ENC1(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM1);
Encoder ENC2(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM2);
Encoder ENC3(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM8);
Encoder ENC4(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM3);

int main()
{
    M1.init();
    M2.init();
    M3.init();
    M4.init();

    ENC1.init();
    ENC2.init();
    ENC3.init();
    ENC4.init();

    printf("Start...\n");

    ThisThread::sleep_for(3s);

    while (true)
    {   
        // M1.run(20);
        // M2.run(20);
        // M3.run(20);
        // M4.run(20);
        // ThisThread::sleep_for(2s);
        // M1.run(0);
        // M2.run(0);
        // M3.run(0);
        // M4.run(0);
        // ThisThread::sleep_for(2s);
        // M1.run(-20);
        // M2.run(-20);
        // M3.run(-20);
        // M4.run(-20);
        // ThisThread::sleep_for(2s);
        // M1.run(0);
        // M2.run(0);
        // M3.run(0);
        // M4.run(0);
        // ThisThread::sleep_for(2s);
        
        printf("M1: %.2lf | M2: %.2lf | M3: %.2lf | M4: %.2lf\n", ENC1.getSpeed(), ENC2.getSpeed(), ENC3.getSpeed(), ENC4.getSpeed());

        
    }

}