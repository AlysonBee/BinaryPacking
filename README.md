# BinaryPacking
A repo of binary packing stuff 

My first packer is an ELF binary packer based off of `elfinject.c` in the bookk Practical Binary Analysis.<br><br>

The technique revolves around appending executable code to the end of a target binary, and the modifying a PT_NOTE program header and SHT_NOTE section to directly reference this newly added code section.<br>
These two sections are changed to executable program and section headers respectively; the first PT_NOTE section is overwritten and changed to a PT_LOAD section and has its address and offset point to my newly injected code, and the SHT_NOTE section is changed to a SHT_PROGBITS section also pointing to my injected code.<br><br>

Lastly, the entrypoint of the program in the program header is changed to point to the address of my injected code so it jumps here on program startup.
