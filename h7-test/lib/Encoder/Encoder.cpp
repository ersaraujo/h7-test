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
  if (timer == TIM1)
    init_enc_timer1();
  else if (timer == TIM8)
    init_enc_timer8();
  else if (timer == TIM2)
    init_enc_timer2();
}

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

}

void Encoder::init_enc_timer8() // PC_6 PC_7 - REVISAR
{
  RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
  RCC->AHB1ENR |= RCC_AHB4ENR_GPIOCEN;

  GPIOC->MODER &= ~GPIO_MODER_MODE6;
  GPIOC->MODER |= GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1;

  GPIOC->OTYPER |= GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7;

  GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7;

  GPIOC->AFR[1] |= (1 << GPIO_AFRL_AFSEL6_Pos);
  GPIOC->AFR[1] |= (1 << GPIO_AFRL_AFSEL7_Pos);

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
}

void Encoder::init_enc_timer2()  // PA_5 PB_3 - LEITURA ERRADA
{
  RCC->APB2ENR |= RCC_APB1LENR_TIM2EN;
  RCC->AHB1ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN;

  GPIOA->MODER &= GPIO_MODER_MODE5;
  GPIOB->MODER &= GPIO_MODER_MODE3;

  GPIOA->MODER |= GPIO_MODER_MODE5_1; 
  GPIOB->MODER |= GPIO_MODER_MODE3_1;

  GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
  GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;

  GPIOA->AFR[1] |= (1 << GPIO_AFRL_AFSEL5_Pos);
  GPIOB->AFR[1] |= (1 << GPIO_AFRL_AFSEL3_Pos);

  TIM2->CR1 = 0;
  TIM2->CR2 = 0;
  TIM2->PSC = 0;
  TIM2->ARR = 0xFFFF;
  TIM2->RCR = 0;

  TIM2->CCMR1 = TIM_CCMR1_CC1S_0 | (0x00 << 4) | TIM_CCMR1_CC2S_0 | (0x00 << 12);
  TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;
  TIM2->DIER = 0;

  TIM2->SMCR = 3;
  TIM2->CR1 = TIM_CR1_CEN;

} 