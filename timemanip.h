//does the argument represetn a valid time? (is it a valid signed 32-bit int)
bool representsTime(char *string) {
    char *ptr;
    long stringAsLong = strtol(string, &ptr, 10);
    //we're casting an int to a time_t so it should be a signed 32 bit int
    if(strcmp(ptr, "") == 0 && (int)0x80000000 <= stringAsLong && stringAsLong <= 0x7FFFFFFF) {
        return true;    
    }
    else {
        return false;
    }
}

/*If the commandline argument represents a valid time_t, set the flag which determines whether the actime or mtime need to be changed to true.
Otherwise, print error message and tell the user to supply a valid value for the -a or -m flag*/
bool getTimeAndSetFlag(char *string, time_t *time, bool *flag, char option) {
    if(!representsTime(string)) {
        *flag = false;
        printf("Please specify a valid value for -%c\n", option);
        return false;
    }
    else {
        *time = (time_t) atoi(string);
        *flag = true;
        return true;
    }
}

