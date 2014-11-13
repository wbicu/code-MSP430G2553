#include "Pervasive_Displays_small_EPD.h"

volatile int ready = 1;
volatile unsigned i = 0;
unsigned char test1[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF};


void init(){
	WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;
    P1SEL = BIT1 | BIT2 ;
    P1SEL2 = BIT1 | BIT2;
    P1DIR |= 0x41;
    P1SEL = BIT1 | BIT2 ;
    P1SEL2 = BIT1 | BIT2;
    UCA0CTL1 = UCSWRST;
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 65;
    UCA0BR1 = 3;
    UCA0MCTL = UCBRS1 + UCBRS0;
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0RXIE;
    __bis_SR_register(GIE);
}

int main(void) {
	init();

	for(;;) {
		if (ready==1){
			EPD_display_from_pointer(EPD_270,test1);
			ready = 0;
		}
	}

}
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
	unsigned char data = UCA0RXBUF;
	    if (i < 33) {
	    	test1[i++] = data;
	    } else {
	    	i=0;
	    	test1[33] = data;
	    	ready = 1;
	    }
		IFG2 = IFG2 & 0x0A;
}
