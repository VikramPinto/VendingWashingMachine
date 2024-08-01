#include<pic.h>
#include<htc.h>
//__CONFIG (DEBUGDIS & LVPDIS & FCMEN & IESODIS & MCLREN & BOREN & /*UN*/PROTECT &  PWRTEN & WDTDIS & INTIO); 
//__CONFIG (BORV21);

unsigned char ucCount_OneSec = 0 ;
bit bOneSecOver = 0 ;
#define TMR0_VAL 		175    // [256-175 = 81 x 128uS = 10.24ms]
void vfnInit()
{
	/**************** Initialization of Clocks ****************/

	OSCCON = 0x71 ;				// Select 8Mhz internal Oscillator as clock source 
								// Internal Frequency Select bits  --> 	IRCF < 6:4 > = 111 = 8Mhz
								// System Clock Select 		   -->	SCS < 0 >    = 0   = Internal Oscillator
								// Other bits ( Status bits ) are ReadOnly bits			

	OSCTUNE = 0x00 ;					// Tune the Oscillator to Factory caliberated frequency
								// Frequency Tuning Bits   --> 	TUN < 4:0 >  = 0000 = Factory caliberated
								// Bits < 7 : 5 > are unimplemented



	/**************** Initialization of Ports *****************/

	ANSEL = 0x00 ;				 // Disable Analog channel		 
	TRISA = 0x00 ;				 // Make the port as output 
						 // RA7 --> Test LED		
							  				


	/*********** Configure Timer 0 for 10ms interrupt generation *************/
	TMR0 = TMR0_VAL ;                            // Load Count value for 10ms into TMR0	
	OPTION_REG = 0x07; //0x04 ;		     // Select 1:256 Prescalar ant assign it to Timer0
						     // Prescalar Assignment bit		--> PSA <3> = 0 = Prescalar is assigned to Timer0
						     // Prescalar Selection bits		--> PS<2:0> = 111 = 1:256 Prescalar
 										 
						     // Clock Source 	: Fosc/4 = 2MHz
			       			     // Pre-Scalar	    : 1:256
						     // 1 Count		    : 1 / (2MHz/256) = 7.8125KHz = 128uS
						     // Mode		    : 8 bit Timer mode, interrupt enabled

	
	T0IE = 1 ;                                   // Enable Timer0 Interrupt	
}


/******************************* 10ms Interrupt **************************************************************/
static void interrupt my_isr (void)    					
{
	
	if ( T0IF )											//  If Timer 0 Interrupt flag is set
	{												//  reset Timer 0 interrupt flag
		T0IF = 0 ;										
	

		/*************************** 1 Second ***************************************************/
	 	ucCount_OneSec++ ;
		if ( ucCount_OneSec > 99 )          // 1 second
		{
			ucCount_OneSec = 0 ;
			bOneSecOver = 1;
		}									// End of 1 Second
		/***************************** End of 1 Second ******************************************/

                TMR0 = TMR0_VAL ;            // Assign the prescalar back to the timer                                    		
		
		
	} 

	
}


void main()
{
	GIE = 0 ;                           		// Disable all the interrupts
	vfnInit();
	GIE = 1 ;                           		// Enable all the interrupts
	while(1)
	{
		if(bOneSecOver)
		{
			bOneSecOver =0;
			RA7 ^= 1;
		}
		
	}

}



