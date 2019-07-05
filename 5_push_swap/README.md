# PUSH_SWAP

**Project Objectives :** Sorting algorithms, Stack concept

## Intro

This project requires you to sort data on a stack, with a limited set of instructions, in fewer possible moves.

## Usage

First, you have to  `make`. There are two programs: `push_swap` to get the instructions in function of a list of integers, and `checker` to execute those instructions.

```
>> ./push_swap
usage: ./push_swap [num1 num2 ...] -v[v_arg]

- [num] : Has to be integer and only different numbers

- [v_arg] NULL : quick-sort
-            1 : radix-sort
             2 : shell-sort
```
```
>> ./checker
usage: ./checker [num1 num2 ...] -v[v_arg]

- [num] : Has to be integer and only different numbers

- [v_arg] 1 : shell-viewer
          2 : graphic-viewer
``` 
### Testing
To generate a list of int you can use `` NUMS=`ruby -e "puts (-100..100).to_a.shuffle.join(' ')"` `` and then `./push_swap $NUMS`

<p align="center">
<img src="https://github.com/Talasta/My42Cursus/blob/master/5_push_swap/.resources/push_swap.gif" width="50%">
</p>

### Bonus
1.	Sorting algorithms
	> - **Quick sort**, _complexity_ ![equation](https://latex.codecogs.com/gif.latex?O%28n%5Ccdot%20log%28n%29%29)
	> - **Radix sort**, _complexity_ ![equation](https://latex.codecogs.com/gif.latex?O%28w%5Ccdot%20n%29) _where w is the number of bits required to store each key._
	> - **Shell sort**, _complexity_ ![equation](https://latex.codecogs.com/gif.latex?O%28n%5E2%29)

2. Visualization of sorting process
