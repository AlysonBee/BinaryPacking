

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

	printf("p_vaddr %lx\n", elf->pt_note_phdr->p_vaddr);
	printf("sh_addr %lx\n", elf->sh_note_shdr->sh_addr);
	
	printf("p_offset %ld\n", elf->pt_note_phdr->p_offset);
	printf("sh_offset %ld\n", elf->sh_note_shdr->sh_offset);

	printf("p_addr %ld\n", elf->pt_note_phdr->p_paddr);
	printf("p_filesz %ld\n", elf->pt_note_phdr->p_filesz);
	
	printf("p_memsz %ld\n", elf->pt_note_phdr->p_memsz);

	size_t n = (size % 4096) - (0x800000 % 4096);
	printf("section is now %lx\n", n + 0x800000);
	printf("p_offset %% 4096 is %ld\n", elf->pt_note_phdr->p_offset);
	printf("p_vaddr  %% 4096 is %ld\n", elf->pt_note_phdr->p_vaddr);
	printf("p_offset %% p_align is %ld\n",
		elf->pt_note_phdr->p_offset  % 0x1000);
	
	// patch program
	elf->pt_note_phdr->p_type = PT_LOAD;
	elf->pt_note_phdr->p_flags = PF_R | PF_X;
	elf->pt_note_phdr->p_align = 0x1000;
	elf->pt_note_phdr->p_filesz = binsize;
	elf->pt_note_phdr->p_memsz = binsize;
	elf->pt_note_phdr->p_vaddr = 0x800000 + n;
	elf->pt_note_phdr->p_paddr = 0x800000 + n;
	elf->pt_note_phdr->p_offset = size;
	

	// patch section 
	elf->sh_note_shdr->sh_type = SHT_PROGBITS;
	elf->sh_note_shdr->sh_addralign = 16;
	elf->sh_note_shdr->sh_flags = SHF_ALLOC | SHF_EXECINSTR;
	elf->sh_note_shdr->sh_offset = size;
	elf->sh_note_shdr->sh_size = binsize;
	elf->sh_note_shdr->sh_link = 0;
	elf->sh_note_shdr->sh_info = 0;
	elf->sh_note_shdr->sh_addr = 0x800000 + n;	
	elf->sh_note_shdr->sh_entsize = 0;

	printf("e_entry (before) %lx\n", header->e_entry);


	header->e_entry = elf->pt_note_phdr->p_vaddr;

	printf("e_entry is %lx\n", header->e_entry);
	fd = open("woody", O_RDWR | O_CREAT, 0777);
	write(fd, content, size);
	lseek(fd, 0, SEEK_END);
	write(fd, patch, binsize);
	close(fd);
}
