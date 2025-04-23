#include "main.h"
/**
 * main - Point d’entrée du programme. Lance une boucle interactive qui lit
 * les commandes utilisateur, résout le chemin des exécutables via PATH et
 * exécute la commande avec `fork`, `execve`, et `wait`.
 * @ac : Nombre d’arguments passés au programme depuis la ligne de commande.
 * Non utilisé ici car les arguments sont lus dynamiquement à l'exécution.
 * @av : Tableau de chaînes contenant les arguments passés au programme.
 * Non utilisé ici, mais présent pour respecter la signature standard.
 * @environ : Tableau de chaînes représentant les variables d’environnement
 * Return: 0
 */
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
