# MES: Exercise Week 4

## Task 1 - Command Line Interface
> One of the requirements for your final project is to have a serial interface. Chapter 3 talked
> about testing the hardware and software with a command pattern. This sort of testing lets you
> try pieces on the hardware over and over, making debugging easier.

I used another console application for embedded systems instead of the one given.
It is the same I use at work (though i did not set it up and port to the system, so this was new to me) and i like
the way to add commands more.

The console i used is part of this [anchor](https://github.com/rideskip/anchor) library 
(see [console](https://github.com/rideskip/anchor/tree/master/console)).

To port it to my system i first had to implement a write function that you pass to the console struct (using a function pointer):
```
void Console_Write_Function(const char *str);
```
The second thing is to read the input from the UART and pass it on to the `console_process` function which takes a char array and its length.
This function can be also used with only one char, so i implemented a reading function that reads one character and passes it on.
This function is called as often as possible in the main loop. 
I used the UART in blocking mode for transmitting and also for receiving data due to lack of time.
I plan on changing receiving data to interrupt or even to DMA if i find the time to do that.

For now I only implemented one command, that enables/disables the led blinking (by turning off its timer).

## Task 2 - Final Project Specification

See the [README](https://github.com/friedemann03/Plant-Controller/blob/main/README.md) of this repository.

I am far from finished, I got sick during the week so i did not have a lot of time. I already have a basic idea and also
gave a lot of though to different aspects of the idea but did not finalize anything yet.
