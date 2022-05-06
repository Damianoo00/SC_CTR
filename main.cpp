#include <Arduino.h>
#include "../include/uart.h"
#include "../include/PWM.h"
#include "../include/converters.h"

/*** SWITCHES
LOG - log duty
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
  int duty = get_Cuk_duty(Vo, Vs);
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