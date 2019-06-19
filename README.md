## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Compiling](#compiling)
* [Preview](#preview)
* [Author](#author)

## General info
 This software is designed to serve as a C++ shell interface that accepts user commands, then execute each command in a separate process.In addition, it provides a history feature that allows the user to access the most recently entered commands.

 "!!" will trigger the history command and will show a list of commands that have been entered.
 In order to run a command from the list, user must type "!1" where the number is the index from the history list.
 
 Supported commands are ps, cal, date, who, top and ls.
	
## Technologies
Project is created with:
* XCode version: 10.2.1

## Compiling

To compile this software you must use a gcc terminal.
1. Open the bash terminal
2. To compile, $ g++ --std=c++11 -o run.out main.cpp
3. To run, ./run.out

## Preview

<img src="https://i.imgur.com/IIOcyZj.png">


## Author

* Burak Can Ozter
* burak.ozter@dal.ca
	
