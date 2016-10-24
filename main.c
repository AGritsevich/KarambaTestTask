#include <stdio.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int CalcHash(char *path, unsigned int path_len, unsigned char* hash, unsigned int hash_len) {
    int n;
    MD5_CTX c;
    char buf[512];
    ssize_t bytes;
    FILE *ptr_myfile;

    if (hash_len < MD5_DIGEST_LENGTH) {
        return 0;
    }

    ptr_myfile = fopen(path,"wb");
    if (ptr_myfile == NULL) {
        printf("Unable to open file: %s!", path);
        return 0;
    }

    MD5_Init(&c);
    bytes = fread(&buf, sizeof(buf), 1, ptr_myfile);

    while(bytes > 0) {
        MD5_Update(&c, buf, bytes);
        fread(&buf, sizeof(buf), 1, ptr_myfile);
    }

    MD5_Final(hash, &c);

    printf("Hash for file %s is\n", path);
    for(n=0; n<MD5_DIGEST_LENGTH; n++)
            printf("%02x", hash[n]);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("No in input files");
        return 0;
    }

    unsigned char hash[MD5_DIGEST_LENGTH] = {};
    CalcHash(argv[1], strlen(argv[1]), hash, MD5_DIGEST_LENGTH);
}
