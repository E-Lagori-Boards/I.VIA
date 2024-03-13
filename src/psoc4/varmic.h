#ifndef ELI_VMM_H
#define ELI_VMM_H
       
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
#include "digipot.h"    
    

unsigned addr,d_bit;
int VmM_RT = 10000,VmM_RC = 1000,VmM_RW = 40;
double VmM_NGain_1dB,VmM_NGain_dB,VmM_NGain,VmM_Gain_1dB,VmM_RWB,VmM_RAW,D2;
uint8_t txbuffer[8],D_1,D_2,ND_1,ND_2;
float Gain_dB_val,NGain_dB_val,Max_dB_val=28.43,Min_dB_val=-40.46;
int VmM_read_data;

float VmM_GainCal(uint8_t,uint8_t);

void VmM_4_10(int);

float setGain(float);//
void storeGain ();//
void restoreGain ();//
float incGain(float);//
float decGain(float);//
float amplify(float);//
float attenuate(float);//
float presentGain();//

void VmM_4_10(int address)
{
  chgBoardaddr(address);
}

float setGain(float Gain_dB){
        if (Gain_dB>28.43){
            D_1 = 255;
            D_2 = 0;
            Gain_dB_val = Max_dB_val;
            Write_RDAC(0,D_1);
            VmM_read_data = Write_RDAC(1,D_2);
            return (VmM_read_data)? 1:2;
        }
        else if (Gain_dB<-40.46){
            D_1 = 0;
            D_2 = 255;
            Gain_dB_val = Min_dB_val;
            Write_RDAC(0,D_1);
            VmM_read_data = Write_RDAC(1,D_2);
            return (VmM_read_data)? -1:2;
        }
            else{
                 float VmM_Gain_dB = Gain_dB;
//                 printf("VmM_Gain_dB: %d.\n",(int)VmM_Gain_dB);
                 float VmM_Gain = pow(10,(VmM_Gain_dB/20));
                 for(int D1 = 0;D1<256;D1++){
                        D2 = round(256-(256*(((VmM_Gain*VmM_RT)/(1+2*(VmM_RC/(((256.0- D1)/256.0)*VmM_RT+VmM_RW))))-VmM_RW)/VmM_RT));
                        if(D2<256 && D2>=0){
                                VmM_NGain_1dB = VmM_GainCal(D1,D2);
                                printf("VmM_NGain_1dB: %d.\n",(int)VmM_NGain_1dB);
                                VmM_Gain_1dB= round(VmM_Gain_dB* 10) / 10; 
                                printf("VmM_Gain_1dB: %d.\n",(int)VmM_Gain_1dB);
                                if(fabs(VmM_NGain_1dB - VmM_Gain_1dB)<0.3){
                                        D_1 = D1;
                                        D_2 = D2;
                                        Gain_dB_val = VmM_NGain_dB;
                                        break;
                                }
                        }
                }
                Write_RDAC(0,D_1);
                VmM_read_data = Write_RDAC(1,D_2);
                return (VmM_read_data)? 0:2;
                }
}  
float amplify(float amp_factor){float Amp_NGain=(Gain_dB_val)*amp_factor;float t= setGain(Amp_NGain);return t;}
float attenuate(float att_factor){float Att_NGain=(Gain_dB_val)/att_factor;float f= setGain(Att_NGain);return f;}
void storeGain (){
        StoreValue (0);
        StoreValue (1);
        ND_1 = D_1;
        ND_2 = D_2;
        NGain_dB_val = Gain_dB_val;
}
void restoreGain (){
        RestoreValue (0);
        RestoreValue (1);
        D_1 = ND_1;
        D_2 = ND_2;
        Gain_dB_val = NGain_dB_val;
}  
float incGain(float inc_dB){
        float Inc_Gain_dB_val = (Gain_dB_val) + inc_dB;
        float w = setGain(Inc_Gain_dB_val);
        return w ;
}  
float decGain(float dec_dB){
        float Dec_Gain_dB_val = (Gain_dB_val) - dec_dB;
        float x = setGain(Dec_Gain_dB_val);
        return x;
}
float VmM_GainCal(uint8_t D1,uint8_t D2){
        VmM_RWB = (((256.0- D2)/256.0)*VmM_RT+VmM_RW);
        VmM_RAW = (((256.0- D1)/256.0)*VmM_RT+VmM_RW);
        VmM_NGain = (VmM_RWB/VmM_RT)*(1+(2*(VmM_RC)/VmM_RAW));
        VmM_NGain_dB = (20*log10(VmM_NGain));
        VmM_NGain_1dB = round(VmM_NGain_dB* 10) / 10;
        return VmM_NGain_1dB;
}
float presentGain(){
        D_1 = Readback_RDAC(0);
        D_2 = Readback_RDAC(1);
        Gain_dB_val = VmM_GainCal(D_1,D_2);
        return Gain_dB_val;
}

#endif
