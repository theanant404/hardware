
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define CLOCK_FREQ 16000000U
#define PRESCALER 256
#define TICKS_PER_SEC (CLOCK_FREQ / PRESCALER)
#define MIN_PULSE_WIDTH 544
#define MAX_PULSE_WIDTH 2400

int servo1Pin = 11;
int servo2Pin = 3;

int clip(int val, int min, int max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

int map(int val, int in_low, int in_high, int out_low, int out_high)
{

    val = clip(val, in_low, in_high);
    
    return (val - in_low) * (out_high - out_low) / (in_high - in_low) + out_low;
}

void servo_write_us(int pin, int micro_secs)
{
    int ticks = (micro_secs * TICKS_PER_SEC) / 1000000; 
    if (pin == 11) {
        OCR2B = ticks;  
    } else if (pin == 3) {
        OCR2A = ticks; 
    }
}

void servo_write_angle(int pin, int angle)
{
    int pulse_width = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
        servo_write_us(pin, pulse_width);
}

int main()
{
    TCCR2B |= (1 << CS22); 

    TCCR2A |= (1 << WGM21) | (1 << WGM20);  // Enable Phase Correct PWM mode

    DDRB |= (1 << PB3); 
    DDRB |= (1 << PB4);  
    sei();

    while (1)
    {
        servo_write_us(servo1Pin, MIN_PULSE_WIDTH);
        servo_write_us(servo2Pin, MAX_PULSE_WIDTH);
        _delay_ms(1000);
        servo_write_us(servo1Pin, MAX_PULSE_WIDTH);
        servo_write_us(servo2Pin, MIN_PULSE_WIDTH);
        _delay_ms(1000);
        servo_write_angle(servo1Pin, 0);
        servo_write_angle(servo2Pin, 180);
        _delay_ms(1000);
        servo_write_angle(servo1Pin, 90);
        servo_write_angle(servo2Pin, 90);
        _delay_ms(1000);
        servo_write_angle(servo1Pin, 180);
        servo_write_angle(servo2Pin, 0);
        _delay_ms(1000);

        for (int angle = 180; angle >= 0; angle--)
        {
            servo_write_angle(servo1Pin, angle);
            servo_write_angle(servo2Pin, 180 - angle);
            _delay_ms(10);
        }
        _delay_ms(500);
        for (int angle = 0; angle <= 180; angle++)
        {
            servo_write_angle(servo1Pin, angle);
            servo_write_angle(servo2Pin, 180 - angle);
            _delay_ms(10);
        }
        _delay_ms(500);
    };
}
