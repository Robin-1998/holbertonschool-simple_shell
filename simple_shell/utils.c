#include "main.h"

/**
 * _strlen - Calcule la longueur d'une string
 * @str : string
 * Return: Retourne le nombre de caractère
 */
int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - Compare deux chaîne de caractères
 * @s1 : la première chaîne de caractères à comparer
 * @s2 : la deuxième chaîne de caractères à comparer
 * @nbre_lettre : nombre de caractère
 * Return: Si les 2 chaînes sont égale cela renvoit NULL
 *         Si 1ère plus petite que 2ème cela renvoit valeur négative
 *         Si 2ème plus petite que 1ère cela renvoit valeur positive
 */
int _strcmp(char *s1, char *s2, int nbre_lettre)
{
	int i;

	for (i = 0; i < nbre_lettre; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * strtok - Découpe une chaîne en sous-chaînes (tokens) en utilisant un
 * séparateur.
 * @str: La chaîne à découper
 * @separator: La chaîne contenant les séparateurs.
 * Return: Un pointeur vers le token trouvé, ou NULL s’il n’y en a plus.
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

/**
 * strdup - Duplique une chaîne de caractères en allouant dynamiquement
 * de la mémoire pour y copier la chaîne source.
 * @str: La chaîne de caractères source à dupliquer.
 * Return: Un pointeur vers la nouvelle chaîne dupliquée, ou NULL si
 * l’allocation échoue.
 */
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
