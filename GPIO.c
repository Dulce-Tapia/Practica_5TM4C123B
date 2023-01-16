#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    SYSCTL->RCGCGPIO |=(1<<3); 
    GPIOD->LOCK= 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIOD->CR = 0x1F;           // allow changes to PF4-0
    GPIOD->AMSEL = 0x00;        // 3) disable analog on PF
    GPIOD->PCTL = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIOD->DIR = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
    GPIOD->AFSEL = 0x00;        // 6) disable alt funct on PF7-0
    GPIOD->PUR = 0x11;          // enable pull-up on PF0 and PF4
    GPIOD->DEN = 0x1F;          // 7) enable digital I/O on PF4-0

    SYSCTL->RCGCGPIO |=(1<<4); 
    GPIOE->LOCK= 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIOE->CR = 0x1F;           // allow changes to PF4-0
    GPIOE->AMSEL = 0x00;        // 3) disable analog on PF
    GPIOE->PCTL = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIOE->DIR = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
    GPIOE->AFSEL = 0x00;        // 6) disable alt funct on PF7-0
    GPIOE->PUR = 0x11;          // enable pull-up on PF0 and PF4
    GPIOE->DEN = 0x1F;          // 7) enable digital I/O on PF4-0

    SYSCTL->RCGCGPIO |=(1<<1); 
    GPIOB->LOCK= 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIOB->CR = 0x1F;           // allow changes to PF4-0
    GPIOB->AMSEL = 0x00;        // 3) disable analog on PF
    GPIOB->PCTL = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIOB->DIR = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
    GPIOB->AFSEL = 0x00;        // 6) disable alt funct on PF7-0
    GPIOB->PUR = 0x11;          // enable pull-up on PF0 and PF4
    GPIOB->DEN = 0x1F;          // 7) enable digital I/O on PF4-0
}

extern void Delay(void)
{
  unsigned long volatile time;
  time = 1600000;
  while(time)
  {
		time--;
  }
}