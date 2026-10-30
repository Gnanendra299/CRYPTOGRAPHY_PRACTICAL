/* Diffie-Hellman key exchange toy example; small values are not secure. */
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
    uint64_t p=23, g=5;
    uint64_t alice_private=6, bob_private=15;
    uint64_t alice_public=modpow(g,alice_private,p);
    uint64_t bob_public=modpow(g,bob_private,p);
    uint64_t alice_secret=modpow(bob_public,alice_private,p);
    uint64_t bob_secret=modpow(alice_public,bob_private,p);
    printf("Public parameters: p=%llu, g=%llu\n",
           (unsigned long long)p,(unsigned long long)g);
    printf("Alice public key : %llu\n",(unsigned long long)alice_public);
    printf("Bob public key   : %llu\n",(unsigned long long)bob_public);
    printf("Alice shared key : %llu\n",(unsigned long long)alice_secret);
    printf("Bob shared key   : %llu\n",(unsigned long long)bob_secret);
    printf("Keys match       : %s\n",alice_secret==bob_secret?"YES":"NO");
    return 0;
}
