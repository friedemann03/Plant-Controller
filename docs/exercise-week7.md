# Week 7 Exercise

## Task
> Each chapter in the book ends with an interview question followed by the analysis of what an
> interviewer would look for in an answer. Choose two of the provided interview questions and answer them.
> Answers for the **I.x** ones are [here](https://www.interviewbit.com/embedded-c-interview-questions/), 
> answers for the **R.x** ones are [here](https://rmbconsulting.us/publications/a-c-test-the-0x10-best-questions-for-would-be-embedded-programmers/)


## First Question: I.3

_**What is an ISR?**_

An ISR or Interrupt Service Routine is a function that handles a specific interrupt related to it.
That's why it's also called an IRQ Handler (IRQ = Interrupt Request).
It has to take all steps necessary to "handle" the interrupt, e.g. clearing flags and often it also needs to determine where the interrupt comes from.
That is due to multiple peripherals or interrupts sharing the same ISR or the External Interrupts, which often share one interrupt across multiple pins.
The ISRs are related to the Interrupts over the Vector Table which is usually at the beginning of memory.
The vector table is specified by the chip vendor, relating each address in the vector table with an interrupt. 
In the vector table are addresses that point to the ISRs.
There are a bunch of very typical interrupts like the error handler, Non-Maskable Interrupt and the hard fault.
Those are usually also the first interrupts with the highest priorities.
Speaking of priorities, depending on the specific processor, interrupts can have different priorities and with some processors they even can be nested,
meaning an interrupt can interrupt another interrupt (funny sentence). Though nesting adds a lot of complexity and often is not necessary.
Most processors have a peripheral that takes care of interrupts, which is the Nested Vector Interrupt Controller (or NVIC).
This peripheral is used for nesting interrupts and taking care of interrupting the processor.

## Second Question: I.5

_**Why do we use the keyword volatile?**_

The keyword `volatile` is used to tell the compiler that the variable it is used for can not be replaced with a constant value which can happen
as an optimization by the compiler. A good example where this is a must are flags or set in interrupt that are polled in the main loop.
The compiler goes through the whole program and looks for usages or edits to that flag variable and finds nothing. That is because the 
compiler does not know, the ISR will be called during runtime, as it is not called from anywhere but executed when the corresponding interrupt occurs.
However, the compiler thinks it can save some memory by replacing the flag variable with its initialized value everywhere, basically treating it like a `#define`.
This will cause the flag to never change its value even when the interrupt fires and the ISR would set it.
This also is often the case with communication buffers written to in an ISR of a communication peripheral and the read from the main loop.
As said above, `volatile` stops the processor from doing that which makes it essential to every embedded system and many developers have adopted the habit of using it for all variables, just to be sure.

## Third Question: R.6

_(Answering these questions actually is kinda fun)_

_**What are the uses of the keyword static?**_

The keyword `static` has two different effects depending on the location in the source code it is used.

1. Used inside a function, it will make the variable keep its value across multiple function calls. 
When the function is called for the first time, it will initialize the value that is in the source code. 
If the function then alters that value (for example incrementing it) the variable will retain that value after the function returns.
Next time the function is called, it will not have the value visible in source code and will not re-initialize it.
The variable will have the value it had when the function returned last time.
2. Used inside a file, but not a function (at file scope), it will keep the global variable hidden from the outside.
Normally in C you can get globals from other files in the project with the `extern` keyword. 
This can lead to problems, because that means the globals are project wide global which can cause compile errors when to globals in different files are called the same.
The other (more important) part of the issue is missing information hiding. 
A global buffer inside a uart subsystem for example should never be queried from anywhere else than this file directly.
All information exchanges with the uart subsystem always should go through the exported functions (in the header).
The `static` keyword in file scope allows information hiding principles which are very important in modern software systems.

## Fourth Question R.2

_**Write the ‘standard’ MIN macro. That is, a macro that takes two arguments and returns the smaller of the two arguments.**_

```
#define MIN(X,Y) (X < Y ? X : Y)
```

## Fifth Question: I.15

_**What is a reentrant function?**_

A reentrant function is a function that can safely be called while it is running.
For example when main loop and some interrupt both call the same function, it needs to be reentrant.
All its variables need to be secured. As an example, if the function reads and writes to a global variable it is not reentrant.
The same is true for `static` variables in the function itself.

## Sixth Question: I.16

_**What kind of loop is better: Count up from zero or count down to zero? Why?**_

I would say "count up from zero" is the better approach.
Both approaches work the same and are technically equivalent.
Though for readability and understanding of the code, the first approach is better.
That is because it is the more common one as most problems solved by a for loop usually are up counting problems (copying data from one array to another for example).
Another reason is, that for loops are also called counting loop. 
So their most important information is how often they'll run which is easier to read when it starts from 0 until the loop index is not smaller than the amount of loops.
It also does not limit the functionality of a for loop because you can always alter the loop index (e.g. `amount of loops - i` to count down in an up counting loop).

## Seventh Question: R.9

_**Given an integer variable `a`, write two code fragments. The first should set bit 3 of `a`. 
The second should clear bit 3 of `a`. In both cases, the other bits should be unmodified.**_

```
#define BIT_3 0x08      /* 0b00001000, assuming starting with bit 0, this is bit 3 */

uint8_t a;

a = a | BIT_3           /* Setting Bit 3 while preserving the rest of a's content */

a = a & ~(BIT_3)        /* Clearing Bit 3 while preserving the rest of a's content */
```

## Eight Question: R.10

_**On a certain project it is required to set an integer variable at the absolute address
0x67a9 to the value 0xaa55. Write code to accomplish this task.**_

```
/* I've seen the answer before in the discord, though i can't remember the details */

int32_t *var;
var = (int32_t *)0x67a9;
*var = 0xaa55;
```

## Ninth Question: I.31

_**When does a memory leak occur? What are the ways of avoiding it?**_

A memory leak occurs, when a dynamically allocated memory does not get freed but all references to that memory are lost (due to leaving their context for example).
The memory is not available to the allocator and is seen as used but there is no way of ever using it or freeing it ever again.

## Tenth Question: R.14

_**What are the problems with dynamic memory allocation in embedded systems?**_

Embedded systems have limited resources in comparison to general purpose processors.
Using dynamic resource allocation on them can quickly lead to fragmented memory where you might have a kilobyte of free heap memory, 
but you can not allocate a kilobyte of memory because it is fragmented into a lot of small chunks of only a few byte each.
This can lead to stack overflows or heap overflows.
To really use dynamic memory allocation you need a memory management unit which takes up a lot of space in flash, memory and processor cycles.
This is often not viable for small embedded systems.


## Question I need to research
- **I.12**: _"Is it possible for a variable to be both volatile and const?"_
- **I.20**: _"What are the reasons for segmentation faults in embedded C? How do you avoid these errors?"_