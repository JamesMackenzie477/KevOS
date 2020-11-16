#include "string.h"

// Compares two strings and returns the difference.
size_t strcmp(const char * a, const char * b)
{
	while (*a && (*a == *b))
	{
		a++;
		b++;
	}
	return *a - *b;
}

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
	return STRING_CHARACTER_NOT_FOUND;
}

// Copies n characters from the source string to the destination buffer.
char * strncpy(char * dst, const char * src, size_t n)
{
	for (size_t i = 0; i < n; i++) dst[i] = src[i]; return dst;
}

// Copies the full source string to the destination buffer.
char * strcpy(char * dst, const char * src)
{
	return strncpy(dst, src, strlen(src) + 1);
}

// Reverses the source string and stores it in the destination buffer.
char * strrev(char * src)
{
	for(int i = strlen(src) - 1, y = 0; i > y; i--, y++)
	{
		char temp = src[i];
		src[i] = src[y];
		src[y] = temp;
	}
	// Returns the modified string.
	return src;
}

char * itoa(char * r, uint32_t v, int base)
{
	int i = 0;
	if (v == 0)
	{
		r[i++] = '0';
	}
	else
	{
		while (v != 0)
		{
			uint32_t rem = v % base;
			r[i++] = (rem < 10) ? ('0' + rem) : ('a' + (rem - 10));
			v = v/base;
		}	
	}

	r[i] = '\0';
	strrev(r);
	return r;
}

char specifier_type(const char * s)
{
	for (size_t i = 0; i < strlen(s); i++)
	{
		// Is not a number.
		if (!is_num(s[i])) return s[i];
	}
	return (char)-1;
}

size_t specifier_len(const char * s)
{
	for (size_t i = 1; i < strlen(s); i++)
	{
		// Is not a number.
		if (!is_num(s[i])) return i + 1;
	}
	return 1;
}

char * format(char * dst, const char * src, va_list args)
{
	int int_arg;

	char stype, char_arg, *str_arg, int_str[10];

	size_t dst_i = 0, src_i = 0, slen, index;

	// Loops through the string replacing each specifier.
	while (true)
	{

		// Finds the next specifier index.
		index = find(&src[src_i], '%');
		// If a specifier index was not found.
		if (index == STRING_CHARACTER_NOT_FOUND)
		{
			// We add the rest of the string to the result and return.
			strcpy(&dst[dst_i], &src[src_i]); break;
		}
		// Copies the next part of the string into the result.
		strncpy(&dst[dst_i], &src[src_i], index);
		// Jumps to the specifier index.
		dst_i += index;
		src_i += index;
		// Gets the length of the specifer.
		slen = specifier_len(&src[src_i]);
		// Gets the type of the specifier.
		stype = specifier_type(&src[src_i]);
		// Alters the string according to the type.
		switch (stype)
		{
			case 'c':
				// Gets the argument as a char.
				char_arg = (char)va_arg(args, int);
				// Adds the character to the result string.
				dst[dst_i] = char_arg;
				// Increments the index of the result.
				dst_i += sizeof(char);
				// Breaks out of the switch.
				break;
			case 's':
				// Gets the argument as a string.
				str_arg = va_arg(args, char *);
				// Copies the string into the result string.
				strncpy(&dst[dst_i], str_arg, strlen(str_arg));
				// Increments the result string index.
				dst_i += strlen(str_arg);
				// Breaks out of the switch.
				break;
			case 'd':
				// Gets the arguments as an int.
				int_arg = va_arg(args, int);
				// Converts the int to a string.
				itoa(&int_str, int_arg, 10);
				// Copies the string into the result string.
				strncpy(&dst[dst_i], &int_str, strlen(&int_str));
				// Increments the result string index.
				dst_i += strlen(&int_str);
				// Breaks out of the switch.
				break;
			case 'x':
				// Gets the arguments as an int.
				int_arg = va_arg(args, int);
				// Converts the int to a string.
				itoa(&int_str, int_arg, 16);
				// Copies the string into the result string.
				strncpy(&dst[dst_i], &int_str, strlen(&int_str));
				// Increments the result string index.
				dst_i += strlen(&int_str);
				// Breaks out of the switch.
				break;
			case 'l':
				// Gets the arguments as an int.
				int_arg = va_arg(args, uint64_t);
				// Converts the int to a string.
				itoa(&int_str, int_arg, 16);
				// Copies the string into the result string.
				strncpy(&dst[dst_i], &int_str, strlen(&int_str));
				// Increments the result string index.
				dst_i += strlen(&int_str);
				// Breaks out of the switch.
				break;
		}
		// Skips past the specifier in the source string.
		src_i += slen;
	}
	// Returns a pointer to the new string.
	return dst;
}

void * memset(void * ptr, int value, size_t num)
{
	for (size_t i = 0; i < num; i++) ((char*)ptr)[i] = value;
	return ptr;
}