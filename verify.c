#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
int result;
	printf("Secure Boot verification starting\n");
 result = system("openssl dgst -sha256 -verify public.pem -signature signature.bin firmware_v1.txt > verify_output.txt 2>&1");
 FILE *fp = fopen("verify_output.txt","r");
	if (fp == NULL) 
	{
        printf("Error reading verification result.\n");
        return 1;
    	}

char output[100];
    fgets(output, sizeof(output), fp);
    fclose(fp);

    if (strstr(output, "Verified OK")) {
        printf("Firmware AUTHENTIC. Boot allowed.\n");
    } else {
        printf("Firmware TAMPERED! Boot rejected.\n");
    }

    return 0;

}
