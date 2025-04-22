#include "main.h"
/**
 * main - simple shell
 *
 * Return: int
 */
int main(void)
{
	char *line = NULL, *argument[2];
	size_t n = 0;
	int status;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (read_line(&line, &n) == 0)
		{
			break;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Echec création new processus ");
			exit(1);
		}
		if (pid == 0)
		{
			argument[0] = line;
			argument[1] = NULL;
			if (execve(argument[0], argument, environ) == -1)
			{
				perror("Erreur d'exécution");
				exit(1);
			}
			return (0);
		}
		else
			wait(&status);
	}

	free(line);
	return (0);
}
