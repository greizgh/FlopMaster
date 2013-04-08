#define F_CPU 16000000UL
#define BAUD 500000
#include <util/setbaud.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
  
static void uart_init() {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8-bit data
    UCSR0B = _BV(RXEN0);   // Enable RX
}
static void timer_init(){
    //Enable CTC with CK/8 prescaler
    TCCR0A |= _BV(WGM01);
    TCCR0B |= _BV(CS01);
    //Count until 80
    OCR0A = 0x50;
    //Enable OCR0A compare match interrupt
    TIMSK0 |= _BV(OCIE0A);
}
typedef struct FlopStatus FlopStatus;
struct FlopStatus {
    uint8_t max_pos[18];
    uint8_t cur_pos[18];
    uint8_t direction[18];
    uint16_t period[18];
    uint16_t tick[18];
};
volatile FlopStatus status={{0,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
ISR(TIMER0_COMPA_vect)
{
    if(status.period[2]>0){
        ++status.tick[2];
        if(status.tick[2] >= status.period[2]){
            status.tick[2]=0;
            if(status.cur_pos[2]>=status.max_pos[2]){
                PORTD |= _BV(PD3);
                status.direction[3]=1;
            }
            else if(status.cur_pos[2] <=0){
                PORTD &= ~_BV(PD3);
                status.direction[3]=0;
            }
            if(status.direction[3] == 0){
                ++status.cur_pos[2];
            }
            else {
                --status.cur_pos[2];
            }
            PORTD ^= _BV(PD2);
        }
    }
    if(status.period[4]>0){
        ++status.tick[4];
        if(status.tick[4] >= status.period[4]){
            status.tick[4]=0;
            if(status.cur_pos[4]>=status.max_pos[4]){
                PORTD |= _BV(PD5);
                status.direction[5]=1;
            }
            else if(status.cur_pos[4] <=0){
                PORTD &= ~_BV(PD5);
                status.direction[5]=0;
            }
            if(status.direction[5] == 0){
                ++status.cur_pos[4];
            }
            else {
                --status.cur_pos[4];
            }
            PORTD ^= _BV(PD4);
        }
    }
    if(status.period[6]>0){
        ++status.tick[6];
        if(status.tick[6] >= status.period[6]){
            status.tick[6]=0;
            if(status.cur_pos[6]>=status.max_pos[6]){
                PORTD |= _BV(PD7);
                status.direction[7]=1;
            }
            else if(status.cur_pos[6] <=0){
                PORTD &= ~_BV(PD7);
                status.direction[7]=0;
            }
            if(status.direction[7] == 0){
                ++status.cur_pos[6];
            }
            else {
                --status.cur_pos[6];
            }
            PORTD ^= _BV(PD6);
        }
    }
    if(status.period[8]>0){
        ++status.tick[8];
        if(status.tick[8] >= status.period[8]){
            status.tick[8]=0;
            if(status.cur_pos[8]>=status.max_pos[8]){
                PORTB |= _BV(PB1);
                status.direction[9]=1;
            }
            else if(status.cur_pos[8] <=0){
                PORTB &= ~_BV(PB1);
                status.direction[9]=0;
            }
            if(status.direction[9] == 0){
                ++status.cur_pos[8];
            }
            else {
                --status.cur_pos[8];
            }
            PORTB ^= _BV(PB0);
        }
    }
    if(status.period[10]>0){
        ++status.tick[10];
        if(status.tick[10] >= status.period[10]){
            status.tick[10]=0;
            if(status.cur_pos[10]>=status.max_pos[10]){
                PORTB |= _BV(PB3);
                status.direction[11]=1;
            }
            else if(status.cur_pos[10] <=0){
                PORTB &= ~_BV(PB3);
                status.direction[11]=0;
            }
            if(status.direction[11] == 0){
                ++status.cur_pos[10];
            }
            else {
                --status.cur_pos[10];
            }
            PORTB ^= _BV(PB2);
        }
    }
    if(status.period[12]>0){
        ++status.tick[12];
        if(status.tick[12] >= status.period[12]){
            status.tick[12]=0;
            if(status.cur_pos[12]>=status.max_pos[12]){
                PORTB |= _BV(PB5);
                status.direction[13]=1;
            }
            else if(status.cur_pos[12] <=0){
                PORTB &= ~_BV(PB5);
                status.direction[13]=0;
            }
            if(status.direction[13] == 0){
                ++status.cur_pos[12];
            }
            else {
                --status.cur_pos[12];
            }
            PORTB ^= _BV(PB4);
        }
    }
    if(status.period[14]>0){
        ++status.tick[14];
        if(status.tick[14] >= status.period[14]){
            status.tick[14]=0;
            if(status.cur_pos[12]>=status.max_pos[14]){
                PORTC |= _BV(PC1);
                status.direction[15]=1;
            }
            else if(status.cur_pos[14] <=0){
                PORTC &= ~_BV(PC1);
                status.direction[15]=0;
            }
            if(status.direction[15] == 0){
                ++status.cur_pos[14];
            }
            else {
                --status.cur_pos[14];
            }
            PORTC ^= _BV(PC0);
        }
    }
    if(status.period[16]>0){
        ++status.tick[16];
        if(status.tick[16] >= status.period[16]){
            status.tick[16]=0;
            if(status.cur_pos[16]>=status.max_pos[16]){
                PORTC |= _BV(PC3);
                status.direction[17]=1;
            }
            else if(status.cur_pos[16] <=0){
                PORTC &= ~_BV(PC3);
                status.direction[17]=0;
            }
            if(status.direction[17] == 0){
                ++status.cur_pos[16];
            }
            else {
                --status.cur_pos[16];
            }
            PORTC ^= _BV(PC2);
        }
    }
}
char uart_getchar() {
    loop_until_bit_is_set(UCSR0A, RXC0); // Wait until data exists.
    return UDR0;
}
void setup(){
    //Set ports in output mode
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
    //Clear outputs
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    //Enable serial
    uart_init();
    timer_init();
    sei();
}
void reset(){
    //Disable interrupt
    cli();
    //Clear output
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    //Go in reverse
    PORTD |= (_BV(PD3) | _BV(PD5) | _BV(PD7));
    PORTB |= (_BV(PB1) | _BV(PB3) | _BV(PB5));
    PORTC |= (_BV(PC1) | _BV(PC3));
    //Pulse step pins
    for(int track=0;track<80;track++){
        PORTD |= (_BV(PD2) | _BV(PD4) | _BV(PD6));
        PORTD &= ~(_BV(PD2) | _BV(PD4) | _BV(PD6));
        PORTB |= (_BV(PB0) | _BV(PB2) | _BV(PB4));
        PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB4));
        PORTC |= (_BV(PC0) | _BV(PC2));
        PORTC &= ~(_BV(PC0) | _BV(PC2));
        _delay_ms(10);
    }
}
int main() { 

    setup();
    
    char input;

    for(;;){
        input = uart_getchar();
        if(input!=100) {
            char p1 = uart_getchar();
            char p2 = uart_getchar();
            uint16_t period = (p1 &0x00ff) | (p2 & 0xff00);
            status.period[(uint8_t)input]=(period);
        }
        else {
            reset();
            break;
        }
    }

    return 0;
}
