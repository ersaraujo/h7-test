#include <Encoder.h>

Encoder::Encoder(int pulsesPerRev, int tsample, TIM_TypeDef *timer)
{
  _pulsesPerRev = pulsesPerRev;
  _tsample = tsample;
  _timer = timer;
}

void Encoder::init()
{
    init_enc_timer(this->_timer);
    this->resetPulses();
    _controlTicker.attach(callback(this, &Encoder::update), chrono::milliseconds(_tsample));

}

void Encoder::update()
{
    
    _frequency = double((this->getPulses() * (1.0 / (_tsample/1000.0))) / (4.0 * _pulsesPerRev));
    this->resetPulses();
    // printf("Frequency: %lf | Pulses: %d \n", _frequency, _pulses);
}

double Encoder::getFrequency()
{
    return _frequency;
}

double Encoder::getSpeed()
{
    return 2.0 * M_PI * (MOTOR_GEAR/WHEEL_GEAR) * this->getFrequency();
}

void Encoder::resetPulses()
{
  // Reset Timer and Pulses counter
  this->_timer->CNT = PULSES_RESET;
  _pulses = 0;
}

int Encoder::getPulses()
{
    _pulses = PULSES_RESET - this->_timer->CNT;
    return _pulses;
}

void Encoder::init_enc_timer(TIM_TypeDef *timer)
{
  if (timer == TIM1){
    init_enc_timer1();
    init_enc_timer2();
    init_enc_timer3();
    init_enc_timer8();
  }
  else if (timer == TIM8){
    init_enc_timer1();
    init_enc_timer2();
    init_enc_timer3();
    init_enc_timer8();
  }
  else if (timer == TIM2){
    init_enc_timer1();
    init_enc_timer2();
    init_enc_timer3();
    init_enc_timer8();
  }
  else if (timer == TIM3){
    init_enc_timer1();
    init_enc_timer2();
    init_enc_timer3();
    init_enc_timer8();
  }
}


// AFR[0] geralmente é associado aos pinos de 0 a 7, enquanto AFR[1] é associado aos pinos de 8 a 15.

void Encoder::init_enc_timer1()
{
// Habilitar o clock para o Timer 1 e os portos GPIOE e GPIOA
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN | RCC_AHB4ENR_GPIOAEN;

  // Configurar pinos GPIO para modo alternativo
  GPIOE->MODER &= ~GPIO_MODER_MODE9; // Limpar bits
  GPIOE->MODER |= GPIO_MODER_MODE9_1; // Modo alternativo

  GPIOA->MODER &= ~GPIO_MODER_MODE9; // Limpar bits
  GPIOA->MODER |= GPIO_MODER_MODE9_1; // Modo alternativo

  GPIOE->OTYPER |= GPIO_OTYPER_OT9; // Saída push-pull
  GPIOA->OTYPER |= GPIO_OTYPER_OT9; // Saída push-pull

  GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED9; // Velocidade máxima
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED9; // Velocidade máxima

  GPIOE->AFR[1] |= (1 << GPIO_AFRH_AFSEL9_Pos); // Selecionar função alternativa AF1 para o pino PE9
  GPIOA->AFR[1] |= (1 << GPIO_AFRH_AFSEL9_Pos); // Selecionar função alternativa AF1 para o pino PA9

  // Configurar Timer 1
  TIM1->CR1 = 0;
  TIM1->CR2 = 0;
  TIM1->PSC = 0;
  TIM1->ARR = 0xFFFF;
  TIM1->RCR = 0;

  // Configurar modos de captura/comparação
  TIM1->CCMR1 = TIM_CCMR1_CC1S_0 | (0x0A << 4) | TIM_CCMR1_CC2S_0 | (0x0A << 12);
  TIM1->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E; // Habilitar captura nos canais 1 e 2
  TIM1->DIER = 0;

  // Configurar modo de encoder
  TIM1->SMCR = 3; // Modo de encoder 3 (conta todas as transições)
  TIM1->CR1 = TIM_CR1_CEN; // Habilitar o contador

  printf("TIM1->CR1: %X\n", TIM1->CR1);      // Configurações de controle do timer
  printf("TIM1->SMCR: %X\n", TIM1->SMCR);    // Configurações de controle do modo do timer
  printf("TIM1->CCMR1: %X\n", TIM1->CCMR1);  // Configurações de captura/comparação do canal 1
  printf("TIM1->CCMR2: %X\n", TIM1->CCMR2);  // Configurações de captura/comparação do canal 2
  printf("TIM1->CCER: %X\n", TIM1->CCER);    // Configurações de controle dos canais de captura/comparação
  printf("TIM1->PSC: %X\n", TIM1->PSC);      // Prescaler do timer
  printf("TIM1->ARR: %X\n", TIM1->ARR);      // Valor de recarga automática (Auto-Reload Register)
  printf("TIM1->CNT: %X\n", TIM1->CNT);      // Valor do contador do timer
  printf("TIM1->AFR: %X\n", GPIOC->AFR[1]);


}

