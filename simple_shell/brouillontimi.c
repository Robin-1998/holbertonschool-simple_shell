int main(int ac, char **av, char **environ)
{
	int i;
	char *line = NULL, *separator = " ", **argument;
	size_t n = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		if (_read_line(&line, &n) == 0)
			break;

		argument = _strtok(line, separator);
		if (argument == NULL)
			continue;

		if (_exit_prog(argument))
			continue;

		if (_strcmp(argument[0], "env", 3) == 0)
		{
			for (i = 0; environ[i]; i++)
				printf("%s\n", environ[i]);
			free(argument); /* Libération à la fin de l'itération */
			continue;
		}
		if (_getpath(argument, environ) == 1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", av[0], argument[0]);
			free(argument);
			continue;
		}
		else
			_fork_execve_wait(argument, environ);
		free(argument); /* Libération de mémoire pour chaque commande */
	}
	free(line);
	return (0);
}

