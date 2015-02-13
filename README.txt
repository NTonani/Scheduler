SCHEDULER COMPARISON

Author: Nathan TOnani

Simple c program comparing two different scheduling algorithms: Priority based vs shortest job first (neither pre-emptive).

Within is a text file titled "Setup.txt". Within this text file is (in order):

ProcessID ArrivalTime CPUBurst Priority

NOTE: A larger priority value means higher priority

The program will check for lines with all four values and will stop when a line that is different than that is recorded. Do not change the title of the file ("Setup.txt"). I have supplied the file, with an example of 50 processes.

The results show the following: Priority based is slower but more effective in running the necessary processes. Neither algorithms are considered fair, because they aren't based on the time a process joins the queue. This has a lot to do with neither algorithm being pre-emptive.
