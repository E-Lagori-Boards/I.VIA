#include "project.h"
#include "varmic.h"
#include "stdio.h"


/********************************
 ***START printf() ACCOMODATION***
 *********************************/
 int _write(int file, char *ptr, int len)
 {
     (void) file ;
     int i ;
     for (i = 0 ; i < len ; i++) {
         UART_UartPutChar(*ptr++) ;
     }
     return len ;
 }
/********************************
 ****END printf() ACCOMODATION****
 *********************************/


#define gain 18

#define ARRSIZE 256
 
# define I1  0
# define I2  1
# define I3  2
# define I4  3
# define I5  4
# define I6  5
# define I7  6
# define I8  7
# define I9  8
# define I10 9
# define I11 10
# define I12 11
# define I13 12
# define I14 13
# define I15 14
# define I16 15

void setmux(int a){
    switch(a){
        case  I1:    S3_Write(0);   S2_Write(0);    S1_Write(0);    S0_Write(0);     break;
        case  I2:    S3_Write(0);   S2_Write(0);    S1_Write(0);    S0_Write(1);     break;
        case  I3:    S3_Write(0);   S2_Write(0);    S1_Write(1);    S0_Write(0);     break;
        case  I4:    S3_Write(0);   S2_Write(0);    S1_Write(1);    S0_Write(1);     break;
        case  I5:    S3_Write(0);   S2_Write(1);    S1_Write(0);    S0_Write(0);     break;
        case  I6:    S3_Write(0);   S2_Write(1);    S1_Write(0);    S0_Write(1);     break;
        case  I7:    S3_Write(0);   S2_Write(1);    S1_Write(1);    S0_Write(0);     break;
        case  I8:    S3_Write(0);   S2_Write(1);    S1_Write(1);    S0_Write(1);     break;
        case  I9:    S3_Write(1);   S2_Write(0);    S1_Write(0);    S0_Write(0);     break;
        case I10:    S3_Write(1);   S2_Write(0);    S1_Write(0);    S0_Write(1);     break;
        case I11:    S3_Write(1);   S2_Write(0);    S1_Write(1);    S0_Write(0);     break;
        case I12:    S3_Write(1);   S2_Write(0);    S1_Write(1);    S0_Write(1);     break;
        case I13:    S3_Write(1);   S2_Write(1);    S1_Write(0);    S0_Write(0);     break;
        case I14:    S3_Write(1);   S2_Write(1);    S1_Write(0);    S0_Write(1);     break;
        case I15:    S3_Write(1);   S2_Write(1);    S1_Write(1);    S0_Write(0);     break;
        case I16:    S3_Write(1);   S2_Write(1);    S1_Write(1);    S0_Write(1);     break;
    }
}

uint8 count;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    I2CM_Start();
    UART_Start();
    CTRL_Write(0);
    ADC_Start();
    VmM_4_10(22);
//    setGain(gain);
//    presentGain();
    volatile int16 result[ARRSIZE];
    float sample,volt; 
    uint32 RDACval0=0, RDACval1=0;
    int i;
//    ADC_Start();
    count = 0;
    setmux(I2);
    ADC_StartConvert();
    int cnt = 0;
    char c;
    
    printf("Initialization Done\n");
    
    for (;;)
    {
        c = UART_UartGetChar(); 
        if( c == 'U'){
            printf("INC_GAIN: %d. \n",(int)incGain(1));
            printf("Updated Gain: %d.\n", (int)presentGain());
        }
        if(c == 'D'){
            printf("DEC_GAIN: %d. \n",(int)decGain(1));
            printf("Updated Gain: %d.\n", (int)presentGain());
        }
        
        if(c == 'A'){
            printf("Gain Chnage\n");
            Write_RDAC(0, 0);
            Write_RDAC(1, 0);
            RDACval0 = Readback_RDAC(0);
            RDACval1 = Readback_RDAC(1);
            printf("RDAC0 Val is: %ld\n", RDACval0);
            printf("RDAC1 Val is: %ld\n", RDACval1);
        }
        if(c == 'B'){
            while(1){
                sample = ADC_GetResult16(0);
                volt = ADC_CountsTo_Volts(0, sample);
                printf("ADC val: %d\n", (int)(volt*1000));
            }
        }
        
//        if(0u != ADC_IsEndConversion(ADC_RETURN_STATUS)){
//            ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
//             
//                result[cnt] = (ADC_GetResult16(0) - 1024);
//                cnt = (cnt+1)%ARRSIZE;
//        }
//        if (cnt == 0){
//            for(int i = 0; i<ARRSIZE;i++)
//                printf("%d\n", result[i]);
//        }
    }
}

