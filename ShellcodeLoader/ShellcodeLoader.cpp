#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* fp;

	if (argc < 2) {
		printf("[-] Please provide the shellcode filename\n");
		return 0;
	}

	printf("[!] Current Process ID: %d.\n", GetCurrentProcessId());
	printf("[!] Load Sourcecode File: %s.\n", argv[1]);

	fp = fopen(argv[1], "rb");
	if (!fp) {
		printf("[-] Uable to open file. Error: %d.\n", GetLastError());
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	printf("[!] File size of shellcode: %d.\n", size);
	BYTE* buf = (BYTE*)VirtualAlloc(NULL, size, 0x3000, 0x40); // MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	printf("[!] Shellcode allocated at %p.\n", buf);

	if (!fread(buf, size, 1, fp)) {
		printf("[-] Read shellcode file failed. Error: %d.\n", GetLastError());
		return 0;
	}

	system("pause");
	((void(*)())buf)();

	return 0;
}