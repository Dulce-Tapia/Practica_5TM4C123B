#include "lib/include.h"

extern void Configura_Reg_PWM0(uint16_t freq)
{    
    // Experimento 2 
    //Habilitar el reloj de modulo PWM0 pag 354
    SYSCTL->RCGCPWM |= (1<<0); 
    //Habilitar el reloj de GPIO Puerto B y E pag 340 pin 5
    SYSCTL->RCGCGPIO |= (1<<1)|(1<<4); 
    //Habilitar el divisor del reloj PWM pag 254 Nota *Se requiere dividir entre 8 para su capaidad
    SYSCTL -> RCC |= (1<<20)|(0<<19)|(1<<18)|(0<<17);  //No da los 50 Hz
    // Habilitar función alternativa  Control de registros ya sea por GPIO o Otros Pag 672
    GPIOB_AHB->AFSEL |= (1<<4)|(1<<7); // PB4 y PB7
    GPIOE_AHB->AFSEL |= (1<<4); // PE4  
    //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    // 4 indica que es PWM 
    GPIOB_AHB->PCTL |= (GPIOB_AHB->PCTL&0x0FF0FFFF) | 0x40040000; 
    GPIOE_AHB->PCTL |= (GPIOE_AHB->PCTL&0xFFF0FFFF) | 0x00040000; 
    // Salida de PWM 
    GPIOB_AHB->DIR |= (1<<4)|(1<<7); // PB4 y PB7
    GPIOE_AHB->DIR |= (1<<4); // PE4  
    // para decirle si es digital o no Pag 682
    GPIOB_AHB->DEN |= (1<<4)|(1<<7); // PB4 y PB7
    GPIOE_AHB->DEN |= (1<<4); // PE4  
    //Bloqueo y desbloqueo pag 1266, pag 1233 generadores de PWM 
    PWM0->_0_CTL = (0<<0);   
    PWM0->_1_CTL = (0<<0);  
    PWM0->_2_CTL = (0<<0);  
    //Pag 1248  
    PWM0->_0_GENB = 0x0000080C; //PWM1 trabaja con comparador B 
    PWM0->_1_GENA = 0x0000008C; //PWM2 trabaja con comparador A 
    PWM0->_2_GENA = 0x0000008C; //PWM4 trabaja con comparador A 
    //cuentas=fclk/fpwm  (20,000,000/8)=2500000 
    PWM0->_0_LOAD = (int)(2500000/freq); 
    PWM0->_1_LOAD = (int)(2500000/freq); 
    PWM0->_2_LOAD = (int)(2500000/freq); 
    PWM0->_0_CMPB = 15000; //Ciclo de trabajo Nota *Regla de 3
    PWM0->_1_CMPA = 15000; 
    PWM0->_2_CMPA = 15000; 
    // Se activa el generador 0,1,2
    PWM0->_0_CTL = (1<<0);
    PWM0->_1_CTL = (1<<0);
    PWM0->_2_CTL = (1<<0);
    // habilitar el PWM3,PWM2,PWM4 pag 1248
    PWM0->ENABLE = (1<<1)|(1<<2)|(1<<4); 
}
