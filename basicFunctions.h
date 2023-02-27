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

