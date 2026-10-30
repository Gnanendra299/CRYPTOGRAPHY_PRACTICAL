/* Small-number RSA demonstration only; not secure for real use. */
#include <stdio.h>
#include <stdint.h>

static uint64_t modpow(uint64_t b, uint64_t e, uint64_t m) {
    uint64_t r=1;
    while(e) {
        if(e&1) r=(r*b)%m;
        b=(b*b)%m;
        e>>=1;
    }
    return r;
}
int main(void) {
    /* p=61, q=53, n=3233, phi=3120, e=17, d=2753 */
    uint64_t message=65, cipher, recovered;
    uint64_t n=3233, e=17, d=2753;
    cipher=modpow(message,e,n);
    recovered=modpow(cipher,d,n);
    printf("Message number : %llu\n",(unsigned long long)message);
    printf("Public key     : (e=%llu, n=%llu)\n",
           (unsigned long long)e,(unsigned long long)n);
    printf("Ciphertext     : %llu\n",(unsigned long long)cipher);
    printf("Private key d  : %llu (demo only)\n",(unsigned long long)d);
    printf("Decrypted      : %llu\n",(unsigned long long)recovered);
    return 0;
}
