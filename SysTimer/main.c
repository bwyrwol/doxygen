/** @file main.c
  *  
  * @brief Plik glowny programu
  *
  * @author B.W.
  * @date 2024/11/20
  *
  */

#include <avr/io.h>
#define F_CPU 14745600UL ///< definicja czestotliwosci rezonatora kwarcowego
#include "systimer.h"

void systimer_callback(void) /* wywolanie funkcji callback */
{
  PORTD ^= 0b11000000; /* przy kazdym wywolaniu negowane sa bity PD7 i PD6 */
}

int main(void)
{

  DDRD |= 0b11000000; /* dla testow wykorzystane zostana wyprowadzenia PD7 i PD6 */
  PORTD |= 0b11000000; /* mozna do nich podlaczyc np. diody LED */

  systimer_init(231); /* wywolanie funkcji inicjalizujacej SysTimer 
                         z przykladowa wartoscia (okresla co jaki czas w ms
                         wywolywana bedzie funkcja systimer_callback()) */
  
  while (1) /* petla nieskonczona */
  {
  }
}
