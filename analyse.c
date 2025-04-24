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
{ /* lit une ligne depuis l'entrée standard et le stock*/
	ssize_t read = getline(line, n, stdin);

	if (read == -1)
	{ /* Vérifie si l'entrée est un terminal interactif */
		if (isatty(STDIN_FILENO))
			printf("\n"); /* Affiche \n en cas d'erreur (CTRL+D) */
		return (0);
	}
/* Si la ligne lue se termine par '\n', on l'enlève */
	if (read > 0 && (*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';
/* Remplace '\n' par '\0' pour terminer la chaîne */
	return (read); /* nombre de caractère lu*/
}
/**
 * _token_doubletableau - fonction qui tokenise une chaîne de
 * caractères en utilisant
 * un séparateur donné. (reproduit la commande strtok mais prend en compte
 * le cas d'un double pointeur)
 * @str: La chaîne d'entrée à diviser.
 * @separator: Le séparateur utilisé pour la division (écrasé ici par " :")
 * Return: Un tableau de chaînes (tokens) terminé par NULL,
 * ou NULL en cas d'erreur.
 */
char **_token_doubletableau(char *str, char *separator)
{
	char *copie, *token, **double_tableau;
	int i = 0, nbre_mot = 0;

	separator = " :"; /* espace et/ou : */
	if (!str)
		return (NULL);
	copie = _strdup(str); /* duplique str dans copie*/
	if (!copie)
		return (NULL);
	token = strtok(copie, separator); /* découpe copie et stock dans token */
	while (token) /* continue la découpe */
	{
		nbre_mot++;
		token = strtok(NULL, separator);
	}
	free(copie); /* Libère la première copie après le comptage */
	double_tableau = malloc(sizeof(char *) * (nbre_mot + 1));
	if (!double_tableau) /* Alloue de la mémoire pour le tableau final */
		return (NULL);
	copie = _strdup(str); /* Reduplication de str pour une seconde découpe */
	if (!copie)
		return (NULL);
	token = strtok(copie, separator);
	while (token) /* Recommence la découpe avec la nouvelle copie */
	{ /* Duplique chaque mot dans le tableau final */
		double_tableau[i] = _strdup(token);
		if (!double_tableau[i])
		{
			while (i > 0) /* Libère tout en cas d'erreur de duplication */
				free(double_tableau[--i]);
			free(double_tableau);
			free(copie);
			return (NULL);
		}
		i++;
		token = strtok(NULL, separator); /* Passe au mot suivant */
	}
	double_tableau[i] = NULL; /* Termine le tableau par un pointeur NULL */
	free(copie);
	return (double_tableau); /* Retourne le tableau de mots dupliqués */
}
