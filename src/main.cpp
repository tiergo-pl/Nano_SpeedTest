#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <avr/builtins.h>

#define MAIN_CLOCK_TICK 10
#define LED_BUILTIN PB5
#define SQUARE_OUT PB2
#define DEBUG_PIN1 PB1

#define PERIOD_16BIT 10000
#define PERIOD_CORRECTION_16BIT 0
#define PERIOD_8BIT 100

volatile uint8_t sysClk8Master, sysClk8, sysClk8Prev;
volatile uint16_t sysClk16Master, sysClk16, sysClk16Prev;

void timerInit(void)
{
  OCR2A = 2 * MAIN_CLOCK_TICK - 1;                    // reset Timer2 at 2 * MAIN_CLOCK_TICK
  TCCR2A = 0b00000010;                                //((1<<WGM21) | (0<<WGM20));        // Timer2 CTC mode
  TCCR2B = ((0 << CS22) | (1 << CS21) | (0 << CS20)); // clk/8
  TIMSK2 = (1 << OCIE2A);                             // Timer/Counter Interrupt Mask
}
void portInit()
{
  DDRB |= _BV(SQUARE_OUT) | _BV(DEBUG_PIN1) | _BV(LED_BUILTIN);
  PORTB &= ~(_BV(SQUARE_OUT) | _BV(DEBUG_PIN1) | _BV(LED_BUILTIN));
}

ISR(TIMER2_COMPA_vect) // TIMER2 interrupt
{
  PORTB |= _BV(DEBUG_PIN1);
  sysClk8Master++;
  PORTB &= ~_BV(DEBUG_PIN1);
  PORTB |= _BV(DEBUG_PIN1);
  sysClk16Master++;
  PORTB &= ~_BV(DEBUG_PIN1);
}

// main starts here =====================================================================================================
// main starts here =====================================================================================================
// main starts here =====================================================================================================
int main()
{
  timerInit();
  portInit();

  sei();

  // MAIN PROGRAM LOOP =====================================================================================================
  // MAIN PROGRAM LOOP =====================================================================================================
  // MAIN PROGRAM LOOP =====================================================================================================
  // MAIN PROGRAM LOOP
  while (1)
  {
    
    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {

      sysClk8 = sysClk8Master;
      sysClk16 = sysClk16Master;
    }
    
/*
    for (uint8_t i = 0; i < 10; i++)
    {
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      __builtin_avr_delay_cycles(10);
    }
    */

    int16_t diff = sysClk16 - sysClk16Prev - PERIOD_16BIT;
    if (diff >= 0)
    {
      sysClk16Prev = sysClk16 + diff + PERIOD_CORRECTION_16BIT;
      PINB |= _BV(LED_BUILTIN); // writing to PINx toggles output
    }
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
    PORTB |= _BV(SQUARE_OUT);
    PORTB &= ~_BV(SQUARE_OUT);
  }
}
