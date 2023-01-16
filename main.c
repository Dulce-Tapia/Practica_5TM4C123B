#include "lib/include.h"

/* EXPERIMENTO 2
   Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
   junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
   cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo para 
   controlar la posición de tres servos sg90 o otros 
*/
 
int main(void)
{
    uint16_t Result[2];
    uint16_t duty[2];
    Configurar_PLL(_20MHZ); //Experimento 2 y 3  
    Configurar_GPIO();
    Configura_Reg_PWM0(50); //Configuro a 50Hz el pwm Experimento 2 y 3 
    
    while(1)
    { 
        //PARTE DEL EXPERIMENTO 2 
        ADC0_In(Result,duty); //llamada a la conversion por procesador
        PWM0->_0_CMPB = duty[0];
        PWM0->_1_CMPA = duty[1];
        PWM0->_2_CMPA = duty[2];
    }
}
