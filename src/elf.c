

#include "../inc/header.h"

t_elf_info	*malloc_elf_info(void)
{
	t_elf_info	*elf;
	
	elf = (t_elf_info *)malloc(sizeof(t_elf_info));
	if (!elf)
	{
		fprintf(stderr, "Run out of memory\n");
		return (NULL);
	}
	return (elf);
}

Elf64_Shdr	*get_sh_note_shdr(Elf64_Shdr *section_headers, int sheader_count)
{
	Elf64_Shdr	*sh_note_shdr;
	int		count;

	sh_note_shdr = section_headers;
	count = 0;
	while (count < sheader_count)
	{
		if (sh_note_shdr->sh_type == SHT_NOTE)
		{
			printf("SHT_NOTE section header found\n");
			return (sh_note_shdr);
		}
		sh_note_shdr = (Elf64_Shdr *)((void *)sh_note_shdr + sizeof(Elf64_Shdr));
		count++;
	}
	printf("No SHT_NOTE section found. Binary is possibly hardened against SHT_NOTE injection.\n");
	return (NULL);
}

Elf64_Phdr 	*get_pt_note_phdr(Elf64_Phdr *program_headers, int pheader_count)
{
	Elf64_Phdr	*pt_note_phdr;
	int		count;

	pt_note_phdr = program_headers;
	count = 0;
	while (count < pheader_count)
	{
		if (pt_note_phdr->p_type == PT_NOTE)
		{
			printf("PT_NOTE prog header found\n");
			return (pt_note_phdr);
		}
		pt_note_phdr = (Elf64_Phdr *)((void *)pt_note_phdr + sizeof(Elf64_Phdr));
		count++;
	}
	printf("No PT_NOTE program header found. Binary is possibly hardened against Note injection.\n");
	return (NULL);
}

void		*get_section(
	Elf64_Shdr *section_headers, 
	int section_count, 
	unsigned char *content, 
	size_t *size, 
	char *section_name,
	char *string_table)
{
	Elf64_Shdr 	*curr_section;
	void		*text_section;
	int 		count;

	count = 0;
	curr_section = section_headers;
	while (count < section_count)
	{
		if (strcmp(&string_table[curr_section->sh_name], section_name) == 0)
		{
			*size = curr_section->sh_size;
			return (&content[curr_section->sh_offset]);
		}
		printf("section name : %s\n", &string_table[curr_section->sh_name]);
		count++;
		curr_section = (Elf64_Shdr *)((void *)curr_section + sizeof(Elf64_Shdr));
	}
	printf("Text section label not found. Possibly stripped binary\n");
	return (NULL);
}

char		*get_string_table(Elf64_Shdr *section_headers, int e_shstrndx,
	int sheader_count,
	unsigned char *content)
{
	Elf64_Shdr *trav;
	int count;
	char *string_table;

	trav = section_headers;
	count = 0;
	while (count < sheader_count && count < e_shstrndx)
	{
		trav = (Elf64_Shdr *)((void *)trav + sizeof(Elf64_Shdr));
		count++;
	}
	string_table = &content[trav->sh_offset];
	return (string_table);
}

t_elf_info	*setup_elf_info(unsigned char *content, size_t size)
{
	t_elf_info *elf;

	elf = malloc_elf_info();
	if (!elf)
		return (NULL);

	Elf64_Ehdr *header;
	Elf64_Phdr *program_headers;
	Elf64_Shdr *section_headers;
	int	   sheader_count;
	int	   pheader_count;
	char 	   *string_table;

	header = (Elf64_Ehdr *)content;
	program_headers = (Elf64_Phdr *)&content[header->e_phoff];
	section_headers = (Elf64_Shdr *)&content[header->e_shoff];
	sheader_count = header->e_shnum;
	pheader_count = header->e_phnum;

	elf->string_table = get_string_table(section_headers, header->e_shstrndx, sheader_count, content);

	elf->pt_note_phdr = get_pt_note_phdr(program_headers, pheader_count);
	if (!elf->pt_note_phdr)
		return (NULL);
	
	elf->sh_note_shdr = get_sh_note_shdr(section_headers, sheader_count);
	if (!elf->sh_note_shdr)
		return (NULL);

	elf->text_section = get_section(section_headers, sheader_count, content, &elf->text_size, 
		".text", elf->string_table);
	if (!elf->text_section)
		return (NULL);

	return (elf);	
}






