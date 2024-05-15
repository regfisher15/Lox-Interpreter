**HOW TO RUN THE CLOX INTERPRETER**

**Introduction:**

Below is a simple guide that shows how to run the clox interpreter. It informs you on the tools

that you will need and also the commands that you will need in order to build and run the program.

Links and images will be given down below.

**TOOLS YOU'LL NEED:**

In order to run and test this interpreter, you will need an IDE for manipulating the code and a

terminal to build and run the project. The IDE I use is visual studio code. If you need help

downloading the software there is a link below that shows how to get through the setup of the

software. (any software that supports c++17 would be suffice)

<https://www.youtube.com/watch?v=JPZsB_6yHVo>

You will also need a terminal for running this program. The terminal I used for this interpreter

is Cygwin. If you need help downloading this software as well, there is another link down below

that can help you with installing the software. When installing, make sure to download the C++17

packages and the cmake packages. (again, any terminal should be fine to use that has c++17 and cmake features)

<https://www.youtube.com/watch?v=5b-dzp9HBN4>

**HOW TO RUN THE PRGORAM:**

There are two ways that you can run the clox interpreter. You can either enter the lox code into the repl loop or you can enter lox code into the text file named "Code.txt". I will show you how to do both options.

**THE REPL OPTION:**

To run the repl option for the code, first make sure that you change your directory to where you downloaded the file too. You can do this using the “cd” command. Next, here are the commands that you will need to enter into your terminal to start the repl:

\> **make clean**

\> **make**

\> **./SyntaxTreeGenerator**

\> **./Application**

Once you enter these commands in, you can type lox code into the terminal and hit enter to submit them. The program will continue to ask you for code until you kill the program. You can kill the program by typing CTRL + C. An example of the repl option is given in the image below.

![BYTECODE REPL EXAMPLE](https://github.com/regfisher15/Lox-Interpreter/assets/168298464/b186035e-e68b-4a94-98a6-f82bb6b8f47c)

**THE SOURCE CODE OPTION:**

To run the source code option for the code, first make sure that you change your directory to where you download the file too. You can do this using the “cd” command. The final folder you want to move into would be the Interpreter folder. Next, you want to copy and paste your lox code into the file named “Code.txt” and save the file. This file can be found in the folder called “Source Code”. After doing this, here are the commands that you will need to enter into the terminal to run and execute the program:

\> **make clean**

\> **make**

\> **./SyntaxTreeGenerator**

\> **./Application SourceCode/Code.txt**

Once you have entered in these commands, the program will automatically compile and run your code and the results will be displayed on the screen. If you would like to enter in new code, simply edit the “Code.txt” file and enter the same commands once again. An example of the source code option is given in the image below.



There is another README file found in the “Interpreter” folder if you would like to view it as you work with the code. That’s all, happy coding 😊
