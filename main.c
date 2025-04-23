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
	char *line = NULL;
	size_t n = 0;
	char **argument;
	char *separator = " ";
	(void)ac;
	(void)av;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		if (_read_line(&line, &n) == 0)
		{
			break;
		}

		argument = _strtok(line, separator);
		if (argument == NULL)
			return (1);

		_getpath(argument, environ);

		_fork_execve_wait(argument, environ);

		for (i = 0; argument[i]; i++)
			free(argument[i]);
		free(argument);
	}
	free(line);
	return (0);
}
