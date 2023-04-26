#include "shell.h"

/**
  * get_args_inter - Read and return arguments
  * from standard input in iterative mode
  * Return: input_t containing arguments read
  * or NULL if empty space or error
  */
input_t *get_args_inter(void)
{
	char c, buf[1024];
	input_t *inp = malloc(sizeof(input_t));
	int is_eof = 0, buf_sz = 1024, sz = 0,  itr, last_char = -1;

	init_array(buf, buf_sz);
	for (c = _fgetc(STDIN_FILENO); c != '\n' && c != EOF && c != ';'; sz++)
	{
		buf[sz] = c;
		c = _fgetc(STDIN_FILENO);
	}
	if (sz == 0)
	{
		if (inp == NULL || c == '\n')
		{
			free(inp);
			return (NULL);
		}
		inp->data = NULL;
		inp->is_eof = 1;
		return (inp);
	}
	else
	{
		for (itr = 0; itr < sz; itr++) /* remove extra spaces at end of input */
		{
			if (buf[itr] != ' ' && buf[itr] != '\n')
				last_char = itr;
		}
	}
	if (c == '\n')
		is_eof = 1;
	inp->is_eof = is_eof;
	if (last_char < 0) /* only blank spaces */
	{
		free(inp);
		return (NULL);
	}
	inp->data = _strndup(buf, last_char + 1);
	return (inp);
}

/**
  * get_args_non_inter - Read and return arguments
  * from standard input in non iterative mode
  * Return: input_t containing arguments read
  * or NULL if empty space or error
  */
input_t *get_args_non_inter(void)
{
	char buf[1024];
	char c;
	int num_char;
	input_t *inp;

	init_array(buf, 1024);
	num_char = 0;
	c = _fgetc(STDIN_FILENO);
	while (c != '\n' && c != EOF && c != ';')
	{
		buf[num_char] = c;
		num_char++;
		c = _fgetc(STDIN_FILENO);
	}
	inp = malloc(sizeof(input_t));

	if (inp == NULL || num_char == 0)
	{
		free(inp);
		return (NULL);
	}
	inp->is_eof = 0;
	inp->data = _strndup(buf, num_char);
	return (inp);
}


/**
  * is_exit - Checks whether the user typed in
  * 'exit' or not
  * @s: pointer to string representing user input
  * Return: 1 if true and 0 if false
  */
int is_exit(const char *s)
{
	return (!_strcmp(s, "exit"));
}

/**
  * free_input - Free memory space allocated to
  * user created data type 'input_t'
  * @inp: pointer to input_t data type
  * Return: void
  */
void free_input(input_t *inp)
{
	free(inp->data);
	free(inp);
}
