#include "stosnet_tls_v5.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
int main(void){
 stosnet_tls_evidence e={0}; uint8_t b[32],d[32]; int tests=0;
 memset(b,0x21,32);memset(d,0x32,32);
 assert(stosnet_tls_gate(NULL,b,d)==STOSNET_TLS_DENY);tests++;
 assert(stosnet_tls_gate(&e,b,d)==STOSNET_TLS_DENY);tests++;
 memcpy(e.channel_binding,b,32);memcpy(e.device_key_id,d,32);
 e.now_seconds=100;e.expires_seconds=110;e.tls_version=0x0304;
 e.authenticated_tls=1;e.peer_key_proven=1;e.device_enrolled=1;
 e.device_not_revoked=1;e.origin_verified=1;e.authority_allow=1;
 assert(stosnet_tls_gate(&e,b,d)==STOSNET_TLS_ALLOW);tests++;
 e.authenticated_tls=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.authenticated_tls=1;
 e.peer_key_proven=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.peer_key_proven=1;
 e.device_enrolled=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.device_enrolled=1;
 e.device_not_revoked=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.device_not_revoked=1;
 e.origin_verified=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.origin_verified=1;
 e.authority_allow=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.authority_allow=1;
 e.tls_version=0x0303;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.tls_version=0x0304;
 e.expires_seconds=100;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.expires_seconds=110;
 b[0]^=1;assert(stosnet_tls_gate(&e,b,d)==0);tests++;b[0]^=1;
 d[0]^=1;assert(stosnet_tls_gate(&e,b,d)==0);tests++;d[0]^=1;
 e.channel_binding[0]=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.channel_binding[0]=0x21;
 e.device_key_id[0]=0;assert(stosnet_tls_gate(&e,b,d)==0);tests++;e.device_key_id[0]=0x32;
 assert(stosnet_tls_gate(&e,NULL,d)==0);tests++;
 assert(stosnet_tls_gate(&e,b,NULL)==0);tests++;
 printf("PASS: %d synthetic TLS evidence boundary assertions\\n",tests);return 0;
}
