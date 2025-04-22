#include "main.h"

/* fonction qui duplique une chaine de caractère*/
char *_strdup(char *str)
{
	int i, j;
	char *dest;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		;

	dest = malloc((i + 1) * sizeof(char));
	if (!dest)
		return (NULL);

	for (j = 0; str[j] != '\0'; j++)
		dest[j] = str[j];

	dest[j] = '\0';
	return (dest);
}

/* fonction qui lit la ligne du terminal, les entrées de l'utilisateur*/
size_t _read_line(char **line, size_t *n)
{
	ssize_t read = getline(line, n, stdin);
	if (read == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		return 0;
	}

	if (read > 0 && (*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';

	return (read);
}

/* fonction qui découpe les phrases en petit bout */
char **_strtok(char *str, char *separator)
{
	char *copie, *token, **double_tableau;
	int i = 0, nbre_mot = 0;
	separator = " :";
	if (!str)
		return (NULL);
	copie = _strdup(str);
	if (!copie)
		return (NULL);
	token = strtok(copie, separator);
	while (token)
	{
		nbre_mot++;
		token = strtok(NULL, separator);
	}
	free(copie);
	double_tableau = malloc(sizeof(char *) * (nbre_mot + 1));
	if (!double_tableau)
		return (NULL);
	copie = _strdup(str);
	if (!copie)
		return (NULL);
	token = strtok(copie, separator);
	while (token)
	{
		double_tableau[i] = _strdup(token);
		if (!double_tableau[i])
		{
			while (i > 0)
				free(double_tableau[--i]);
			free(double_tableau);
			free(copie);
			return (NULL);
		}
		i++;
		token = strtok(NULL, separator);
	}
	double_tableau[i] = NULL;
	free(copie);
	return (double_tableau);
}

/* fonction qui execute un programme si trouvé */
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
