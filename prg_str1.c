#include "s_shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int f;
	int t;

	for (f = 0; dest[f] != '\0'; f++)
		;

	for (t = 0; src[t] != '\0'; t++)
	{
		dest[f] = src[t];
		f++;
	}

	dest[f] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t f;

	for (f = 0; src[f] != '\0'; f++)
	{
		dest[f] = src[f];
	}
	dest[f] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int f;

	for (f = 0; s1[f] == s2[f] && s1[f]; f++)
		;

	if (s1[f] > s2[f])
		return (1);
	if (s1[f] < s2[f])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int f = 0;

	for (; *(s + f) != '\0'; f++)
		if (*(s + f) == c)
			return (s + f);
	if (*(s + f) == c)
		return (s + f);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int f, t, bool;

	for (f = 0; *(s + f) != '\0'; f++)
	{
		bool = 1;
		for (t = 0; *(accept + t) != '\0'; t++)
		{
			if (*(s + f) == *(accept + t))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (f);
}
