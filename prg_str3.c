#include "s_shell.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int count = 0, f, t;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (f = 0; f < (count - 1); f++)
	{
		for (t = f + 1; t > 0; t--)
		{
			temp = *(str + t);
			*(str + t) = *(str + (t - 1));
			*(str + (t - 1)) = temp;
		}
	}
}
