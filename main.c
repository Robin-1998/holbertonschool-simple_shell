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
			printf("$ "); /* Affiche l'invite si mode interactif */
		if (_read_line(&line, &n) == 0)
		{
			break; /* Quitte la boucle si l'utilisateur fait CTRL+D */
		}
/* Découpe la ligne en tokens et les stocke dans un tableau */
		argument = _token_doubletableau(line, separator);
		if (argument == NULL)
			return (1); /* Quitte si erreur d'allocation mémoire */
/* Trouve le chemin complet de la commande */
		_getpath(argument, environ);
	/* Crée un processus pour exécuter la commande */
		_fork_execve_wait(argument, environ);
		for (i = 0; argument[i]; i++)
			free(argument[i]); /* Libère chaque chaîne du tableau */
		free(argument);  /* Libère le tableau */
	}
	free(line); /* Libère la ligne saisie à la fin du programme */
	return (0); /* Fin normale du programme */
}
