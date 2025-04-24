#include "main.h"
/**
 * _fork_execve_wait - fonction qui exécute une commande en créant un
 * processus fils
 * @argument : correspond à notre argument dans notre terminal
 * @environ : Tableau de chaînes représentant les variables d’environnement
 */
void _fork_execve_wait(char **argument, char **environ)
{
	pid_t pid = fork(); /*on créé au processus enfant*/
	int status;

	if (pid == -1) /*on gère le cas d'erreur*/
	{
		perror("Echec de création du nouveau processus");
		exit(1);
	}
	if (pid == 0)/*execve remplace le process actuel par la commande demandée*/
	{ /*on gère aussi le cas d'erreur si ça ne fonctionne pas et on quitte*/
		if (execve(argument[0], argument, environ) == -1)
		{
			perror("Erreur dans l'exécution");
			exit(127);
		}
	}
	else /*on bloque le processus parent tant que l'enfant n'a pas terminé*/
	{
		wait(&status); /* on met en pause tant que ce n'est pas fini*/
	}
}

/**
 * _getpath - Cherche où se trouve la commande dans les dossiers du PATH
 * @argument : Tableau de chaînes représentant la commande et ses arguments
 * @environ : Tableau de chaînes représentant les variables d’environnement
 * Return: int
 */
int _getpath(char **argument, char **environ)
{
	int i = 0;
	char *token, *PATH = NULL, contenant[1024], *copie;
/* On cherche la ligne qui commence par "PATH=" dans les variables d'env*/
	while (environ[i])
	{
		if (_strcmp(environ[i], "PATH=", 5) == 0)
		{
			PATH = environ[i] + 5;
			break;
		}
		i++;
	}
	if (PATH == NULL)/*Si on trouve pas PATH, on arrête tout*/
		return (1);
	copie = _strdup(PATH);/*duplique la variable PATH pour pas tuer l'original*/
	if (copie == NULL)
	{
		perror("strdup"); /*si la duplication échoue*/
		return (1);
	} /*On découpe chaque dossier du PATH (séparés par des ":")*/
	token = strtok(copie, ":");
	while (token)
	{/*on stock dans contenant notre chemin complet*/
		sprintf(contenant, "%s/%s", token, *argument);
		if (access(contenant, X_OK) == 0) /*access c'est exécutable*/
		{/*Si commande trouvé, on remplace argument[0] par le chemin absolu*/
			free(*argument);
			*argument = _strdup(contenant);
			if (!*argument)
			{
				perror("strdup");/*Si on n'arrive pas à sauvegarder le chemin*/
				free(copie);
				return (1);
			}
			break;
		} /*Sinon on teste le dossier suivant dans PATH*/
			token = strtok(NULL, ":");
	}
	free(copie);
	return (0);
}

