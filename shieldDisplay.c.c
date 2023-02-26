#include <pic32mx.h>
#include <stdint.h>
    


/*
A simple delay used in the initialisation process of the code 
*/

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}



/*
A very important function of the program that sends data to the data buffer.
This function is responsible for being able to communicate with the display  
*/

uint8_t sendToBuf(uint8_t data) {           //THIS WAS TAKEN FROM THE HELLO-DISPLAY EXAMPLE PROVIDED BY https://github.com/is1200-example-projects/hello-display/blob/master/main.c#L9
	while(!(SPI2STAT & 0x08));              //Wait for buffer to be ready
	SPI2BUF = data;                         //Write to next transmit byte
	while(!(SPI2STAT & 0x01));              //Wait for the received byte 
	return SPI2BUF;                         //Put the received byte in the buffer
}



/*
This part of the code is used to initiate the display/buttons.
*/

void initDisplay(){
    
    PORTFCLR = 0x10;            //(All bits are initilized to 1 automatically.) port RF4
    
    delay(10);                  //Delays are needed for the setup of the initialization for the display, if there aren't any you program wont start
    
    PORTFCLR = 0x40;            //Set RF6 and RF4 to outputs, this turns on the VDD for the OLED and 
                                //gives data command.
    delay(1000000);         
    sendToBuf(0xAE);            //Turns on the display   
    PORTGCLR = 0x200;           //Something with RG9
    delay(10);
    PORTGSET = 0x200;           //Not needed 
    delay(10);

    
    sendToBuf(0x8D);            //Disables charge
    //senToBuf(0x18);           //Set the Higher column start adress for page adressing mode
                                //meaning that we set the value of the 
    sendToBuf(0xD9);            //Setting up pre-charge period, for the data clock
    //sendToBuf(0xF1);	        //Sets the adressing mode, in this case [01] -> Vertical adressing mode, Could write 0 instsead of F. 

 
    PORTFCLR = 0x20;

    delay(10000000);
    sendToBuf(0xA1);            //Column map adress 127 is mapped to SEG0. Meaning that SEG0 is to the most right of the OLED
    sendToBuf(0xC8);            //Remapped mode, scan from COM[N-1] TO COM0 which means it goes through the Rows of the OLED 

    sendToBuf(0xDA);            //Init COM pins
    sendToBuf(0x20);            //Init memory 

    sendToBuf(0xAF);            //Toggle(in this case on) display

}



void initPins(){
	/* Output pins for display signals */
	TRISFCLR = 0x70;			//0111 0000		sets bits (index) 4-6 to 0(outputs) in portF
	TRISGCLR = 0x200;			//0010 0000 0000	sets bit (index) 9 to 0(output) in PORTG
		
    SPI2CONSET = 0x60;		    //0110 0000 Turns on MSTEN(Master mode) and CKP(Clock polarity select)
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000;		//1000 0000 0000 0000
}



/*

*/

void sendDisplayData(const uint8_t *data) {
    int i, j;

    for(i = 0; i < 4; i++){
        PORTFCLR = 0x10;        //Turns on the VDD 
        sendToBuf(0x22);        //Set page command
        sendToBuf(i);           //Page number

        sendToBuf(0x0);
        sendToBuf(0x10);

        PORTFSET = 0x10;

        for(j = 0; j < 64; j++){			// j < x is the width of the render. 
            sendToBuf(~data[i*32 + j]);
        }
    }
}



void initShield(){

    initPins();
    initDisplay();

}