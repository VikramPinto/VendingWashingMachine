#include<pic.h>
#include<htc.h>
//__CONFIG (DEBUGDIS & LVPDIS & FCMEN & IESODIS & MCLREN & BOREN & /*UN*/PROTECT &  PWRTEN & WDTDIS & INTIO); 
//__CONFIG (BORV21);
unsigned char disp_pos=0;
unsigned char ucCount_OneSec = 0;
unsigned char ucCount_100ms  = 0;
unsigned char ucCount_500ms  = 0;
bit bOneSecOver = 0;
bit b100msOver  = 0;
bit b500msOver  = 0;
bit b5msOver =0;
unsigned int ones, tens, hundreds,number=0;
char pos[4]={0,0,0,0};

#define TMR0_VAL 		215    // [256-175 = 81 x 128uS = 10.24ms]

#define DIG1 RA2
#define DIG2 RA1
#define DIG3 RA0

#define SEG_A  RB7
#define SEG_B  RB1
#define SEG_C  RB2
#define SEG_D  RB3
#define SEG_E  RB4
#define SEG_F  RB5
#define SEG_G  RB6
#define SEG_DP RA7

#define HIGH 1
#define LOW  0

#define SEG_ON HIGH
#define SEG_OFF LOW

#define DIG_ON HIGH
#define DIG_OFF LOW  

#define DISP_DLY delay(100)
#define STATUS_LED RA7

void vfnInit() {
	/**************** Initialization of Clocks ****************/

	OSCCON = 0x71 ;				// Select 8Mhz internal Oscillator as clock source 
								// Internal Frequency Select bits  --> 	IRCF < 6:4 > = 111 = 8Mhz
								// System Clock Select 		   -->	SCS < 0 >    = 0   = Internal Oscillator
								// Other bits ( Status bits ) are ReadOnly bits			
       							// Tune the Oscillator to Factory caliberated frequency
								// Frequency Tuning Bits   --> 	TUN < 4:0 >  = 0000 = Factory caliberated
								// Bits < 7 : 5 > are unimplemented



	/**************** Initialization of Ports *****************/

	ANSEL = 0x00 ;				 // Disable Analog channel		 
	TRISA = 0x00 ;				 // Make the port as output 
	         					 // RA7 --> Test LED		
	ANSELH = 0x00;		         // Disable Analog channel				  				
	TRISB  = 0x01;               // RB0 is external interrupt for coin detection
	//PORTB  = 0x00;               // 
	
	

	/*********** Configure Timer 0 for 10ms interrupt generation *************/
	TMR0 = TMR0_VAL ;                    // Load Count value for 10ms into TMR0	
	OPTION_REG = 0x07; //0x04 ;		     // Select 1:256 Prescalar ant assign it to Timer0
						                 // Prescalar Assignment bit		--> PSA <3> = 0 = Prescalar is assigned to Timer0
						                 // Prescalar Selection bits		--> PS<2:0> = 111 = 1:256 Prescalar
 										 
						     // Clock Source 	: Fosc/4 = 2MHz
			       			 // Pre-Scalar	    : 1:256
						     // 1 Count		    : 1 / (2MHz/256) = 7.8125KHz = 128uS
						     // Mode		    : 8 bit Timer mode, interrupt enabled

	
	T0IE   = 1;   // Enable Timer0 Interrupt	
	INTE   = 1;   // Enable external interrupt
	INTEDG = 1;   // config for rising edge
	INTF   = 0;   // clear ext interrupt flag
}



void delay(int delay){
	int i=0;
	for(i=0;i<delay;i++);
}

