static int _readResolution = 10;
static int _ADCResolution = 10;
static int _writeResolution = 8;


static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
  Serial.println("map_resolution\tstart");
  if (from == to) {
        Serial.println("map_resolution\tend\n");
    return value;
  }
  if (from > to) {
        Serial.println("map_resolution\tend\n");
    return value >> (from-to);
  }
    Serial.println("map_resolution\tend\n");
  return value << (to-from);

}

// Wait for synchronization of registers between the clock domains
static __inline__ void syncADC() __attribute__((always_inline, unused));
static void syncADC() {
  Serial.println("syncADC\tstart");
  while (ADC->STATUS.bit.SYNCBUSY == 1){
    
  }
  Serial.println("syncADC\tend\n");
}

// Wait for synchronization of registers between the clock domains
static __inline__ void syncDAC() __attribute__((always_inline, unused));
static void syncDAC() {
  Serial.println("syncDAC\tstart");
  while (DAC->STATUS.bit.SYNCBUSY == 1){
    
  }
  Serial.println("syncDAC\tend\n");
}

int pinPeripheral( uint32_t ulPin, EPioType ulPeripheral )
{
  Serial.println("pinPeripheral\tstart");
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
  {
    Serial.println("pinPeripheral\tend\tnot a pin\n");
    return -1 ;
  }else{
      Serial.println("passed first if statement");
  }

  switch ( ulPeripheral )
  {
    case PIO_DIGITAL:
      Serial.println("digital");
    case PIO_INPUT:
      Serial.println("input");
    case PIO_INPUT_PULLUP:
      Serial.println("input pullup");
    case PIO_OUTPUT:
      Serial.println("output");
      // Disable peripheral muxing, done in pinMode
//      PORT->Group[g_APinDescription[ulPin].ulPort].PINCFG[g_APinDescription[ulPin].ulPin].bit.PMUXEN = 0 ;

      // Configure pin mode, if requested
      if ( ulPeripheral == PIO_INPUT )
      {
        pinMode( ulPin, INPUT ) ;
      }
      else
      {
        if ( ulPeripheral == PIO_INPUT_PULLUP )
        {
          pinMode( ulPin, INPUT_PULLUP ) ;
        }
        else
        {
          if ( ulPeripheral == PIO_OUTPUT )
          {
            pinMode( ulPin, OUTPUT ) ;
          }
          else
          {
            // PIO_DIGITAL, do we have to do something as all cases are covered?
          }
        }
      }
    break ;

    case PIO_ANALOG:
      Serial.println("analog");
    case PIO_SERCOM:
      Serial.println("sercom");
    case PIO_SERCOM_ALT:
      Serial.println("sercom_alt");
    case PIO_TIMER:
      Serial.println("timer");
    case PIO_TIMER_ALT:
      Serial.println("timer_alt");
    case PIO_EXTINT:
      Serial.println("external interrupt");
    case PIO_COM:
      Serial.println("com");
    case PIO_AC_CLK:
      Serial.println("clock");
#if 0//if false????????
      // Is the pio pin in the lower 16 ones?
      // The WRCONFIG register allows update of only 16 pin max out of 32
      Serial.println("clock if loop");
      if ( g_APinDescription[ulPin].ulPin < 16 )
      {
        Serial.println("g_APinDescription[ulPin].ulPin < 16");
        PORT->Group[g_APinDescription[ulPin].ulPort].WRCONFIG.reg = PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_PMUXEN | PORT_WRCONFIG_PMUX( ulPeripheral ) |
                                                                    PORT_WRCONFIG_WRPINCFG |
                                                                    PORT_WRCONFIG_PINMASK( g_APinDescription[ulPin].ulPin ) ;
      }
      else
      {
      Serial.println("g_APinDescription[ulPin].ulPin is not < 16");
        PORT->Group[g_APinDescription[ulPin].ulPort].WRCONFIG.reg = PORT_WRCONFIG_HWSEL |
                                                                    PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_PMUXEN | PORT_WRCONFIG_PMUX( ulPeripheral ) |
                                                                    PORT_WRCONFIG_WRPINCFG |
                                                                    PORT_WRCONFIG_PINMASK( g_APinDescription[ulPin].ulPin - 16 ) ;
      }
#else
      if ( g_APinDescription[ulPin].ulPin & 1 ) // is pin odd?
      {
        Serial.println("pin is odd\nCRASH");
        uint32_t temp ;

        // Get whole current setup for both odd and even pins and remove odd one
        temp = (PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg) & PORT_PMUX_PMUXE( 0xF ) ;
        // Set new muxing
        PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg = temp|PORT_PMUX_PMUXO( ulPeripheral ) ;
        // Enable port mux
        PORT->Group[g_APinDescription[ulPin].ulPort].PINCFG[g_APinDescription[ulPin].ulPin].reg |= PORT_PINCFG_PMUXEN ;
      }
      else // even pin
      {
        Serial.println("even pin\nCRASH");
        uint32_t temp ;

        temp = (PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg) & PORT_PMUX_PMUXO( 0xF ) ;
        uint32_t temp_2;
        temp_2 = temp|PORT_PMUX_PMUXE( ulPeripheral );
        Serial.println(temp_2);
        PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg = temp_2;


        
        PORT->Group[g_APinDescription[ulPin].ulPort].PINCFG[g_APinDescription[ulPin].ulPin].reg |= PORT_PINCFG_PMUXEN ; // Enable port mux
      }
#endif
Serial.println("break of clock");
    break ;

    case PIO_NOT_A_PIN:
    Serial.println("pinPeripheral\tend\tnot a pin\n");
      return -1l ;
    break ;
  }
Serial.println("pinPeripheral\tend\tend of code\n");
  return 0l ;
}

