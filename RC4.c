/* RC4 educational demonstration; RC4 is obsolete and insecure. */
#include <stdio.h>
#include <string.h>

void rc4(const unsigned char *key, int keylen,
         const unsigned char *in, unsigned char *out, int len) {
    unsigned char s[256], t;
    int i, j=0, k;
    for (i=0;i<256;i++) s[i]=(unsigned char)i;
    for (i=0;i<256;i++) {
        j=(j+s[i]+key[i%keylen])&255;
        t=s[i]; s[i]=s[j]; s[j]=t;
    }
    i=0; j=0;
    for (k=0;k<len;k++) {
        i=(i+1)&255; j=(j+s[i])&255;
        t=s[i]; s[i]=s[j]; s[j]=t;
        out[k]=in[k]^s[(s[i]+s[j])&255];
    }
}
int main(void) {
    const unsigned char key[]="secret";
    const unsigned char text[]="Hello RC4";
    unsigned char cipher[sizeof(text)], plain[sizeof(text)];
    int i, n=(int)strlen((const char *)text);
    rc4(key,(int)strlen((const char *)key),text,cipher,n);
    printf("Original : %s\nEncrypted: ",text);
    for(i=0;i<n;i++) printf("%02X",cipher[i]);
    rc4(key,(int)strlen((const char *)key),cipher,plain,n);
    plain[n]='\0';
    printf("\nDecrypted: %s\n",plain);
    return 0;
}
