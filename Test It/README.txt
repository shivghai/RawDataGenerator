Test Input Generator

Definition Format:

<variable name> <string/int/double/char/struct> <def/range/const/fileName> <values>



Input format:

<definition 1>
<definition 2>
..
<definition n>
end
“repeat <literal/int> (optional)” <line 1 format>
“repeat <literal/int> (optional)” <line 2 format>
“repeat <literal/int> (optional)” <line 3 format>
..
“repeat <literal/int> (optional)” <line 3 format>
CTRL+D or end of file to end input



The Data Definition Types:

1. Defined (string, int, double, char)

Each time the variable is used, it may get different values (unless there is only one value defined)
For char, instead of space separated values just specify one string with all the necessary chars

<variable name> <string/int/double/char> def <value1> <value2> ...

examples:
myVar int def 0  (for constant declarations)
myVar int def 0 1 2 3 4 (for random values from a list of values)
myVar string def ABC DEF GHI (for random declarations from a list of values)
myVar char 0123456789abcdefghijklmnopqrstuvwxyz


2. Range (int, double, char)

Generates random value between specified range

Each time the variable is used, it may get different values

<variable name> <int/double/char> range <lower limit> <upper limit>

examples:
myVar int range 0 10 (generates random value between 0 and 10)
myVar double range -10.0 10.0 (generates random value between -10.0 and 10.0)


3. Const (int, double, char)

Same as range, except that when the value is set once, it is constant throughout

i.e. generates a random value in the range, and then every time the variable it used the value stays constant

examples:
same as Range


4. Structure (struct)

Can be used to initialize a struct type from an input file (commma delimited)
The first row should be the categories


5. Literals

Do not need to be defined, only used in the format


The Repeat Command:

Used to repeat a line multiple times. Literals or other int-based variables can be used to specify the number of repeating lines

examples:

input
repeat 5 10 1 0
output
10 1 0
10 1 0
10 1 0
10 1 0
10 1 0

input
repeat myVar 5 10    (assuming myVar is set to 3)
output
5 10
5 10
5 10


Modifiers (used as a prefix for tokens):

format: %<token>

1. > : can be used to append to the next token 

Example:
input
>$ 75
don’t be >ev il
output
$75
don’t be evil

2. , : can be used to modify the separator from a space to a comma
       can also be used to change the file delimiter from a space to a comma

Example:
input
don’t ,be evil
output
don’t be,evil

3. {N} : can be used to loop the following variable ’N’ times in the same line

Example:
input
{5} yay
output
yay yay yay yay yay

input
{5} >yay
yayyayyayyayyay

4. ~ : can be used to ignore all other modifiers after the '~'. Also can be used to output the modifiers

5. @ : struct modifier
    randomly access one of the structs which are initialized from the file, using @varName.category
    access the same struct in the same line using same number of "@"s in the same line
    @ accesses random strings, more than one @ (eg- @@, @@@) in the same line access the same line number from the file

Example:
@@mystruct.name @@mystruct.phone @@mystruct.address in the same line will access the same struct/line from the file
@mystruct.name @mystruct.name will be different
@@mystruct.name @@mystruct.name will be the same
@mystruct.name @@mystruct.name may or may not be the same

6. _ : whitespace flag
adds spaces. if _ is needed, use ~_ which will ignore the special behavior of _


Arithmetic: according to tags
    Tags are parantheses before the tokens
    (var1)myVar
