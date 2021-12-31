#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>

#define MAIN_CLOCK_TICK 10

void timer_init(void)
{
  OCR2A = 2 * MAIN_CLOCK_TICK - 1;                    // reset Timer2 at 2 * MAIN_CLOCK_TICK
  TCCR2A = 0b00000010;                                //((1<<WGM21) | (0<<WGM20));        // Timer2 CTC mode
  TCCR2B = ((0 << CS22) | (1 << CS21) | (0 << CS20)); // clk/8
  TIMSK2 = (1 << OCIE2A);                             // Timer/Counter Interrupt Mask
}



ISR(TIMER2_COMPA_vect) // TIMER2 interrupt
{
  //  PORTC |= _BV(debugPin1);
  mainClock_us++;
  //  PORTC &= ~_BV(debugPin1);
}

// main starts here =====================================================================================================
// main starts here =====================================================================================================
// main starts here =====================================================================================================
int main()
{
  timer_init();
  sei();

  // MAIN PROGRAM LOOP =====================================================================================================
  // MAIN PROGRAM LOOP =====================================================================================================
  // MAIN PROGRAM LOOP =====================================================================================================
  // MAIN PROGRAM LOOP
  while (1)
  {
    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
      mainClock_us_temp = mainClock_us;
    }
  }
}
