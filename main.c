#include <18F4620.h>
#Device adc =10
#include <stdlib.h>

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(c)
#use fast_io(b)
#use fast_io(d)



long optenerVoltaje(float valorVoltaje){
    long rango=0;
    if(valorVoltaje>0.0 && valorVoltaje<=0.5){
       rango=1;
    }
    else{
        if(valorVoltaje>0.5 && valorVoltaje<=1.0){
           rango=2;
        }
        else{
            if(valorVoltaje>1.0 && valorVoltaje<=1.5){
               rango=4;
            }
            else{
                if(valorVoltaje>1.5 && valorVoltaje<=2.0){
                   rango=8;
                }
                else{
                    if(valorVoltaje>2.0 && valorVoltaje<=2.5){
                       rango=16;
                    }
                    else{
                        if(valorVoltaje>2.5 && valorVoltaje<=3.0){
                           rango=32;
                        }
                        else{
                            if(valorVoltaje>3.0 && valorVoltaje<=3.5){
                               rango=64;
                            }
                            else{
                                if(valorVoltaje>3.5 && valorVoltaje<=4.0){
                                   rango=128;
                                }
                                else{
                                    if(valorVoltaje>=4.0 && valorVoltaje<=4.5){
                                       rango=256;
                                    }
                                    else{
                                        if(valorVoltaje>4.5 && valorVoltaje<=5.0){
                                           rango=512;
                                        }
                                    }                                    
                                }
                            }
                        }
                    }
                }         
            }
        }
    }
    return rango;
}
int main(){
   setup_oscillator(OSC_16MHZ);
   
   setup_adc_ports(AN0_TO_AN1);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0xC);
   
   float voltaje1=0,voltaje2=0;
   long voltajeDigital=0;

   while(1){
       set_adc_channel(0);
       voltaje1=read_adc();
       voltaje1=(voltaje1*5)/1024;
       voltajeDigital=optenerVoltaje(voltaje1);
       
       output_b(voltajeDigital);
       output_c(voltajeDigital>>8);
           
       set_adc_channel(1);
       voltaje2=read_adc();
       voltaje2=(voltaje2*5)/1024;
       voltajeDigital=optenerVoltaje(voltaje2);
       
       output_d(voltajeDigital);
       output_e(voltajeDigital>>8);
    
   }
}
