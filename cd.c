#include "main.h"

void cd_command(char *args)
{
  /* If the user does not pass any argument*/
if (args == NULL)
{
char *env_home = getenv("HOME");

if (env_home == NULL)
{
perror("cd: didn't set HOME variable \n");
}
else
{
/* Take the user home*/
if (chdir(env_home) != 0)
{
perror("cd: couldn't change directory\n");
}
}
}
else
{
/* If the user adds an argument*/
if (chdir(args) != 0)
{
perror("cd: couldn't change directory\n");
}
}
}
