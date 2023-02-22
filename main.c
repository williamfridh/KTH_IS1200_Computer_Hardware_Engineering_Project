#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

// Settings
int screenCode = 1;
int mytime = 0x0000;


int main(void) {
volatile int * porte = (volatile int *) 0xbf886110;                   // Supposed to be inside labwork(), but unnecesarry
*porte = 0x2;
  timerInit();
  while(1) {
    listenForTick();
  }
  
}

/* Lab-specific initialization goes here */
void timerInit( void )
{

  volatile int * trise = (volatile int *) 0xbf886100;                 // Defined pointer to TRISE
  *trise = *trise & 0xffffff00;                                       // Set ports 0-7 as outputs

  TRISDSET = 0xfe0;                   //Set switches 1,2,3,4 and buttons 2,3,4 as inputs 
  T2CON = 0x70;                       //Stopping timer and setting the prescaler to 1/256
  PR2 = ((80000000 / 256)/ 10);       //Setting the period for the timer
  TMR2 = 0;                           //Ticks to PR2
  T2CONSET = 0x8000;                  //Starting timer

  return;
}

/* This function is called repetitively from the main program */
volatile int * porte = (volatile int *) 0xbf886110;                   // Supposed to be inside labwork(), but unnecesarry
int timeoutcount = 0;                                                 //A global counter used in labwork
int ledTime = 0;                                                      //Int time counter 
void listenForTick( void )
{

  if(IFS(0) & 0x100){                                             //Detect and interrupt flag
    timeoutcount++;                                               //Increment global counter 
    IFS(0) = 0;                                                   //Clear flags
    if(timeoutcount == 10){                                       //If there as been 10 timeout event flags then the timer value and LEDs will update
      timeoutcount = 0;
      *porte = ledTime;                                           //Set let value to mytime.
      ledTime++;
      update();
    }
  }

}

void update(void) {
}
