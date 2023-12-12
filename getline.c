#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 *Function to handle built-in commands
*/
int handle_builtin(char *cmd) 
{
	if(strcmp(cmd, "exit") == 0) 
		{
        		exit(0);
		} 
	else if(strcmp(cmd, "cd") == 0) 
		{
        /* Handle cd command */
        		return 1;
    		}

	/* Not a built-in command */
	return 0;
}

int main() 
{
    char cmd[100];

    while(1) 
{
        printf("$ ");
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) 
	{
            printf("\n");
            exit(0);
        }

        /* Remove newline character from cmd */
        cmd[strcspn(cmd, "\n")] = 0;

        /* Check for special characters */
        if(strpbrk(cmd, "\"'`,*&#") != NULL) 
	{
		printf("Error: Special characters are not supported.\n");
		continue;
        }

        /* Handle built-in commands */
	if(handle_builtin(cmd)) 
	{
            	continue;
        }


        /*  Execute the command */
        int status = system(cmd);
        if(status == -1) 
	{
            perror("Error executing command");
        } else if(WEXITSTATUS(status) != 0) 
		{
            		printf("Command exited with status %d\n", WEXITSTATUS(status));
        	}
    }

    return 0;
}

