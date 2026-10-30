/* Tiny DSA-style digital signature demonstration.
   Parameters are deliberately tiny and insecure; educational use only. */
#include <stdio.h>
#include <stdint.h>

static int64_t modpow(int64_t b, int64_t e, int64_t m) {
    int64_t r=1;
    while(e>0) { if(e&1) r=(r*b)%m; b=(b*b)%m; e>>=1; }
    return r;
}
static int64_t modinv(int64_t a, int64_t m) {
    int64_t t=0, newt=1, r=m, newr=a%m;
    while(newr) {
        int64_t q=r/newr, tmp=t-q*newt; t=newt; newt=tmp;
        tmp=r-q*newr; r=newr; newr=tmp;
    }
    if(r>1) return -1;
    if(t<0) t+=m;
    return t;
}
int main(void) {
    /* Toy DSA parameters: p=23, q=11, g=4; private x=3 */
    int64_t p=23,q=11,g=4,x=3,h=7,k=6;
    int64_t y=modpow(g,x,p);
    int64_t r=modpow(g,k,p)%q;
    int64_t s=(modinv(k,q)*(h+x*r))%q;
    int64_t w=modinv(s,q);
    int64_t u1=(h*w)%q, u2=(r*w)%q;
    int64_t v=((modpow(g,u1,p)*modpow(y,u2,p))%p)%q;
    printf("Toy DSA parameters: p=%lld, q=%lld, g=%lld\n",
           (long long)p,(long long)q,(long long)g);
    printf("Public key y      : %lld\n",(long long)y);
    printf("Message hash h    : %lld (toy value)\n",(long long)h);
    printf("Signature (r,s)   : (%lld, %lld)\n",(long long)r,(long long)s);
    printf("Verification      : %s\n",(r>0 && s>0 && v==r)?"VALID":"INVALID");
    printf("Warning: tiny parameters and fixed nonce are NOT secure.\n");
    return 0;
}
