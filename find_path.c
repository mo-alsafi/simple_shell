#include "main.h"

char *pathFinder(char *token)
{
char *Path = getenv("PATH");
char *copiedPAth = strdup(Path);
char *paths = strtok(copiedPAth, ":");
while (paths != NULL)
{
/* code */
char *fullPath = malloc(1024);
sprintf(fullPath, "%s/%s", paths, token);
if (access(fullPath, F_OK) == 0 && access(fullPath, X_OK) == 0)
{
free(copiedPAth);
return (fullPath);
}
free(fullPath);
paths = strtok(NULL, ":");
}

/*size_t t_size = sizeof(token);
write(1, token, t_size);*/


return (NULL);
}
