# Most common Assembly instructions

Hey ! This text covers the most common x86 instructions that you can encounter with while hacking our beloved games !
Before we can start with enumerating and explainging instructions, we will need to discuss at least basics of how CPU works.

## About CPUs
**CPU** stands for *central processing unit*. What a regular CPU does is expressed in 5 instruction process stages:
1. Fetch 
2. Decode
3. Execute
4. Read
5. Write back

During the first stage, *fetch*, the CPU loads the instuction from **RAM**. Which instruction should it load ? The address is
stored inside so called **instruction pointer** or **program counter**, which is refered as **EIP** at x86 or **RIP** in 64-bit world.

When instruction is fetched into *instruction register*, the CPU must determine the semantics and actions which it should sort out
for given instruction. This stage is called **decode** and causes that required signals inside CPU circuit are set up for the next stage.

In the next stage, the instruction semantics is procceeded. This usually covers doing *arithmetic-logic operations* such as summing,
multiplying, dividing or *bitwise operations* such as logical AND or OR.

During this stage, instruction can also manipulate with **program counter** and conditionally change the address of the next instruction.
That's how programs are branched and how it all works.

But, hold on, what is being added or divided ? What values does it operate on ? Well, the processor has either two
options how to get data it works with - either data are stored inside **registers**, which are specialized and size-bounded 
variables and which can be filled in using specialized CPU instructions.

The second option is that the instruction somehow referes the value outside of CPU. The value which we operate on can be
hard-coded inside the instruction code (and thus already retrieved during *fetch* stage), or it's stored at addresses, which
is mentioned in the instruction. In that case, the whole instrucion process must stall for a single cycle in order to load
data from RAM to immediate register.

Then, when result is retrieved after successfully operating over *ALU unit*, the result must be written back, which happens
in **write back** stage.

To sum it, processors process *instructions* to find out what should happens to data stored in *registers* and in RAM.

## Stack
To be honest with you, there is still something I haven't mentioned yet - stack.
**Stack** is a range of addresses inside RAM, allocated for it. As the name says,
this addresses are usually being manipulated in terms of *stacking* - new values
are **pushed** onto stack, and afterwards **popped** from the top.

What can be this good for ? 
1. Temporary variables and midresults are stored at stack, because there is a fixed number of registers
and it's easier to organize data in layers which are pushed and poped
2. Stack frames for functions. Whenever a function is called, the caller saves the current function state onto stack
and the address for returning back. This also allows us to call the same function recursivelly - each time
the function is called the variables are stored at stack, so the next recursive call won't overwrite our current values 

**CAUTION !!!** In convention, the stack works in reversed. When pushing data onto stack, the stack address **decreases**, and when
popping it **increases**. 
The idea is that your **heap** and **stack** are stored inside the same memory and they both grow towards each other.


## Instructions
### mov dest, src
This instruction stands for moving - actually, it *copies* data from *source* to *dest*.

### jmp dst
This instruction changes **program counter** to dst uncoditionally. That means the program will continue
at location *dest*.

### CMP a,b
Compares integer values of both resources. It result of comparison is stored in **flag register**.

### jz/jnz/je dest
This is a conditional version of *jmp* instruction. The jump is done if and only if condition is fullfilled.
The fullfillness is stored inside so-called **flag register** which can be set by comparison instructions such 
as **CMP**, **AND**.

Character 'N' means negation of condition.

### call dest
Calls function at dest. Usually, arguments are either pushed at stack using **push** instruction, or stored inside devoted **regiters** (e.g. ECX is used for
storing class instance's address). If you are insterested, search for **calling conventions**.
### ret 
Jump to the next instruction after previous **CALL**.

### push value
Pushes value onto stack. The stack address after completing 

### label:
Stand for marked addresses which we can use for jumping and calling.
## Simple program

Consider following programm:

```asm
mov eax, 0xF
cycle:
dec eax
cmp eax, 0x0
jne cycle
end:
```
We will examine the program function step-by-step.

```
mov eax, 0xF
```
The first line uses *mov* instruction for setting the initial value in *EAX* register. The initial value is
*0xF*, which is 16 in decimal form. In computer world, 0x prefix usually *implies hexadecimal notation*.

```
cycle:
```
*cycle* label denotes the address of cycle beginning.

```
dec eax
```
Each time the instruction is executed the value in EAX get decreased.

```
cmp eax, 0x0
```
The instruction compares the current value in EAX register with 0. If both values are equal, then **zero flag** is set.
If EAX is greater, **above flag** is set.

```
jne cycle
```
Finally, **jne** stands for *jump if not equal**. The instruction checks for **zero flag**. If the flag isn't set, it jumps.

As you can see, the previous program iterates over values 16, 15, 14 ... 0 and then it terminates.