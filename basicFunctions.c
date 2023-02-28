/**
 * Get Char Length
 * 
 * @param char c - char array to calculate length of
 * 
 * @return int - length of char array
*/
int getCharLen(char *c) {
    int len = 0;
    while(*c) {
        len++;
        c++;
    }
    return len;
}



/**
 * A simple delay use
 * 
 * @param int d - amount of ticks that the loop will go through
*/

void delay(int ticks) {
	int i;
	for(i = ticks; i > 0; i--);
}

