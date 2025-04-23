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

char *_strchr(char *s, char c)
{
	int i; /* Déclaration d'un compteur pour parcourir la chaîne */

	i = 0; /* Initialisation de l'index à 0 */

	/* Boucle qui parcourt la chaîne tant qu'on n'a pas trouvé le caractère*/
	/*recherché et qu'on n'est pas arrivé à la fin de la chaîne ('\0') */
	while (s[i] != c && s[i] != '\0')
	{
		i++; /* Passage au caractère suivant */
	}

	/* Vérifie si on a trouvé le caractère recherché */
	if (s[i] == c)
	{
		/* Retourne l'adresse du caractère trouvé dans la chaîne */
		return (&s[i]);
	}
	else
	{
		/* Retourne NULL (0) si le caractère n'a pas été trouvé */
		return (0);
	}
}
