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

char * strncpy(const char * s, char * r, size_t n)
{
	for (size_t i = 0; i < n; i++) r[i] = s[i]; return r;
}

char * strcpy(const char * s, char * r)
{
	strncpy(s, r, strlen(s) + 1);
}

char specifier_type(const char * s, size_t i)
{
	while (++i < strlen(s))
	{
		// Is not a number.
		if (!is_num(s, i))
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
		if (!is_num(s, i)) break;
	}
	return l;
}

char * format(const char * s, char * r, ...)
{
	// Used to iterate over the varargs.
	va_list a;

	char t, v;
	// Indexes.
	size_t si = 0, ri = 0, len, index;
	// Copies the string into the result buffer.
	// strcpy(s, r);

	// Sets the address of the varargs.
	va_start(a, r);

	while (true)
	{

		// Finds the next specifier index.
		index = find(s + si, '%');

		if (index == STRING_CHARACTER_NOT_FOUND)
		{
			strcpy(s + si, r + ri);
			break;
		}

		strncpy(s + si, r + ri, index);

		ri += index;
		si += index;

		// Gets the length of the specifer.
		len = specifier_len(s, si);
		t 	= specifier_type(s, si);

		switch (t)
		{
			case 'c':
				v = (char)va_arg(a, int);
				r[ri] = v;
				ri += 1;

		}

		si += len;
	}

	va_end(a);

	return r;
}