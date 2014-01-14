#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

void init_osc();

int main(int argc, char** argv) {
    init_osc();
    //CMCON0bits.CM = 0b111;//disable comparators
    //TRISAbits.TRISA0 = 0;//output
    //PORTAbits.RA0 = 0;
    //ANSELbits.ANS0 = 0;//digital

    //OPTION_REGbits.T0CS = 1;//t0 transitions on f_osc/4
    //OPTION_REGbits.PSA = 0;//sw prescaler assigned to t0
    //OPTION_REGbits.PS = 0b000; //http://puu.sh/6kre1.png

    //ALL OPERATIONS WRITING TO TMR0 WILL CLEAR SOFTWARE PRESCALER
    //set tmr1 and tmr1if before enabling interrupts

    //INTCONbits.GIE = 1; //global interrupts
    //INTCONbits.PEIE = 1; //enable periph interrupts
    //INTCONbits.T0IE = 1; //enable t0 overflow interrupt
    //INTCONbits.T0IF = 0; //t0 interrupt flag
    //PIE1bits.TMR1IE = 1; //enable peripheral t1 interrupt
    //PIR1bits.TMR1IF = 0; //t1 overflow flag

    //T1CONbits.T1CKPS = 0b00;//11 = 1:8, 10 = 1:4, etc
    //T1CONbits.TMR1ON = 1;
    return (EXIT_SUCCESS);
}


void init_osc(){
    OSCCONbits.SCS = 1;//use internal osc for sys clock
    OSCCONbits.HTS = 1;//hfq osc is
    OSCCONbits.IOSCF = 0b111; //f_osc = 8mhz
    // 111 = 8mhz
    // 110 = 4mhz
    // 101 = 2mhz
    // 100 = 1mhz
    // 011 = 500khz
    // 010 = 250khz
    // 001 = 125khz
    // 000 = 31khz (lfintosc)
}