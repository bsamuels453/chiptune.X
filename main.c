#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 500000
#include <xc.h>

#include "main.h"
#include "tone.h"
#include "song.h"
#include "init.h"

static int sig_uptime = 0;
static float sig_period = 0;
#define INSTRUCT_SPEED 1000000

int main(int argc, char** argv) {
    init_osc();
    init_io();
    init_timers();
    play_tune();
    sig_uptime = 0;
    sig_period = 0;
    for(;;);
    return (EXIT_SUCCESS);
}

void play_tune(){
    for(unsigned int i=0; i<song_length; i++){
        if(song[i] == ' '){
            sig_uptime = 0;
            delay(beats[i]);
        }
        else{
            play_note(song[i], beats[i]);
        }
        delay(5);
    }
}

void delay(char beats){
    float realBeats = (float)beats/10f;
    float delay_time_sec = realBeats * (60f/(float)tempo);
    int delay_ms = (int)(delay_time_sec * 1000f);

    for(int i=0; i<delay_ms; i+=1){
        __delay_ms(1);
    }
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
    int period = (int)(INSTRUCT_SPEED/(1/time_high_s));
    sig_uptime = 0xFFFF - period;
    sig_period = time_high_s;
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
         TMR1 = 0xFFFF - (int)(INSTRUCT_SPEED/1000);
         PORTAbits.RA2 = 0;
    }
}