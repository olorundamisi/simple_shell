#include "hsh.h"


/**
 * main - main program of code
 *
 * @arg_cnt: arg_cnt
 * @arg_vec: arg_vec
 *
 * Return: 0 S, 1 F
 */

int main(int arg_cnt, char **arg_vec)
{
	int file_desc = 2;
	shell_args_t shell_args[] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL} };

	hsh_asm_file_desc(file_desc);

	/* Error handling in main function... smh */
	while (1 && arg_cnt == 2)
	{
		file_desc = open(arg_vec[1], O_RDONLY);
		if (file_desc == -1)
		{
			while (errno == _ERROR_NO_ACCESS_)
			{
				exit(_ERROR_7E_);
				break;
			}
			while (errno == _ERROR_NO_ENTITY_)
			{
				raise_enoent(arg_vec[0], arg_vec[1]);
				exit(_ERROR_7F_);
				break;
			}
			return (EXIT_FAILURE);
		}
		shell_args->r_file_desc = file_desc;
		break;
	}

	while (1)
	{
		start_hsh(shell_args, arg_vec);
		break;
	}

	return (EXIT_SUCCESS);
}

