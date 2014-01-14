#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "main.h"
#include "tone.h"
#include "song.h"
#include "init.h"

static int sig_uptime = 0;

int main(int argc, char** argv) {
    init_osc();
    init_io();
    init_timers();
    play_tune();
    return (EXIT_SUCCESS);
}

void play_tune(){
    for(unsigned int i=0; i<song_length; i++){
        if(song[i] == ' '){
            delay(beats[i]);
        }
        else{
            play_note(song[i], beats[i]);
        }
        delay(5);
    }
}

void delay(char beats){
    float delay_time_sec = ((float)beats/10) * (1/(float)tempo);
    char delay_instructs = (int)(delay_time_sec * (1000000f/4)/256);

    //xx doesnt setting tmr0 clear the software prescaler?
    OPTION_REGbits.PS = 0b111;
    TMR0 = 0;
    while(TMR0 != delay_instructs);
}

void play_note(char note, char duration){
    float frequency;
    for(char i=0; i<num_notes; i++){
        if(notes[i] == note){
            frequency = tones[i];
            break;
        }
    }
    float time_high_s = 1f / (2 * frequency);
    int period = (int)(time_high_s * 250000);
    sig_uptime = 0xFFFF - period;
    delay(duration);
}



void interrupt int_t1(){
    PIR1bits.TMR1IF = 0;
    if(sig_uptime != 0){
        char state = PORTAbits.RA2;
        PORTAbits.RA2 = ~state;
        TMR1 = sig_uptime;
    }
    else{
         TMR1 = 0xFF05;
    }
}