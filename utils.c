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
 * _strdup - Duplique une chaîne de caractères en allouant dynamiquement
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
