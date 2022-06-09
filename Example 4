/*Q1
/*PORTF PF0 and PF4 fall edge interrupt example*/
/*This GPIO interrupt example code controls green LED with switches SW1 and SW2 external interrupts */
#define DELAY 16000000
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *)0x4002551C))



#include "TM4C123.h" // Device header
int main(void)
{
SYSCTL_RCGCGPIO_R = 0x20;

/* PORTF0 has special function, need to unlock to modify */
GPIOF->LOCK = 0x4C4F434B; /* unlock commit register */
GPIOF->CR = 0x01; /* make PORTF0 configurable */
GPIOF->LOCK = 0; /* lock commit register */
/*Initialize PF3 as a digital output, PF0 and PF4 as digital input pins */
GPIOF->DIR &= (1<<4); /* Set PF4 as a digital input pins */
GPIOF->DIR |= (1<<3); /* Set PF3 as digital output to control green LED */
GPIOF->DIR |= (1<<1); /* Set PF1 as digital output to control red LED */
GPIOF->DIR |= (1<<2); /* Set PF2 as digital output to control blue LED */
GPIOF->DEN |= (1<<4)|(1<<3)|(1<<1) |(1<<2) ; /* make PORTF4-0 digital pins */
GPIOF->PUR |= (1<<4); /* enable pull up for PORTF4, 0 */

/* configure PORTF4, 0 for falling edge trigger interrupt */
GPIOF->IS &= (1<<4); /* make bit 4, 0 edge sensitive */
GPIOF->IBE &=(1<<4); /* trigger is controlled by IEV */
GPIOF->IEV |= (1<<4); /* rising edge trigger */
GPIOF->ICR |= (1<<4); /* clear any prior interrupt */
GPIOF->IM |= (1<<4); /* unmask interrupt */

/* enable interrupt in NVIC and set priority to 3 */
NVIC->IP[30] = 3 << 5; /* set interrupt priority to 3 */
NVIC->ISER[0] |= (1<<30); /* enable IRQ30 (D30 of ISER[0]) */

while(1)
{

}

}
/* SW1 is connected to PF4 pin, SW2 is connected to PF0. */
/* Both of them trigger PORTF falling edge interrupt */





void GPIOF_Handler(void)
{

volatile unsigned long ulLoop ;
volatile unsigned long red_light_seconds ;
volatile unsigned long green_light_seconds ;

SYSCTL->RCGCGPIO |= (1<<5); /* Set bit5 of RCGCGPIO to enable clock to PORTF*/


    while(1)
    {
      GPIOF->DATA &= ~(1<<1);//clear red
      GPIOF->DATA |= (1<<3);//green
      for(green_light_seconds=0;green_light_seconds<2;green_light_seconds++)
      {
        for ( ulLoop = 0; ulLoop < DELAY; ulLoop++)
        {
        }
      }
      GPIOF->DATA &= ~(1<<3);// clear green
      GPIOF->DATA &= ~(1<<1);//clear red
      GPIOF->DATA |= (1<<1);//red
      for(red_light_seconds=0;red_light_seconds<4;red_light_seconds++)
      {
        for ( ulLoop = 0; ulLoop < DELAY; ulLoop++)
        {
        }
      }
      GPIOF->DATA &= ~(1<<3);// clear green
      GPIOF->DATA &= ~(1<<1);//clear red
      GPIOF->ICR |= 0x10; /* clear the interrupt flag */
      if (GPIOF->MIS & 0x01) break;
     }   

}