void disp_val(char *val)
{  
  switch(val[0])
  {
    case '0' :
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_ON; // e
              SEG_F  = SEG_ON; // f
              SEG_G  = SEG_OFF; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '1' : 
              
              SEG_A  = SEG_OFF; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_OFF; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_OFF; // f
              SEG_G  = SEG_OFF; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '2' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_OFF; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_ON; // e
              SEG_F  = SEG_OFF; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '3' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_OFF; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '4' : 
              SEG_A  = SEG_OFF; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_OFF; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_ON; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '5' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_OFF; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_ON; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '6' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_OFF; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_ON; // e
              SEG_F  = SEG_ON; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '7' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_OFF; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_OFF; // f
              SEG_G  = SEG_OFF; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '8' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_ON; // e
              SEG_F  = SEG_ON; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    case '9' : 
              SEG_A  = SEG_ON; // a
              SEG_B  = SEG_ON; // b
              SEG_C  = SEG_ON; // c
              SEG_D  = SEG_ON; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_ON; // f
              SEG_G  = SEG_ON; // g
              SEG_DP = SEG_OFF; // dp
    break;

    default:
              SEG_A  = SEG_OFF; // a
              SEG_B  = SEG_OFF; // b
              SEG_C  = SEG_OFF; // c
              SEG_D  = SEG_OFF; // d
              SEG_E  = SEG_OFF; // e
              SEG_F  = SEG_OFF; // f
              SEG_G  = SEG_OFF; // g
              SEG_DP = SEG_OFF; // dp
    break;
  }
}

void send_disp(unsigned char dig)
{
	DIG1 = DIG_OFF;
	DIG2 = DIG_OFF;
	DIG3 = DIG_OFF;
 
	switch(dig)
	{
		case 0:
          
		  disp_val(pos);                      
		  DIG1= DIG_ON;
		break;
		
		case 1:  
  		  disp_val(pos +1 );                       
		  DIG2= DIG_ON;  
		break;

		case 2:
		  disp_val(pos +2);
		  DIG3= DIG_ON;
		break;
	}

}

/******************************* 10ms Interrupt **************************************************************/
static void interrupt my_isr (void) {

	if(INTF)
	{
		INTF =0;
		number++;
	}
	
	if ( T0IF )											//  If Timer 0 Interrupt flag is set
	{												//  reset Timer 0 interrupt flag
		T0IF = 0 ;		
				
		b5msOver = 1;
       
		/************************** 100 ms ******************************************************/
		ucCount_100ms++;
		if(ucCount_100ms >19) {
			ucCount_100ms =0;
			b100msOver =1;

			ucCount_500ms++;
			if(ucCount_500ms > 4)
			{
				b500msOver =1;
				ucCount_500ms=0;

				ucCount_OneSec++ ;
				if ( ucCount_OneSec > 1 )          // 1 second
				{
					ucCount_OneSec = 0 ;
					bOneSecOver = 1;
					
				}	
			}		
		}
	

		/*************************** 1 Second ***************************************************/
	 									// End of 1 Second
		/***************************** End of 1 Second ******************************************/

        TMR0 = TMR0_VAL ;  // Assign the prescalar back to the timer                                    		
	}	
}


void main()
{
	GIE = 0 ;                           		// Disable all the interrupts
	vfnInit();
	GIE = 1 ;                           		// Enable all the interrupts
	
	while(1)
	{

		if(b5msOver)
		{			
			send_disp(disp_pos);
        	if(++disp_pos > 2)
        		disp_pos=0;
			b5msOver=0;	
		}

		if(b100msOver) {
			b100msOver =0;

					        	
		}

		if(b500msOver)
		{
			b500msOver=0;

			ones = number % 10; 
		    tens = (number / 10) % 10; 
		    hundreds = number / 100; 
		
		    pos[0] = (hundreds + 0x30) ;
		    pos[1] = (tens + 0x30) ;
		    pos[2] = (ones + 0x30) ;
		    pos[3] = ' ' ;
			
		}

		if(bOneSecOver) {
		
			//STATUS_LED ^= 1;
			//for (number =0; number<1000; number++){
			    
				//number ++;
				//if(number > 999)
 				//number =0;
			//}


				

			bOneSecOver =0;
		}		
	}
}
