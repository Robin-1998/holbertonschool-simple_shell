#include "main.h"
/**
 * _fork_execve_wait - fonction qui exécute un programme
 * @argument : correspond à notre argument dans notre terminal
 * @environ : Tableau de chaînes représentant les variables d’environnement
 */
void _fork_execve_wait(char **argument, char **environ)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("Echec de création du nouveau processus");
		exit(1);
	}
	if (pid == 0)
	{
		if (execve(argument[0], argument, environ) == -1)
		{
			perror("Erreur dans l'exécution");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * _getpath - Recherche dans les variables d’environnement la commande à
 * exécuter, et remplace `argument[0]` par le chemin absolu si elle est
 * trouvée dans l’un des répertoires du PATH.
 * @argument : Tableau de chaînes représentant la commande et ses arguments
 * @environ : Tableau de chaînes représentant les variables d’environnement
 * Return: int
 */
int _getpath(char **argument, char **environ)
{
	int i = 0;
	char *token, *PATH = NULL, contenant[1024], *copie;

	while (environ[i])
	{
		if (_strcmp(environ[i], "PATH=", 5) == 0)
		{
			PATH = environ[i] + 5;
			break;
		}
		i++;
	}
	if (PATH == NULL)
		return (1);
	copie = _strdup(PATH);

	if (copie == NULL)
	{
		perror("strdup");
		return (1);
	}
	token = strtok(copie, ":");
	while (token)
	{
		sprintf(contenant, "%s/%s", token, *argument);
		if (access(contenant, X_OK) == 0)
		{
			free(*argument);
			*argument = _strdup(contenant);
			if (!*argument)
			{
				perror("strdup");
				free(copie);
				return (1);
			}
		}
			token = strtok(NULL, ":");
	}
	free(copie);
	return (0);
}

