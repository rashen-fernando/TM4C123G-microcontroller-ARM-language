/* This is a timer interrupt example code of TM4C123 Tiva C Launchpad  https://microcontrollerslab.com/introduction-tiva-tm4c123g-launchpad/ */
/* Generates a delay of one second using Timer1A interrupt handler routine */
#include "TM4C123.h" // Device header file for Tiva Series Microcontroller
#define Green (1<<3) // PF3 pin of TM4C123 Tiva Launchpad, Green LED
void Time1A_1sec_delay(void);
int main(void)
{
/*Initialize PF3 as a digital output pin */
SYSCTL->RCGCGPIO |= 0x20; // turn on bus clock for GPIOF
GPIOF->DIR |= Green; // set Green pin as a digital output pin
GPIOF->DEN |= Green; // Enable PF2 pin as a digital pin
Time1A_1sec_delay();
while(1)
{
// do nothing wait for the interrupt to occur
}
}
/* Timer1 subtimer A interrupt service routine */
void TIMER1A_Handler()
{
if(TIMER1->MIS & 0x1)
GPIOF->DATA ^= Green; /* toggle Green LED*/
TIMER1->ICR = 0x1; /* Timer1A timeout flag bit clears*/
}
void Time1A_1sec_delay(void)
{
SYSCTL->RCGCTIMER |= (1<<1); /*enable clock Timer1 subtimer A in run mode */
TIMER1->CTL = 0; /* disable timer1 output */
TIMER1->CFG = 0x4; /*select 16-bit configuration option */
TIMER1->TAMR = 0x02; /*select periodic down counter mode of timer1 */
TIMER1->TAPR = 125-1; /* TimerA prescaler value */
TIMER1->TAILR = 128000-1 ; /* TimerA counter starting count down value */
TIMER1->ICR = 0x1; /* TimerA timeout flag bit clears*/
TIMER1->IMR |=(1<<0); /*enables TimerA time-out interrupt mask */
TIMER1->CTL |= 0x01; /* Enable TimerA module */
NVIC->ISER[0] |= (1<<21); /*enable IRQ21 */
}
