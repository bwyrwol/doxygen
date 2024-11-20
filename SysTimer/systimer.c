/** @file SysTimer.c 
  *
  * @brief Plik implementacyjny biblioteki SysTimer
  *
  * W pliku zawarto implementacje wszystkich funkcji biblioteki SysTimer.
  * Inicjalizacja licznika odbywa sie automatycznie w oparciu o wartosc
  * podanego czasu - interwalu pomiedzy wystapieniem kolejnych przerwan.
  *
  */

#include "systimer.h"

/**
  *
  * @brief Tablica wartosci dzielnika czestotliwosci sygnalu zegarowego dla 
  *        licznika Timer1
  *
  * Stablicowane wartosci dzielnika czestotliwosci licznika Timer1. Wartosci
  * umieszczone jako stale w pamieci programu FLAS.
  */
const uint16_t prescaler_div[5] PROGMEM = {1, 8, 64, 256, 1024};

uint8_t systimer_init(uint16_t systick)
{
  uint64_t _OCR1A;
  uint8_t  index = 0;
  
  /* wyszukiwanie wartosci dzielnika */
  do
  {
    _OCR1A = (((F_CPU / pgm_read_word(&prescaler_div[index]))) * systick) / 1000ULL;
  } while ((_OCR1A > 65535) && (index++ < 5));
  
  /* sprawdzenie jak dokladnie udalo sie dobrac parametry licznika */
  uint8_t error_code = 0;
  if (index >= 5)
    error_code = SYSTIMER_ERROR_2; /* nie udalo sie znalezc dzielnika prescalera do odmierzania czasu */
  else if (((((F_CPU / pgm_read_word(&prescaler_div[index]))) * systick) / 1000ULL) != 0)
    error_code = SYSTIMER_ERROR_1; /* dla podanych wartosci czas odmierzany z przyblizeniem */
  else
    error_code = SYSTIMER_NO_ERROR; /* licznik skonfigurowany poprawnie*/
  
  if (error_code < SYSTIMER_ERROR_2) /* wlasciwa konfiguracja licznika Timer1 */
  {
    OCR1A = (uint16_t) _OCR1A;
    TIMSK |= (1 << OCIE1A); 
    sei();
    TCCR1B = (1 << WGM12) | (index + 1); /* start timer at index (1-5) prescaler */
  }  
  
  return error_code;
}

/**
  *
  * @brief Funkcja przerwania od licznika Timer1
  *
  * Funkcja obslugi przerwania od porownania licznika Timer1. Zawiera wywolanie
  * tzw. funkcji zwrotnej, ktora zdefiniowana w aplikacji bedzie wywolywana
  * cyklicznie co czas @c systick.
  *
  */
ISR(TIMER1_COMPA_vect)
{
  systimer_callback();
}