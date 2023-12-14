#include "main.h"

int main(void)
{
while (1)
{
/* prompting */
char *prompt = "shell$~ ";
char *new_line = "\n";
char *string = malloc(1024);
size_t nl_size = 1;
size_t size = 0;
int input;
char *token;
int index = 0;
char *arguments[1024];
char *command_path;
int PID;
int status;


write(1, prompt, sizeof(prompt));
/*start taking input*/


input = getline(&string, &size, stdin);
if (input == -1)
{
/* code */
if (feof(stdin))
{
/* code */
write(1, new_line, nl_size);
exit(0);
}
else
{
perror("no input read");
return (-1);
}
}
else if (input == 1)
{
continue;
}
else
{
/* Process the input using string tokenization*/

token = strtok(string, " \n");
/* We use a null terminating tokenization*/
while (token != NULL)
{
arguments[index] = token;
token = strtok(NULL, " \n");
index++;
}
arguments[index] = NULL;
if (strcmp(arguments[0], "cd") == 0)
{
cd_command(arguments[1]);
}
else if (strcmp(arguments[0], "exit") == 0)
{
exit(0);
}
else
{
command_path = pathFinder(arguments[0]);
if (command_path == NULL)
{
write(1, arguments[0], sizeof(arguments[0]));
perror(":");
continue;
}
else if (command_path != NULL)
{
PID = fork();
if (PID == -1)
{
write(1, arguments[0], sizeof(arguments[0]));
perror(": fork failed");
return (-1);
}
else if (PID == 0)
{
command_path = pathFinder(arguments[0]);
execve(command_path, arguments, __environ);
write(1, arguments[0], sizeof(arguments[0]));
perror(": execute failed");
exit(1);
}
else
{
waitpid(PID, &status, 0);
if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
{
perror(": command found but can't execute");
}
}
}
}
}
}
return (0);
}