

#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <elf.h>
#include <unistd.h>
#include <fcntl.h>


typedef struct s_elf_info
{
	unsigned char 	*content;
	size_t		size;
	void 		*text_section;
	size_t		text_size;
	Elf64_Phdr	*pt_note_phdr;	
	Elf64_Shdr	*sh_note_shdr;
	char		*string_table;
	char		*sh_note_string;
}		t_elf_info; 


// Misc
unsigned char   *read_file(char *filename, size_t *size);



t_elf_info      *setup_elf_info(unsigned char *content, size_t size);


void 		pack(t_elf_info *elf, unsigned char *content, size_t size);


// encryptor
void	encrypt_text_section(Elf64_Shdr *section_headers, int section_count, 
	char *string_table, unsigned char *file_buffer);

void _read_write_exec(Elf64_Phdr *program_headers, int pheader_count);

#endif 
