#include "main.h"
/**
 * main -
 *
 * @return int
 */
int main()
{
	char *line = NULL;
	size_t n = 0;
	ssize_t read = 0;
	int status, i;
	pid_t pid;
	char *argument[2];
	extern char **environ;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		read = getline(&line, &n, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror ("Echec création new processus ");
			exit (1);
		}

		if (pid == 0)
		{
			argument[0] = line;
			argument[1] = NULL;
			if (execve(argument[0], argument, environ) == -1)
			{
				perror ("Erreur d'exécution");
				exit (1);
			}
			return (0);
		}
		else
		{
			wait(&status);
		}
	}
	for (i = 0; argument[i]; i++)
		free(argument[i]);

	free(line);
	return (0);
}
