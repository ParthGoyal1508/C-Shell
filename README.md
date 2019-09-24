# Bash Shell:

### Usage:
1. make
2. ./shell

### Files:
	* main.c 	            -	contains the main file
	* builtin-commands.c 	-	Functions to execute built-in commands like echo, cd, pwd
	* display.c 	        -	Function to display in <username@system_name:curr_dir> format
	* history.c 	        -	Function to get the history of user's command 
	* input.c 	            -	Taking input and parcing the commands 
	* ls.c 	                - 	listing out directories and files 
	* pinfo.c 	            -	prints the process related info of your shell program.
	* headers.h 	        - 	Libraries Include and global variable

### Commands that can be run on the shell:
	* pwd	                        -	Get the present working directory
	* cd                            -	Change directory
	* ls with options -l and -a     -	List the contents(files/folders/symlinks, etc)
	* pinfo             	        -	Get the process information
	* pinfo <pid>	                -	Get the process information of the given process id
	* clear	                        -	Clear the screen
    * echo                          -   Normal functioning as in bash
	* background processes can be run with & -	Get processes running in the background
    * history                       -   Normal functioning as in bash
    * history <num>                 -   Display only latest <num> commands
