// for unsigned int, shift right is assembled to srli

// riscv64-unknown-elf-gcc -march=rv32ima -mabi=ilp32 -c -g test.c -o test.o
// riscv64-unknown-elf-objdump -S test.o
void foo()
{
	unsigned int i = 0x80000000;
	i = i >> 4;
}