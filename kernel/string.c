#include "string.h"

// Returns the length of the specified string.
size_t strlen(const char * s)
{
	// Calculates the returns the string length.
	size_t i; for (i = 0; s[i] != '\0'; i++); return i;
}

// Returns the index of the first occurence of the given character in the specified string.
// Returns -1 if the character cannot be located.
size_t find(const char * s, char c)
{
	for (size_t i = 0; i < strlen(s); i++)
	{
		if (s[i] == c) return i;
	}
	// find the character decode it, patch the string, redo this until finished.
	// Account for % without anything around it.
	return STRING_CHARACTER_NOT_FOUND;
}

char * strncpy(char * r, const char * s, size_t n)
{
	for (size_t i = 0; i < n; i++) r[i] = s[i]; return r;
}

char * strcpy(char * r, const char * s)
{
	strncpy(r, s, strlen(s) + 1);
}

char specifier_type(const char * s, size_t i)
{
	while (++i < strlen(s))
	{
		// Is not a number.
		if (!is_num(s[i]))
		{
			return s[i];
		}
	}
	return (char)-1;
}

size_t specifier_len(const char * s, size_t i)
{
	size_t l = 1;
	while (++i < strlen(s))
	{
		l++;
		// Is not a number.
		if (!is_num(s[i])) break;
	}
	return l;
}

char * reverse(char * r, char * s)
{
	for (int i = 0; i < strlen(s); i++)
	{
		r[i] = s[strlen(s) - 1 - i];
	}
	return r;
}

char * itoa(char * r, int v)
{
	char d[10];
	int i = 0;
	while (v != 0)
	{
		int rem = v % 10;
		r[i++] = '0' + rem;
		v = v/10;
	}
	r[i] = '\0';
	reverse(&d, r);
	strcpy(r, &d);
	return r;
}

char * format(char * r, const char * s, ...)
{
	// Used to iterate over the varargs.
	va_list a;
	char stype, v, *str, hi[10];
	size_t si = 0, ri = 0, slen, index;
	// Sets the address of the varargs.
	va_start(a, r);
	// Loops through the string replacing each specifier.
	while (true)
	{

		// Finds the next specifier index.
		index = find(s + si, '%');
		// If a specifier index was not found.
		if (index == STRING_CHARACTER_NOT_FOUND)
		{
			// We add the rest of the string to the result and return.
			strcpy(r + ri, s + si); break;
		}
		// Copies the next part of the string into the result.
		strncpy(r + ri, s + si, index);
		// Jumps to the specifier index.
		ri += index;
		si += index;
		// Gets the length of the specifer.
		slen = specifier_len(s, si);
		// Gets the type of the specifier.
		stype = specifier_type(s, si);
		// Alters the string according to the type.
		switch (stype)
		{
			case 'c':
				// Adds the char to the string.
				v = (char)va_arg(a, int);
				r[ri] = v;
				ri += 1;
				break;
			case 's':
				// Adds a string to the string.
				str = va_arg(a, char *);
				strncpy(r + ri, str, strlen(str));
				ri += strlen(str);
				break;
			case 'd':
				// Adds the number to the string.
				str = itoa(&hi, va_arg(a, int));
				strncpy(r + ri, str, strlen(str));
				ri += strlen(str);
				break;
		}
		// Skips past the specifier in the source string.
		si += slen;
	}
	// We no longer need the varargs.
	va_end(a);
	// Returns a pointer to the new string.
	return r;
}