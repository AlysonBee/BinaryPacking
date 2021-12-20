

#include "../inc/header.h"

// Extremely insecure!
void	_read_write_exec(Elf64_Phdr *program_headers, int pheader_count)
{
	Elf64_Phdr *curr_program;
	int	count;

	count = 0;
	curr_program = program_headers;
	while (count < pheader_count)
	{
		if (curr_program->p_type == PT_LOAD)
		{
			curr_program->p_flags = PF_X | PF_W | PF_R;
		}
		count++;
		curr_program = (Elf64_Phdr *)((void *)curr_program + sizeof(Elf64_Phdr));
	}
}

void	_42_xor(unsigned char *file_buffer, size_t offset, size_t size)
{
	size_t count;
	size_t offset_tracker;

	printf("offset is %lx\n", offset);
	printf("size is %zu\n", size);
	count = 0;
	offset_tracker = offset;
	while (count < size)
	{
		file_buffer[offset_tracker] ^= 42;
		count++;
		offset_tracker++;
	}
	return ;
}


void	encrypt_text_section(Elf64_Shdr *section_headers, int section_count, 
	char *string_table, unsigned char *file_buffer)
{
	Elf64_Shdr *curr_section;
	int counter;

	counter = 0;
	curr_section = section_headers;
	while (counter < section_count)
	{
		if (strcmp(&string_table[curr_section->sh_name], ".text") == 0)
		{
			_42_xor(file_buffer, curr_section->sh_offset,
				curr_section->sh_size);				
			break ;
		}
		counter++;
		curr_section = (Elf64_Shdr *)((void *)curr_section + sizeof(Elf64_Shdr));
	}
	printf("Test\n");
}


