#include "stosnet_transport_v4.h"
#include <string.h>
static int nonzero(const uint8_t *p,size_t n) {
 size_t i; uint8_t x=0; for(i=0;i<n;i++) x|=p[i]; return x!=0;
}
static int bounded_audience(const char *s,size_t cap) {
 size_t i; if(!s||!s[0])return 0;
 for(i=0;i<cap;i++) {
   unsigned char c=(unsigned char)s[i];
   if(c==0)return 1;
   if(c<0x21||c>0x7e)return 0;
 }
 return 0;
}
static int equal_fixed(const uint8_t *a,const uint8_t *b,size_t n) {
 size_t i; uint8_t d=0;
 for(i=0;i<n;i++) d|=(uint8_t)(a[i]^b[i]);
 return d==0;
}
stosnet_v4_decision stosnet_v4_channel_decide(
 const stosnet_v4_channel_evidence *e,
 const stosnet_v4_authority *a,
 const uint8_t binding[STOSNET_V4_BINDING_BYTES],
 const char *audience,uint64_t now) {
 if(!e||!a||!binding||!audience) return STOSNET_V4_DENY;
 if(e->abi!=STOSNET_TRANSPORT_ABI||a->abi!=STOSNET_TRANSPORT_ABI||
    !a->recheck||!a->trusted_ctx) return STOSNET_V4_DENY;
 if(!bounded_audience(e->audience,sizeof e->audience)||
    !bounded_audience(audience,STOSNET_V4_MAX_AUDIENCE)||
    strcmp(e->audience,audience)!=0) return STOSNET_V4_DENY;
 if(!e->tls_verified||!e->device_possession_verified||
    !e->enrollment_approved||!e->revocation_fresh) return STOSNET_V4_DENY;
 if(!e->connection_id||!e->revocation_epoch||
    !e->authenticated_at||now<e->authenticated_at||
    now>=e->expires_at||e->authenticated_at>=e->expires_at) return STOSNET_V4_DENY;
 if(!nonzero(binding,STOSNET_V4_BINDING_BYTES)||
    !nonzero(e->tls_channel_binding,STOSNET_V4_BINDING_BYTES)||
    !nonzero(e->device_key_fingerprint,STOSNET_V4_DEVICE_BYTES)||
    !equal_fixed(e->tls_channel_binding,binding,STOSNET_V4_BINDING_BYTES))
    return STOSNET_V4_DENY;
 return a->recheck(a->trusted_ctx,e,binding,audience,now)==1?
    STOSNET_V4_ALLOW:STOSNET_V4_DENY;
}
