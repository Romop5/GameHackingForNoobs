# Introduction
Welcome to Game Hacking for Noobs. This aim of this book is to give you a *really* brief
introduction into an art of examining computer processes and more precisely, computer games.

By reading this modest book you should
* understand what computer programs are and how their run at our computers 
* find variables in alien programs you are interested in 
* create simple hacks

# Architecture of computers
Before we can start with examining applications such as computer games, we will need to understand
at least some basics of *computer architecture*. Following section will give you rather brief overview
of the architecture. In case you are familiar with terms such as *stack*, *heap*, *instructions* and
*instruction set*, you can skip this chapter.

## What are computer programs made of
So you probably knows that computers are running computer programs, written by fanatic programmers
who sacrifice their life to create the best program ever doing their voo-doo with mystery computers. 

In reality, **computer programs** are just sequentions of code. But what's code ? Well, that depends
on what the program is written in. Usually, programs consist of **statements** and **expressions**,
   which determine model the flow of program. 

According to Dijkstra, *statements* can be listed into three general categories:

 * **sequence** allows to define a block of commands which are processed one-by-one
 * **control** statements can choose which way to go according to some conditions
 * **iteration** defines commands which are executed repeatedly either for fixed-iteration times or till
condition for iteration is valid - for example, **for**, **while** or **do while**  
 * **assignment** copies values from one place to another 

*Expressions* are made of operators and can be evaluated into value of some type. For example,
    expression (sin(90 deg)*5.0 + 1.0) evaluates roughly to 6.

The text state above can is demostrated in following C program: 
```
    // this is a simple function which takes a single parameter N 
    int fibonnaci(int n)
    {
        // if N is lower than or equal to  1, return 1
        if(n <= 1) // IF is a control-flow statement 
            return 1; // return is just a statement which assigns return value
        else {
            // otherwise compute value as a sum of previous two elements of Fibbonaci series
            // n-2 is an expression which computes a temporate value whis passed to fibonnaci function
            return fibonnaci(n-1)+fibonnaci(n-2);
        }
    }
```

## Stack vs heap
While implementing an algorithm, one may not be certain about how much of data he will need to
store. The amout of data may be determined by users or other outter factors. 
To store the data in the program, computer programs utilize two memory models:

 * **stack** is special region in global memory which has a specific mode of access. It can be
 accessed randomly as for reading, but data can only be appended or poped from the top of stack. It
 is used implicitely when we create local variables in functions. Each thread has its
 own stack and stack is usually used to pass arguments to functions.
 * **heap** is another specialized region in global memory which has its memory manager called
 **allocator** which assignes memory subsection on demand. Heap can either be managed by standard
 library (that's that malloc does), operating system or even the program itself. 

## A CPU point of view
As you can see, programms are usually programmed using programming languages with *higher
abstraction*. Hold on, why higher ? Is there any lower abstraction ? Actually, there is as programs
are perceived differently by computers and will get to this in following section.

When programmes are done in abstract languages, they must be converted into form which can be
interpreted by CPU. Most of modern CPUs are actually dumb - they only use a set of simple
instructions which express simple operations with memory, registers and ALU unit.

CPUS are **state-machines**. That means their activity is controled by *state*, which they store in so-called **flags**. 
This machines have access to global memory (called RAM) and to **registers** that stores the data
that CPU is currently working with. Actually, CPUs are such simple that there are no instructions
to express iterations or selections explicitely. Instead, CPUs work with **jumps** and
**conditioned jumps** which allow to express these high level abstractions.

What CPU does is that it has a special register called **instruction pointer** which stores address
to global memory and denotes the current position in code. Before CPU runs, it **fetches** the
instruction at pointed address, **decodes** and **executes** the instruction afterwards. Execution
manipulates **data path** - it may lead to loading additional data from memory to register, manipulating with registers using arithemetics and logics
or storing data back to memory.

Consider the example of calculating `fibonnaci` function. We have already seen its C version. So how
would a C function look like in CPU-instruction version ?

Here is an example snippet in a pseudo-Assembly language:
```
    # Beggining of fibonnaci
    fibonnaci:
    COMPARE n, 1
    JUMP IF EQUAL zeroAndOneCase
    # If JUMP is not taken, this section is executed
    
    # Store our current n argument
    PUSH n 
    # Execude n-1
    SUBTRACT n, 1
    # Call fibonnaci function with new argument n
    CALL fibonnaci
    ADD sum, returnValue 
    # Get the original argument
    POP n
    # SUBTRACT n, 2
    # Call fibonnaci function with new argument n
    CALL fibonnaci
    ADD sum, returnValue 
    POP n
    MOVE returnValue, sum
    RETURN
    # zeroAndOneCase section of code is only accessed using JUMP above
    zeroAndOneCase:
    MOVE returnValue, 1
    RETURN 
```

Please, note that I made up the names of instructions in order to make the example more concise.

Except of lines starting with #, each line stand for an **instruction** which is executed by CPU.
The execution of instruction is influenced by flags (for example, JUMP IF EQUAL would check EQUAL
        flag before deciding where to continue.


So, as you could see, in reality, CPUs are executing simple instructions which has no knowledge of
the program itself - instructions only access registers, flags and global memory.

## Compilation & Linking & Execution
Up to now, we've seen how programs are written in languages supporting abstract constructions and
we've noted the fact that CPU can't work this way - it requires rather dumb sequence of
instructions, encode in CPU's specific instruction set code. So, how do we get there ? We use
*compilers*.

**Compilers** are computer programs which analyze other's program source codes and converts
(compiles) program from one computer language to another (possibly CPU sequence of instructions).
Naturally, the conversion preserves program's functionality so that both programs act equally.
Compilers analyze source code at different levels. Just briefly - characters which made the code are
gathered and analyzed to detect what kind of *lemma* (sentence member) are. Subsequently, syntax
trees are construct using lemmas and result in *abstract syntax trees* which can be either
exectuced (that's how interpreted languages such as Java/Python might work) or stored in different
language representing the parsed nodes of AST.

As a game hacker, you should understand that compilation may transform the source code into
something which looks completely different than the original. This covers stripping the names of
varibles, functions and commentaries stored in the code.


