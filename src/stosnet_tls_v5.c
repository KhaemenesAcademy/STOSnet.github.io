#include "stosnet_tls_v5.h"
static int same(const uint8_t *a,const uint8_t *b,size_t n) {
 unsigned diff=0; size_t i;
 for(i=0;i<n;i++) diff|=(unsigned)(a[i]^b[i]);
 return diff==0;
}
static int nonzero(const uint8_t *a,size_t n) {
 unsigned v=0; size_t i; for(i=0;i<n;i++)v|=a[i]; return v!=0;
}
stosnet_tls_decision stosnet_tls_gate(const stosnet_tls_evidence *e,
 const uint8_t binding[STOSNET_TLS_BINDING_LEN],
 const uint8_t device[STOSNET_TLS_ID_LEN]) {
 if(!e||!binding||!device) return STOSNET_TLS_DENY;
 if(!e->authenticated_tls||!e->peer_key_proven||!e->device_enrolled||
    !e->device_not_revoked||!e->origin_verified||!e->authority_allow)
    return STOSNET_TLS_DENY;
 if(e->tls_version<0x0304u||!e->now_seconds||
    e->expires_seconds<=e->now_seconds) return STOSNET_TLS_DENY;
 if(!nonzero(binding,32)||!nonzero(device,32)||
    !same(e->channel_binding,binding,32)||
    !same(e->device_key_id,device,32)) return STOSNET_TLS_DENY;
 return STOSNET_TLS_ALLOW;
}
