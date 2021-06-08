/*
 
 Simple C++ Shell.cpp
 
 CSCI 3120, Assignment #1
 Summer 2018
 
 Author:
 Burak Can Ozter - B00784243
 
 Assignment Description:
 
 Design a C++ program to serve as a shell interface that accepts user commands, then execute each command in a separate process.In addition, provide a history feature that allows the user to access the most recently entered commands.
 
 
 
 
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_CMD_LINE 80

int main(void){
    
    char *args[MAX_CMD_LINE/2 +1];
    int should_run =1;
    int argc = 0;               //argument count
    
    
    std::vector<std::string>entered_input;
    std::vector<std::string> command_history;
    
    while(should_run == 1){
        int status = 1;             //int variable to control to run a process.
        
        
        std::string input;              //user input variable initialize
        std::cout << "CSCI3120>";
        std::getline(std::cin, input);  //capture entire user input line
        
        std::istringstream iss(input);  //start tokenizing
        std::string InputAfterSpace;                  //capture second input after space
        while ( getline( iss, InputAfterSpace, ' ' ) ) {    //getline with space delimiter
            
            
            if(InputAfterSpace == "exit"){              //if user input exit, program stops
                std::cout << "Exiting the program..." << std::endl;
                
                should_run = 0; //set should run to 0 so gets out of while loop and stop
                
            }
            
            if(!InputAfterSpace.empty() && (InputAfterSpace != "history")){ //history isnt captured as a shell command.
                if(input[0] == '!'){
                    continue;
                }
                else{
                    /*
                     The token is not history or does not start with exclamation mark
                     Therefore, it is a shell command and should be stored for the history
                     feature purposes.
                     
                     Argc = Argument Count is also increased in order to find index of commands.
                     
                     */
                    entered_input.push_back(InputAfterSpace);
                    command_history.push_back(InputAfterSpace);
                    argc++;
                }
            }
            
            
        }
        std::string com_arr[argc];                      //allocate array memory for as many as arguments present
        std::copy(command_history.begin(), command_history.end(), com_arr); //copy vector into array of strings
        
        if(input == "history"){
            /*
             
             User types history and wants to see what commands are executed.
             They are going to displayed here.
             
             If no commands in the history error that to user.
             As assignment 1 stated, only last 10 commands to be displayed.
             */
            
            if(command_history.empty()){
                
                std::cout << "No commands in history.." << std::endl;
            }
            if(command_history.size() > 10)
            {
                for(int i=argc; i> (command_history.size() -10); i--){
                    std::cout << i << ": " << com_arr[i-1] << std::endl;
                }
            }
            else
            {
                for(int i = argc; i>0; i--)
                {
                    std::cout <<  i << ": " << com_arr[i-1] << std::endl;
                }
            }
        }
        
        
        std::string arr[argc];          //allocate array size of argument count
        std::copy(entered_input.begin(),  entered_input.end(), arr); // copy vector into array of strings
        
        if(input != "history") {
            /*
             This is where user inputs actual command such as ps, cal, who, top etc.
             and they get executed by the child proccess.
             */
            
            
            
            if(input[0] == '!' && input[1] != '!'){
                
                int num = 0;                    //int variable num, number , to get the number after exclamation mark
                std::string hold = &input[1];   //get the number after ! and store as a string
                num = std::stoi(hold.c_str());  //conversion from string to int and
                //this is also the command index we want to access and run
                
                if (num > command_history.size()) //if number is not in range of command history, show that error
                {
                    std::cout << "No such command in history..." << std::endl;
                    status =0;                      //this variable is not to trigger the most recent process.
                }
                else{
                    num--;                              //because the vector list start from 0, correction is made by decreasing
                    //num variable by 1
                    
                    args[0] = const_cast<char*>(entered_input.begin()[num].c_str());  //accesed to Nth element in the history
                }
            }
            else  if(input == "!!"){
                /*
                 The case where user enter double exclamation marks
                 The most recent command is to be run
                 */
                if(command_history.empty())
                {
                    /*
                     Check if there are no commands
                     */
                    std::cout << "No commands in history.." << std::endl;
                    
                }
                else{
                    /*
                     There are commands therefore access the last element of vector list
                     */
                    args[0] = const_cast<char*>(entered_input.end()[-1].c_str());
                }
            }
            
            else{
                /*
                 User input to run
                 */
                
                args[0]= const_cast<char*>(entered_input.back().c_str());
            }
            
            
            if(status == 1 && (should_run == 1)){
                
                /*
                 Status = 1 therefore execute this part of the code.
                 
                 Start child and parent processes here.
                 */
                
                args[argc] = NULL; //The last element of args is always set to be NULL
                
                pid_t pid = fork();  //create child process
                
                
                if (pid < 0) {
                    /*
                     Pid is negative number flag the error
                     */
                    std::cout << "Error" << std::endl;
                    return 1;
                }
                
                // Child process
                else if (pid == 0) {
                    // Execute command
                    execvp(args[0], args);
                    
                    return 0;
                }
                
                // Parent process
                else {
                    // Wait for child process to finish
                    int childStatus;
                    waitpid(pid, &childStatus, 0);
                    should_run = 1;
                }
            }
            
        }
    }
    
    return 0;
}