void Encoder::init_enc_timer8()   // PC_6 PC_7 - REVISAR
{
  RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
  RCC->AHB1ENR |= RCC_AHB4ENR_GPIOCEN;

  GPIOC->MODER &= ~GPIO_MODER_MODE6_Msk; // Tentar ~GPIO_MODER_MODE6_Msk
  GPIOC->MODER |= GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0;

  GPIOC->OTYPER |= ~(GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);

  GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_0 | GPIO_OSPEEDR_OSPEED7_0;

  GPIOC->AFR[0] |= GPIO_AFRL_AFSEL6_0  | GPIO_AFRL_AFSEL7_0 ;

  TIM8->CR1 = 0;
  TIM8->CR2 = 0;
  TIM8->PSC = 0;
  TIM8->ARR = 0xFFFF;
  TIM8->RCR = 0;

  TIM8->CCMR1 = TIM_CCMR1_CC1S_0 | (0x0A << 4) | TIM_CCMR1_CC2S_0 | (0x0A << 12);
  TIM8->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;
  TIM8->DIER = 0;

  TIM8->SMCR = 3;
  TIM8->CR1 = TIM_CR1_CEN;

  printf("TIM8->CR1: %X\n", TIM8->CR1);      // Configurações de controle do timer
  printf("TIM8->SMCR: %X\n", TIM8->SMCR);    // Configurações de controle do modo do timer
  printf("TIM8->CCMR1: %X\n", TIM8->CCMR1);  // Configurações de captura/comparação do canal 1
  printf("TIM8->CCMR2: %X\n", TIM8->CCMR2);  // Configurações de captura/comparação do canal 2
  printf("TIM8->CCER: %X\n", TIM8->CCER);    // Configurações de controle dos canais de captura/comparação
  printf("TIM8->PSC: %X\n", TIM8->PSC);      // Prescaler do timer
  printf("TIM8->ARR: %X\n", TIM8->ARR);      // Valor de recarga automática (Auto-Reload Register)
  printf("TIM8->CNT: %X\n", TIM8->CNT);      // Valor do contador do timer
  printf("TIM8->AFR: %X\n", GPIOC->AFR[0]);
}

void Encoder::init_enc_timer2()   // PA_5 PB_3 - AJUSTAR ORDEM DE CAPTURA
{
  // Ativar o clock para o Timer 2 e os GPIOs relevantes
  RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
  RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN;

  // Configurar os pinos PA_5 e PB_3 como entradas de captura
  GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
  GPIOB->MODER &= ~GPIO_MODER_MODE3_Msk;

  // Configurar os pinos para modo de captura
  GPIOA->MODER |= GPIO_MODER_MODE5_1;
  GPIOB->MODER |= GPIO_MODER_MODE3_1;

  // Configurar a velocidade dos pinos (opcional)
  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
  GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;

  // Configurar os pinos para AF1 (modificando os bits de AFSEL5 e AFSEL3)
  GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;  // Configurar AF1 para PA_5
  GPIOB->AFR[0] |= GPIO_AFRL_AFSEL3_0;  // Configurar AF1 para PB_3

  // Configurar o Timer 2
  TIM2->CR1 = 0;
  TIM2->CR2 = 0;
  TIM2->PSC = 0;
  TIM2->ARR = 0xFFFF;
  TIM2->RCR = 0;

  // Configurar os canais de captura
  TIM2->CCMR1 = TIM_CCMR1_CC1S_0 | (0x0A << 4) | TIM_CCMR1_CC2S_0 | (0x0A << 12);
  TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;

  TIM1->CCMR1 = TIM_CCMR1_CC1S_0 | (0x0A << 4) | TIM_CCMR1_CC2S_0 | (0x0A << 12);
  TIM1->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E; // Habilitar captura nos canais 1 e 2

  // Configurar o modo do encoder
  TIM2->SMCR = 3;  // Modo de encoder usando os canais TI1 e TI2

  // Habilitar o Timer 2
  TIM2->CR1 |= TIM_CR1_CEN;

  printf("TIM2->CR1: %X\n", TIM2->CR1);      // Configurações de controle do timer
  printf("TIM2->SMCR: %X\n", TIM2->SMCR);    // Configurações de controle do modo do timer
  printf("TIM2->CCMR1: %X\n", TIM2->CCMR1);  // Configurações de captura/comparação do canal 1
  printf("TIM2->CCMR2: %X\n", TIM2->CCMR2);  // Configurações de captura/comparação do canal 2
  printf("TIM2->CCER: %X\n", TIM2->CCER);    // Configurações de controle dos canais de captura/comparação
  printf("TIM2->PSC: %X\n", TIM2->PSC);      // Prescaler do timer
  printf("TIM2->ARR: %X\n", TIM2->ARR);      // Valor de recarga automática (Auto-Reload Register)
  printf("TIM2->CNT: %X\n", TIM2->CNT);      // Valor do contador do timer
  printf("TIM2->AFR: %X\n", GPIOA->AFR[0]);
  printf("TIM2->AFR: %X\n", GPIOB->AFR[0]);

} 

void Encoder::init_enc_timer3()   // PA_6 PB_5
{
  RCC->APB2ENR |= RCC_APB1LENR_TIM3EN;
  RCC->AHB1ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN;

  GPIOA->MODER &= ~GPIO_MODER_MODE6; // Tentar ~GPIO_MODER_MODE6_Msk
  GPIOB->MODER &= ~GPIO_MODER_MODE5; // Tentar ~GPIO_MODER_MODE5_Msk

  GPIOA->MODER |= GPIO_MODER_MODE6_1; 
  GPIOB->MODER |= GPIO_MODER_MODE5_1;

  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;
  GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;

  GPIOA->AFR[0] |= (1 << GPIO_AFRL_AFSEL6_Pos);
  GPIOB->AFR[0] |= (1 << GPIO_AFRL_AFSEL5_Pos);

  TIM3->CR1 = 0;
  TIM3->CR2 = 0;
  TIM3->PSC = 0;
  TIM3->ARR = 0xFFFF;
  TIM3->RCR = 0;

  TIM3->CCMR1 = TIM_CCMR1_CC1S_0 | (0x00 << 4) | TIM_CCMR1_CC2S_0 | (0x00 << 12);
  TIM3->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;
  TIM3->DIER = 0;

  TIM3->SMCR = 3;
  TIM3->CR1 = TIM_CR1_CEN;
}