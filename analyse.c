#include "main.h"

/**
 * _read_line - fonction qui permet de lire une ligne depuis l'entrée standard
 * stdin(qui lit les données entrées par l'utilisateur lors du lancement via
 * terminal). Elle utilise getline pour allouer dynamiquement la
 * mémoire si nécessaire.
 * @line : Un double pointeur vers une chaîne de caractères qui servira
 * à stocker l’adresse du texte lu.
 * Autrement dit, la fonction va créer (ou ajuster) un espace en mémoire
 * pour y mettre la ligne que l’utilisateur a tapée, et ce pointeur va
 * te permettre d’y accéder.
 * @n :Un pointeur vers une variable qui indique la taille du texte lu.
 * Return: Le nombre de caractères lus (y compris le retour à la ligne
 * '\n' s’il est présent), ou 0 si l’utilisateur fait Ctrl+D
 * (fin de fichier) ou s’il y a une erreur.
 */
size_t _read_line(char **line, size_t *n)
{
	ssize_t read = getline(line, n, stdin);

	if (read == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (0);
	}

	if (read > 0 && (*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';

	return (read);
}

/**
 * _strtok -fonction qui tokenise une chaîne de caractères en utilisant
 * un séparateur donné.
 * @str: La chaîne d'entrée à diviser.
 * @separator: Le séparateur utilisé pour la division (écrasé ici par " :")
 * Return: Un tableau de chaînes (tokens) terminé par NULL,
 * ou NULL en cas d'erreur.
 */
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
