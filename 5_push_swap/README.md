# PUSH_SWAP

**Learning Goal :** Sorting algorithms

## Intro

This project requires you to sort data on a stack, with a limited set of instructions, in fewer possible moves.

## Usage

First, you have to  `make`. There are two programs: `push_swap` to get the instructions in function of a list of integers, and `checker` to execute those instructions.

```
>> ./push_swap [num1 num2 ...]
```
```
./checker [num1 num2 ...]
``` 
### Testing
To generate a list of int you can use `` NUMS=`ruby -e "puts (-100..100).to_a.shuffle.join(' ')"` `` and then `./push_swap $NUMS`
