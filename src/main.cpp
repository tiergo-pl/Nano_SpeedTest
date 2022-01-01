#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <avr/builtins.h>

#define LED_BUILTIN PB5
#define SQUARE_OUT PB2
#define DEBUG_PIN1 PB1

#define SYS_FREQ 10000    // must be divisor of 250000
#define PERIOD_16BIT 5000 // in system clock ticks
#define PERIOD_8BIT 100
//#define F_CPU 8000000L //Uncoment if XTAL = 8 MHz

volatile uint8_t sysClk8Master, sysClk8, sysClk8Prev;
volatile uint16_t sysClk16Master, sysClk16, sysClk16Prev;

void timerInit(void)
{
  // divide F_CPU by 1600 - gives 10 kHz system clock
  TCCR2A = 0b00000010; //((1<<WGM21) | (0<<WGM20));        // Timer2 CTC mode
#if F_CPU == 16000000L
  TCCR2B = ((1 << CS22) | (0 << CS21) | (0 << CS20)); // prescaler clk/64 - 16 MHz clock
#endif
#if F_CPU == 8000000L
  TCCR2B = ((0 << CS22) | (1 << CS21) | (1 << CS20)); // prescaler clk/32 - 8 MHz clock
#endif
  OCR2A = (250000 / SYS_FREQ - 1); // count to 250000/SYS_FREQ (divide prescaled freq by 250000/SYS_FREQ)
  TIMSK2 = (1 << OCIE2A);          // Timer/Counter Interrupt Mask
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
  // PORTB &= ~_BV(DEBUG_PIN1);
  // PORTB |= _BV(DEBUG_PIN1);
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

    // some cpu consuming routine
    for (uint8_t i = 0; i < 100; i++)
    {
      // 4 positive pulses (16 cpu clocks)
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      PORTB |= _BV(SQUARE_OUT);
      PORTB &= ~_BV(SQUARE_OUT);
      //  and pause (also 16 cpu clocks)
      __builtin_avr_delay_cycles(16 - 3); // loop jump takes 3 cpu clks
    }

    int16_t diff = sysClk16 - sysClk16Prev - PERIOD_16BIT;
    if (diff >= 0)
    {
      sysClk16Prev = sysClk16 + diff;
      PINB |= _BV(LED_BUILTIN); // writing to PINx toggles output
    }

    // 10 pulses with f= F_CPU / 4
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
