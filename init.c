#include <xc.h>

void init_timers(){
    INTCONbits.GIE = 1; //global interrupts
    INTCONbits.PEIE = 1; //enable periph interrupts
    PIE1bits.TMR1IE = 1; //enable t1 overflow interrupt
    OPTION_REGbits.PSA = 0;//sw prescaler assigned to t0
    OPTION_REGbits.T0CS = 0; //timer0 clk src is f_osc/4
    TMR1 = 0xFF05; //check for new frequency at 1000hz
    T1CONbits.T1CKPS = 0b00;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;
}

void init_io(){
    CMCON0bits.CM = 0b111;//disable comparators
    TRISAbits.TRISA2 = 0;//output
    PORTAbits.RA2 = 0;
    ANSELbits.ANS2 = 0;//digital
}

void init_osc(){
    OSCCONbits.SCS = 1;//use internal osc for sys clock
    OSCCONbits.HTS = 1;//hfq osc is
    OSCCONbits.IOSCF = 0b100; //f_osc = 1mhz
    // 111 = 8mhz
    // 110 = 4mhz
    // 101 = 2mhz
    // 100 = 1mhz
    // 011 = 500khz
    // 010 = 250khz
    // 001 = 125khz
    // 000 = 31khz (lfintosc)
}