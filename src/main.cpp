#include <mbed.h>
#include <Motor.h>
#include <Encoder.h>
#include <utils.h>

static BufferedSerial serial_port(USBTX, USBRX, 230400);
FileHandle *mbed::mbed_override_console(int fd) { return &serial_port; }

// Motor M1(M1_PWM, M1_DIR);
// Motor M2(M2_PWM, M2_DIR);

// Encoder ENC1(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM1);
// Encoder ENC2(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM2);
// Encoder ENC3(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM2);
Encoder ENC4(int(PULSES_PER_REV), int(SAMPLE_TIME), TIM8);

DigitalIn pa5(PA_9);
DigitalIn pe5(PE_9);

int main()
{
    // M1.init();
    // M2.init();

    // ENC1.init();
    // ENC2.init();
    // ENC3.init();
    ENC4.init();

    printf("Start...\n");

    ThisThread::sleep_for(3000ms);

    while (true)
    {
        // double v1 = ENC1.getSpeed();
        // double v2 = ENC2.getSpeed();
        // while (fabs(v1)<200 && fabs(v2)<200) {
        //     v1 = ENC1.getSpeed();
        //     v2 = ENC2.getSpeed();
        //     printf("Waiting...");
        //     printf("Motor 1: %f | Motor 2: %f\n", v1, v2);
        // }

        // M1.run(0.08, 0);
        // M2.run(0.8, 1);
        // printf("Motor 1: %f \n", ENC1.getSpeed());
        // printf("Freq: %.2lf | Pulses: %d \n", ENC4.getFrequency(), ENC4.getPulses());
        printf("Timer 8: %f \n", ENC4.getSpeed());

        ThisThread::sleep_for(500ms);
    }
}