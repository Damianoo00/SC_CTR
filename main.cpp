/**
 * @file main.cpp
 * @author Damian Płaskowicki (damian.plaskowicki.stud@pw.edu.pl)
 * @brief Ciuk Controler to set and fix voltage from Super Capacitor
 * @version 0.1
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>
#include "../include/uart.h"
#include "../include/PWM.h"
#include "../include/converters.h"

/**
 * @brief define or remove correct line to switch any mode {#define [param]}
 * @param LOG define to enable logging
 *
 */
#define LOG

/*** UART params ***/
constexpr long BAUD = 9600;
constexpr int TIMEOUT = 10;

/*** PINOUT ***/
#define VOLT_SENSOR A0
#define SC_OUTPUT 6

/*** SC params ***/
constexpr int Vs = 2500; // mV
constexpr int Vo = 5000; // mV

void setup()
{
  uart_begin(BAUD, TIMEOUT);
  PWM_begin(SC_OUTPUT);
}

void loop()
{
  int duty = GetCukDuty(Vo, Vs);
  PWM_write(SC_OUTPUT, duty);

#ifdef LOG
  /************************** Set header and params to log **********************************/
  const String header = "time,duty";
  const long log_parametrs[] = {millis(), duty};
  /********************************************************************************************/

  const int NumOfParams = sizeof(log_parametrs) / sizeof(log_parametrs[0]);
  log_uart(header, log_parametrs, NumOfParams);
#endif
}