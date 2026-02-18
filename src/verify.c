#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_event(const char *message) {
    FILE *log = fopen("security_log.txt", "a");
    if (log != NULL) {
        fprintf(log, "%s\n", message);
        fclose(log);
    }
}



int main() {

    printf("ECU Secure Boot Starting...\n");

    // Step 1: verify signature
    system("openssl dgst -sha256 -verify public.pem -signature signature.bin firmware_v1.txt > verify_output.txt 2>&1");

    FILE *fp = fopen("verify_output.txt", "r");
    if (fp == NULL) {
        printf("Verification file error\n");
        return 1;
    }

    char result[100];
    fgets(result, sizeof(result), fp);
    fclose(fp);

    if (!strstr(result, "Verified OK")) {
        printf("SECURITY ALERT: Firmware tampered. Boot blocked.\n");
	log_event("Tampered firmware detected - boot blocked");
        return 0;
    }

    // Step 2: version check
    FILE *fw = fopen("firmware_v1.txt", "r");
    FILE *cv = fopen("current_version.txt", "r");

    char fw_version[20];
    char current_version[20];

    fgets(fw_version, sizeof(fw_version), fw);
    fgets(current_version, sizeof(current_version), cv);

    fclose(fw);
    fclose(cv);

    if (strstr(fw_version, current_version)) {
        printf("Firmware authentic and version valid.\n");
        printf("Vehicle ready to start safely.\n");
	log_event("Secure boot successful");	
    } else {
        printf("WARNING: Firmware version mismatch! Possible rollback attack.\n");
	log_event("firmware rollback detected - version mismatch");

        printf("Boot blocked.\n");
    }

    return 0;
}
