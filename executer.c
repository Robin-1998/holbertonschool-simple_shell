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
	int i = 0;
	char *token, *PATH = NULL, contenant[1024];

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
	char *copie = _strdup(PATH);

	if (copie == NULL)
	{
		perror("strdup");
		return (1);
	}
	token = strtok(copie, ":");
	while (token)
	{
		sprintf(contenant, "%s/%s", token, *argument);
		if (fichier_stat(contenant))
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

/**
 * fichier_stat - fonction qui vérifie si un fichier ou un répertoire existe
 * à l'aide de stat
 * @ptr: Pointeur vers une chaîne de caractères contenant le
 * chemin du fichier à vérifier.
 * Return: - 1 si le fichier ou répertoire existe ou
 * 0 s'il n'existe pas ou en cas d'erreur.
 */
int fichier_stat(char *ptr)
{
	struct stat st;

	return (stat(ptr, &st) == 0);
}
