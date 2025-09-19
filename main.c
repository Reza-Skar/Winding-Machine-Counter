#include <mega8.h>
#include <stdio.h>
#include <delay.h>
#include <stdlib.h>

#define one     PINB.0 == 0
#define two     PINB.1 == 0
#define three   PINB.2 == 0

#define RED_on      PORTB.3 = 0;
#define GREEN_on    PORTB.4 = 0;
#define BLUE_on     PORTB.5 = 0;
#define RED_off      PORTB.3 = 1;
#define GREEN_off    PORTB.4 = 1;
#define BLUE_off     PORTB.5 = 1;

eeprom unsigned int a;

void main(void)
{
unsigned char seg[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
int x = 0,r = 0,c = 1;
int hezargan = 0;
int sadgan = 0;
int dahgan = 0;
int yekan = 0;

if(a==0xFFFF) 
 {
    a = 0x0000;
 }
// Port B initialization : Bit7=In Bit6=In Bit5=Out Bit4=Out Bit3=Out Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=P Bit6=P Bit5=1 Bit4=1 Bit3=1 Bit2=P Bit1=P Bit0=P 
PORTB=(1<<PORTB7) | (1<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

// Port C initialization : Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit6=P Bit5=P Bit4=P Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(1<<PORTC6) | (1<<PORTC5) | (1<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization : Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(0<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=P Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(1<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
            
while (1)
    {  
      if (x == 0 && one)
        {
            x = 1;
        }         
      if (x == 1 && three)
        {
            x = 4;
        }
      if (x == 1 && two)
        {
            x = 2;
        }
      if (x == 2 && three)
        {
            x = 1;
            r++;
        }
      if (x == 2 && one)
        {
            x = 1;
        }
      if (x == 0 && three)
        {
            x = 4;
        }
      if (x == 4 && one)
        {
            x = 1;
        }
      if (x == 1 && three)
        {
            x = 4;
        }
      if (x == 4 && two)
        {
            x = 5;
        }
      if (x == 5 && one)
        {
            x = 1;
            r--;
        }
      if (x == 5 && three)
        {
            x = 4;
        }
        
      if (PINB.6 == 0)
        {
            a = r; 
        }  
      if (PINB.7 == 0)
        {
            a = 100;
        }
      if (PINC.4 == 0)
        {
            r = 0;
        }
      if (PINC.5 == 0)
        {
            a = 160;
        }  
        
     if (r < a)
        {
            RED_off
            BLUE_on
            GREEN_off
        }
     else
        {
          if (r == a)
            {
                GREEN_on
                BLUE_off
                RED_off
            }      
          else
            {
              if (r > a)
                {
                    BLUE_off
                    RED_on
                    GREEN_off
                }     
              else
                {
                    RED_off
                    BLUE_off
                    GREEN_off
                }
            }
        }
      
      if (r > 9999)
        {
            r = 0;
        }    
      

      
      hezargan=r/1000;
      sadgan=(r%1000)/100;
      dahgan=(r%100)/10;
      yekan=r%10;
      
      switch (c)
      {
            case 1:
                PORTC.0 = 1; PORTC.1 = 1; PORTC.2 = 1; PORTC.3 = 0;
                PORTD=seg[yekan];
                break;
                
            case 2:
                PORTC.0 = 1; PORTC.1 = 1; PORTC.2 = 0; PORTC.3 = 1;
                PORTD=seg[dahgan];
                break;
                
            case 3:
                PORTC.0 = 1; PORTC.1 = 0; PORTC.2 = 1; PORTC.3 = 1;
                PORTD=seg[sadgan];
                break;
                
            case 4:
                PORTC.0 = 0; PORTC.1 = 1; PORTC.2 = 1; PORTC.3 = 1;
                PORTD=seg[hezargan];
                break;
      }              
      c++;
      if(c > 4) c = 1;  
    }
}