int analogRead_debug(pin_size_t pin)
{
  Serial.println("analogRead\tstart");
  uint32_t valueRead = 0;

  if (pin < A0) {
    pin += A0;
  }
//ulPinType
  if (g_APinDescription[pin].ulPinType != PIO_ANALOG){
    return  -1;
  }

  pinPeripheral(pin, PIO_ANALOG);

  // Disable DAC, if analogWrite() was used previously to enable the DAC
  if ((g_APinDescription[pin].ulADCChannelNumber == ADC_Channel0) || (g_APinDescription[pin].ulADCChannelNumber == DAC_Channel0)) {
    syncDAC();
    DAC->CTRLA.bit.ENABLE = 0x00; // Disable DAC
    //DAC->CTRLB.bit.EOEN = 0x00; // The DAC output is turned off.
    syncDAC();
  }

  syncADC();
  ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[pin].ulADCChannelNumber; // Selection for the positive ADC input

  // Control A
  /*
   * Bit 1 ENABLE: Enable
   *   0: The ADC is disabled.
   *   1: The ADC is enabled.
   * Due to synchronization, there is a delay from writing CTRLA.ENABLE until the peripheral is enabled/disabled. The
   * value written to CTRL.ENABLE will read back immediately and the Synchronization Busy bit in the Status register
   * (STATUS.SYNCBUSY) will be set. STATUS.SYNCBUSY will be cleared when the operation is complete.
   *
   * Before enabling the ADC, the asynchronous clock source must be selected and enabled, and the ADC reference must be
   * configured. The first conversion after the reference is changed must not be used.
   */
  syncADC();
  ADC->CTRLA.bit.ENABLE = 0x01;             // Enable ADC

  // Start conversion
  syncADC();
  ADC->SWTRIG.bit.START = 1;

  // Waiting for the 1st conversion to complete
  while (ADC->INTFLAG.bit.RESRDY == 0);

  // Clear the Data Ready flag
  ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;

  // Start conversion again, since The first conversion after the reference is changed must not be used.
  syncADC();
  ADC->SWTRIG.bit.START = 1;

  // Store the value
  while (ADC->INTFLAG.bit.RESRDY == 0);   // Waiting for conversion to complete
  valueRead = ADC->RESULT.reg;

  syncADC();
  ADC->CTRLA.bit.ENABLE = 0x00;             // Disable ADC
  syncADC();
  Serial.println("analogRead\tend\n");
  return mapResolution(valueRead, _ADCResolution, _readResolution);
}




void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
analogRead_debug(9);
delay(10000);
}
