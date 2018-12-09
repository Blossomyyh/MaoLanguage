# MaoLanguage
C program including Reverse Polish expression conversion &amp; Linked list &amp;...

freshman year final project - completed in 2015

------

### Requirements

 Writing a program to run Mao

- The first parameter of the command line is the Mao language source code path, the source code is read and executed, and the result is output on the screen.

- There are only two types of variables in the Mao language—the 32-bit signed integer “int” and the 64-bit signed floating-point number “double”. The variable name contains only English letters and numbers, and the first character cannot be a number. Constants are only one of these two classes. They are considered floating point numbers when they contain a decimal point ".", for example, 3 is an integer and 3.0 is a floating point number. In the Mao language, floating point numbers do not use scientific notation (such as 1e-8, etc.).

- A Mao language program contains many lines of code, and each line has only one statement ending with a semicolon. Defining variables everywhere is also a point that Mao brother hates C language, so there are at most two parts in Mao language - the variable definition part and the statement execution part.

- Reverse Polish expression conversion

  Use stacks to store up the data 

  Define the type of the data by an integer variable.

  Notice the expliciting type conversion

  Use interge variables to identifying the startof stacks

  In the reverse of infix expression ,I use ‘#’ as the lowest priority to identidy the end of stack.



### Example

Input:

```c
int a;

double x, y;

int b, c, d;

a=5.5;

x=y=(1+a)*6.44;

a+4;

a=a/2;

print(a);

y=(c+6)*-(1+1);

print(y);

d=a/(2/5);

print(d);
```

Output:

```c
2

-12.000000

divided by ZERO
```



