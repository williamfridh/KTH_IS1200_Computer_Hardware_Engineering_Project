/**
 * Get Char Length
 * 
 * @param {char}    - char array to calculate length of
 * @return {int}    - length of char array
 * @author Fridh, William
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
 * @param {int} - amount of ticks that the loop will go through
 * 
 * @author Åhlin, Pontus
*/
void delay(int ticks) {
	int i;
	for(i = ticks; i > 0; i--);
}

