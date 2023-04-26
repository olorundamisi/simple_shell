#include "shell.h"

/**
  * _printf - String format printer
  * @fmt: format of the string
  *
  * Return: integer number of characters printed
  */
int _printf(char *fmt, ...)
{
	int ct = 0, is_format = 0, i = 0;
	va_list list;
	char *temp, *data;

	va_start(list, fmt);
	for (temp = fmt; temp != NULL && temp[ct] != '\0'; ct++)
	{
		if (temp[ct] == '%')
		{
			if (is_format)
			{
				i += write(2, temp, ct);
				temp = temp + ct + 1;
				is_format = 0;
			}
			else
			{
				is_format = 1;
				i += write(2, temp, ct);
				temp = temp + ct;
			}
			ct = 0;
		}
		else if (is_format && (temp[ct] == 's'))
		{
			data = va_arg(list, char *);
			i += write(2, data, _strlen(data));
			is_format = 0;
			temp = temp + ct + 1;
			ct = 0;
		}
	}
	va_end(list);
	if (ct)
		i += write(2, temp, ct);
	return (i);
}
