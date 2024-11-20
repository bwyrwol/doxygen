/** @file systimer.h
  *
  * @brief Plik naglowkowy biblioteki SysTimer
  *
  * W bibliotece zawarte zostaly podstawowe funkcji pozwalajace skonfigurowac
  * licznik Timer 1 mikrokontrolera w trybie CTC umozliwiajac generowanie
  * przerwania co okreslony interwal czasu (system tick).
  *
  * @note wersja testowa
  */

#ifndef SYSTIMER_H_
#define SYSTIMER_H_

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
/**
  * @brief Definicja czestotliwosci F_CPU
  */
#define F_CPU 14745600UL
#warning F_CPU is defined as 14745600UL
#endif

#define SYSTIMER_NO_ERROR 0   ///< Licznik skonfigurowany poprawnie
#define SYSTIMER_ERROR_1  1   ///< Licznik nie bedzie dokladnie odmierzac czasu
#define SYSTIMER_ERROR_2  2   ///< Nie udalo sie skonfigurowac licznika

/**
  * @brief Funkcja pozwalajaca skonfigurowac licznik Timer1 tak by pozwalal na generacje
  *        przerwania o okreslony czas.
  *
  * @param  systick watrosc czasu podana w [ms]
  * @return zwraca kod okreslajacy, czy licznik udalo sie poprawnie skonfigurowac
  *         i z jaka dokladnoscia bedzie odmierzany czas
  *
  * Przyklad wykorzystania
  * @code
  * #include "systimer.h"
  *
  * void main(void)
  * {
  *   systimer_init(100); // odmierzany interwal czasu 100ms
  *   
  *   while(1)
  *   {
  *   }
  * }
  *
  * void systimer_callback()
  * {
  *   // tutaj wpisac instrukcje, ktore beda wykonywane co 100ms
  * }
  * @endcode
  */
uint8_t systimer_init(uint16_t systick);

/**
  *
  * @brief Funkcja wywolywana w programie obslugi przerwania od Timer1
  *
  * Funkcja obslugi przerwania od porownania licznika Timer1. Zawiera wywolanie
  * tzw. funkcji zwrotnej, ktora zdefiniowana w aplikacji bedzie wywolywana
  * cyklicznie co czas @c systick.
  *
  */
void systimer_callback(void) __attribute__((weak));

/**
  * @todo <ul>
  *          <li> rozbudowac biblioteke o funkcje opozniajace (blokujaca i nieblokujaca),</li>
  *          <li> dopisac funkcje zerujaca licznik w dowolnej chwili.</li>
  *       </ul>
  * koniec
  */

#endif /* SYSTIMER_H_ */

