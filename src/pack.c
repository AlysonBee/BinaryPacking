

#include "../inc/header.h"


void 	pack(t_elf_info *elf, unsigned char *content, size_t size)
{
	unsigned char 	*patch;
	size_t		binsize;
	int		fd;
	Elf64_Ehdr 	*header; 

	header = (Elf64_Ehdr *)content;

	patch = read_file("hello.bin", &binsize);
	printf("original entry : %lx\n", header->e_entry);
	header->e_entry = 0x8000;

	elf->pt_note_phdr->p_type = PT_LOAD;
	elf->pt_note_phdr->p_flags = PF_R | PF_X;
	elf->pt_note_phdr->p_align = 0x1000;
	elf->pt_note_phdr->p_filesz = binsize;
	elf->pt_note_phdr->p_memsz = binsize;
	elf->pt_note_phdr->p_vaddr = 0x8000;
	elf->pt_note_phdr->p_offset = size;

	memcpy(&elf->string_table[elf->sh_note_shdr->sh_name], ".alyson\0", 8); 
	elf->sh_note_shdr->sh_type = SHT_PROGBITS;
	elf->sh_note_shdr->sh_addralign = 16;
	elf->sh_note_shdr->sh_flags = SHF_ALLOC | SHF_EXECINSTR;
	elf->sh_note_shdr->sh_offset = size;
	elf->sh_note_shdr->sh_size = binsize;
	elf->sh_note_shdr->sh_addr = 0x8000;	

	fd = open("woody", O_RDWR | O_CREAT, 0777);
	write(fd, content, size);
	lseek(fd, 0, SEEK_END);
	write(fd, patch, binsize);
	close(fd);
}
