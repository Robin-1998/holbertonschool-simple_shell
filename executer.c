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
 * _getenv - fonction qui permet de récupérer une variable d'environnement
 * @name: pointeur vers une chaîne contenant le nom de la variable à chercher
 * @environ: Double pointeur vers le tableau des variables d'environnement.
 * Return: Un pointeur vers la valeur de la variable
 * d’environnement si trouvée.
 * NULL si le nom est NULL, si environ est NULL, ou si
 * la variable n’existe pas.
 */
char *_getenv(char *name, char **environ)
{
	int i = 0;
	int longueur;

	if (name == NULL || environ == NULL)
		return (NULL);

	longueur = _strlen(name);

	while (environ[i])
	{
		if (_strcmp(environ[i], name, longueur) == 0 &&
			environ[i][longueur] == '=')
		{
			return (environ[i] + longueur + 1);
		}
		i++;
	}
	return (NULL);
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
	char *token, *PATH, contenant[1024], *copie;

	if (_strchr(argument[0], '/') != NULL)
	{
		if (access(argument[0], X_OK) == 0)
			return (0);
		else
			return (1);
	}

	PATH = _getenv("PATH", environ);
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
		if (_verif_path(token, argument, contenant) == 0)
		{
			free(copie);
			return (0);
		}
		token = strtok(NULL, ":");
	}
	free(copie);
	return (1);
}



int _verif_path(char *token, char **argument, char *contenant)
{
	sprintf(contenant, "%s/%s", token, *argument);

	if (access(contenant, X_OK) == 0)
	{
		free(*argument);
		*argument = _strdup(contenant);
		if (!*argument)
		{
			perror("strdup");
			return (1);
		}
		return (0);
	}
	return (1);
}
