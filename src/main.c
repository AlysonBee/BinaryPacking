
#include "../inc/header.h"

/*
** This is a PT_NOTE elf file rewrite.
*/

int	main(int argc, char **argv)
{
	unsigned char 	*content;
	size_t		size;
	t_elf_info	*elf;
	
	if (argc != 2)
	{
		printf("Usage ./%s [elf file]\n", argv[0]);
		return (1);
	}

	content = read_file(argv[1], &size);
	if (!content)
	{
		return (2);
	}

	elf = setup_elf_info(content, size);

	pack(elf, content, size);
	return (0);
}
