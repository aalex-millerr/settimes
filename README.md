# settimes
Settimes is a tool which lets you modify the timestamps associated with when an inode was last accessed and when it was last modified, or to just see those times. Use the -a flag and a valid signed 32-bit integer to set the time the inode was last accessed, and do the same with the -m flag for the time it was last modified. Call the program with no arguments to receive a help message.

# build
Building is pretty simple, just `cd` in to the project's directory and execute `make`

# examples

`./settimes -a 12345678 -m 87654321 testfile` 
sets the last time the inode was accessed to 12345678 seconds after the epoch, and the last time it was modified to 87654321 seconds after the epoch.

`./settimes testfile`<br>
'testfile' was last accessed at Sat May 23 14:21:18 1970<br>
or 12345678 seconds since the epoch.<br>
'testfile' was last modified at Wed Oct 11 05:25:21 1972<br>
or 87654321 seconds since the epoch.<br>

`./settimes --help` or `./settimes -h` or `./settimes`<br>
To set the time the file was last accessed, use the -a flag and specify the number of seconds since the epoch you wish to set the time to.<br>
For the time the file was last modified, do the same with the -m flag.<br>
To see when the file was last accessed and modified, only enter the file/directory name as an argument.<br>
Example usage: settimes -a <last access time in seconds> -m <last modified time in seconds> <filename>
