nasm -f bin hello.s -o hello.bin
nasm -f bin encryptor.s -o encryptor.bin
gcc -o packer *.c
rm woody
