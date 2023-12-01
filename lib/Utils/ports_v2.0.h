// NOTES
// PC_6 and PD_6 cannot be InterruptIn

// #define M1_DIR  PB_6        // M1_PHASE
// #define M1_PWM  PB_5        // M1_ENABLE  TIM3_CH1
// #define M1_ENCA PA_8        // TIM1_CH1
// #define M1_ENCB PA_9        // TIM1_CH2

// #define M2_DIR  PA_15        // M2_PHASE
// #define M2_PWM  PB_7         // M2_ENABLE  TIM4_CH2
// #define M2_ENCA PC_7_ALT0    // TIM8_CH2
// #define M2_ENCB PC_6_ALT0    // TIM8_CH1

////

#define M1_PWM PD_12 // TIM4 (CH1)
#define M1_DIR PB_8
#define M1_RST PE_15
#define M1_MODE PE_6
#define M1_CST PE_12
#define M1_BRK PE_10
#define M1_ENCA PE_9(main)  // TIM1 (CH1)  | PE_9 (H7)
#define M1_ENCB PF_13(main) //             | PA_9 (H7)
#define M1_FF1 PF_14
#define M1_FF2 PE_11

#define M2_PWM PD_13 // TIM4 (CH2)
#define M2_DIR PB_11
#define M2_RST PE_15
#define M2_MODE PE_6
#define M2_CST PE_12
#define M2_BRK PE_10
#define M2_ENCA PE_5(main) // TIM9 (CH1) | PA_5 (H7)
#define M2_ENCB PE_7(main) //            |
#define M2_FF1 PB_7
#define M2_FF2 PB_6

#define M3_PWM PD_14 // TIM4 (CH3)
#define M3_DIR PC_0
#define M3_RST PE_15
#define M3_MODE PE_6
#define M3_CST PE_12
#define M3_BRK PE_10
// #define M3_ENCA PC_6 // TIM3 (CH1)
// #define M3_ENCB PB_15
#define M3_FF1 PC_2
#define M3_FF2 PF_10

#define M4_PWM PD_15 // TIM4 (CH4)
#define M4_DIR PC_8
#define M4_RST PE_15
#define M4_MODE PE_6
#define M4_CST PE_12
#define M4_BRK PE_10
// #define M4_ENCA PF_8  // TIM13 (CH1)
// #define M4_ENCB PD_6
#define M4_FF1 PD_5
#define M4_FF2 PD_4

#define M5_PWM PF_9 // TIM14 (CH1)
#define M5_DIR PD_0
#define M5_RST PB_13
#define M5_MODE PB_12
#define M5_CST PA_15
#define M5_BRK PC_9 // *
#define M5_FF1 PB_2
#define M5_FF2 PE_3
#define M5_TAC PD_7  // *
#define M5_DIRO PF_2 // *

#define PIN_CHARGE PE_0
#define PIN_CAP_LOAD PA_3
#define PIN_CHIP PG_3
#define PIN_FRONT PB_0
#define PIN_FAULT PD_11

#define NRF_R_MOSI PC_12
#define NRF_R_MISO PC_11
#define NRF_R_SCK PC_10
#define NRF_R_CSN PG_0
#define NRF_R_CE PB_1
#define NRF_R_IRQ PH_1
#define NRF_R_VCC PG_14

#define NRF_S_MOSI PC_12
#define NRF_S_MISO PC_11
#define NRF_S_SCK PC_10
#define NRF_S_CSN PF_3
#define NRF_S_CE PE_13
#define NRF_S_IRQ PG_1
#define NRF_S_VCC PA_0

// #define MPU_MOSI 	PC_3 // PA_7 // TIM1
// #define MPU_MISO 	PB_14 // PA_6 // TIM3
// #define MPU_SCK 	PB_10 // PA_5 // TIM2
// #define MPU_CS	 	PD_2
// #define MPU_IRQ 	PG_2

// ******* EXTERNAL MPU 6050 ******
// Needs to cut PF_0 PIN in main board!!!
#define MPU_SDA PF_0 // I2C
#define MPU_SCL PF_1 // I2C

#define PIN_BUZZER PF_7 // TIM11 (CH1)
#define PIN_RGB PD_1
#define PIN_BATT PF_6

#define PIN_IR_LED PB_4
#define PIN_IR_ADC PA_4
#define PIN_TEMP PF_5

#define PIN_SELECTOR_1 PE_6
#define PIN_SELECTOR_2 PE_2
#define PIN_SELECTOR_3 PD_3
#define PIN_SELECTOR_4 PE_4

#define PIN_PB1 PF_4
#define PIN_PB2 PG_6