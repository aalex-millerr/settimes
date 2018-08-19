#include <time.h> 
#include <utime.h> 
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "timemanip.h"


//set up long-form options so that we can get --help/-h working
static struct option long_options[] = {
    {"help", no_argument, 0, 'h'}, 
    {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {

    time_t atime, mtime;
    bool update_atime, update_mtime = false;
    int c;
    const char *usage = "To set the time the file was last accessed, use the -a flag and specify the number of seconds since the epoch you wish to set the time to.\nFor the time the file was last modified, do the same with the -m flag.\nTo see when the file was last accessed and modified, only enter the file/directory name as an argument.\nExample usage: settimes -a <last access time in seconds> -m <last modified time in seconds> <filename>\n";
    //if settimes is called with no arguments, show the usage messaged
    if(argc == 1) {
        printf("%s", usage);
        return 0;
    }

    while((c = getopt_long(argc, argv, "a:m:h", long_options, NULL)) != -1) {
        switch (c) {
        case 'a':
            if(!getTimeAndSetFlag(optarg, &atime, &update_atime, 'a')) {
                return 0;
            }
            break;
        case 'm':
            if(!getTimeAndSetFlag(optarg, &mtime, &update_mtime, 'm')) {
                return 0;
            }
            break;
        case 'h':
            printf("%s", usage);
            return 0;
            break;
        default:
            return 0;
            break;
        }
    }
    //by the time this loop terminates, optind will be the index of the final argument value in argv, so optind+1 will the file/directory of interest

    //if we have valid arguments and a single identifier, proceed to modify the times appropriately
    if(optind + 1 == argc) {
        char *identifier = argv[optind];
        struct stat currentStats;
        struct utimbuf updatedTimes;
        stat(identifier, &currentStats);
        if(!update_atime && !update_mtime) {
        //ctime_r invariably loads a 26 byte string into the memory at the address given by the pointer
            char atimeBuf[26], mtimeBuf[26];
            ctime_r((&currentStats.st_atim.tv_sec), atimeBuf);
            ctime_r((&currentStats.st_mtim.tv_sec), mtimeBuf);
            printf("'%s' was last accessed at %sor %d seconds since the epoch.\n'%s' was last modified at %sor %d seconds since the epoch.\n", identifier,  atimeBuf, (int)currentStats.st_atim.tv_sec, identifier, mtimeBuf, (int)currentStats.st_mtim.tv_sec);
            return 0;
        }
        if(update_atime) {
            updatedTimes.actime = atime;
        } else {
            updatedTimes.actime = currentStats.st_atim.tv_sec;
        }
        if(update_mtime) {
            updatedTimes.modtime = mtime;
        } else {
            updatedTimes.modtime = currentStats.st_mtim.tv_sec;
        }
        utime(identifier, &updatedTimes);
    }
//If we have more than one file/directory identifier being passed to the program, throw the following error
    if(optind + 1 < argc) {
        printf("settimes only takes a single identifier as an argument.\n");
    }
//if we don't have a file/directory identifier through the following error
    if(optind + 1 > argc) {
        printf("Please specify a file/directory identifier\n");
    }

    return 0;
}
