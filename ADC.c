/* Configuración del módulo ADC */
#include "lib/include.h"

extern void Configuracion_ADC0(void)
{
    // 1. Inicializar el módulo 0 del reloj del ADC RCGCADC pag. 352
    SYSCTL-> RCGCADC =(1<<0);
    // 2. Habilitando el puerto E y D en base del reloj pag. 340
    SYSCTL -> RCGCGPIO |= (0<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(0<<0);
    // 3. Habilitar los pines como I/O 0-entrada y 1 - salida pag. 801
    GPIOE_AHB-> DIR = (0<<1); // PE1 - Canal 2  
    GPIOD_AHB-> DIR = (0<<3)|(0<<1); //PD3 - Canal 4, PD1 - Canal 6
    // 4. Habilitar la función alternativa pag. 672
    GPIOE_AHB -> AFSEL = (1<<1); // PE1 - Canal 2 
    GPIOD_AHB -> AFSEL = (1<<3)|(1<<1); //PD3 - Canal 4, PD1 - Canal 6
    // 5. Deshabilitación del modo digital pág. 683  
    GPIOE_AHB -> DEN =  (0<<1); // PE1 - Canal 2  
    GPIOD_AHB -> DEN = (0<<3)|(0<<1); //PD3 - Canal 4, PD1 - Canal 6
    // 6. GPIOCTL registro combinado con el GPIOAFSEL para funcion alternativa 
    GPIOE_AHB -> PCTL = GPIOE_AHB -> PCTL & (0xFFFFFF0F); //
    GPIOD_AHB -> PCTL = GPIOD_AHB -> PCTL & (0xFFFF0F0F);  //
    // 7. Habilitar lo analogico pag. 687
    GPIOE_AHB -> AMSEL =  (1<<1);  // PE1 - Canal 2  
    GPIOD_AHB -> AMSEL = (1<<3)|(1<<1); //PD3 - Canal 4, PD1 - Canal 6
    // 8. Velocidad de conversión 1 millon de muestras por segundo pág. 891 (7)
    ADC0->PC =(0<<3)|(1<<2)|(1<<1)|(0<<0); //1 Msps
    // 9. Prioridad de los secuenciadores pag. 841
                // 3 2 1 0
    ADC0->SSPRI = 0x0231; // 0 mayor prioridad 
    // 10. Control de la activacion de los secuenciadores sec 3, sec 0, sec 2 pag. 834
    ADC0 ->ACTSS = (0<<3)|(0<<2)|(0<<1)|(0<<0);
    // 11. Selección del evento que activa la conversión trigger pag. 834
    ADC0->EMUX = (0x0000); //Default 
    /*AGREGAR (GPIOADCCTL) Como colocar esa cosa de los botones*/  //PAG 690
    // 12. Define las entradas analógicas con el canal y secuenciador seleccionado Pag. 867
    ADC0 ->SSMUX3 = 0x2; // PE1 - Canal 2  
    ADC0 ->SSMUX0 = 0x00000046; //PD3 - Canal 4, PD1 - Canal 6
    // 13. Configurar el bit de control de muestreo y la interrupción
    ADC0 -> SSCTL0 = (1<<2)|(1<<1)|(1<<5)|(1<<6); //MUX 0 pag 853
    ADC0 -> SSCTL3 =  (1<<2)|(1<<1);              //MUX 3 PAG 856
    // 14. ADC Interrupciones pag. 825 
    ADC0 -> IM |= (1<<3); 
    ADC0 -> IM |= (1<<0); 
    ADC0 -> IM |= (1<<2); 
    // 10. Control de la activacion de los secuenciadores sec 3, sec 0, sec 2 pag. 821 
    ADC0 ->ACTSS = (0<<1)|(1<<2)|(1<<0)|(1<<3);
    ADC0 ->PSSI =  (1<<2)|(1<<0)|(1<<3);
}

extern void ADC0_In(uint16_t *Result,uint16_t *duty)
{
    //ADC0 -> PSSI = 0x00000004; 
    while ((ADC0->RIS&0x04)==0){}; //espera al convertidor 
    Result[0]= ADC0 ->SSFIFO2&0xFFF; 
    Result[1]= ADC0 ->SSFIFO2&0xFFF; 
    Result[2]= ADC0 ->SSFIFO2&0xFFF; 
    duty[0] = 50000-(Result[0]*5000)/4096;
    duty[1] = 50000-(Result[1]*5000)/4096;
    duty[2] = 50000-(Result[2]*5000)/4096;
    ADC0 ->ISC = 0x0004;
}
