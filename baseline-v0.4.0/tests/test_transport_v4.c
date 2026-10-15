#include "stosnet_transport_v4.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int recheck(void *ctx,const stosnet_v4_channel_evidence *e,
 const uint8_t binding[STOSNET_V4_BINDING_BYTES],const char *aud,uint64_t now){
 (void)e;(void)binding;(void)aud;(void)now; return *(int*)ctx;
}
int main(void){
 stosnet_v4_channel_evidence e={0};
 stosnet_v4_authority a={0};
 uint8_t binding[STOSNET_V4_BINDING_BYTES]={0};
 int yes=1, count=0;
 #define DENY() do {assert(stosnet_v4_channel_decide(&e,&a,binding,"stosnet",110)==STOSNET_V4_DENY);count++;}while(0)
 DENY();
 e.abi=4; a.abi=4;a.recheck=recheck;a.trusted_ctx=&yes;
 strcpy(e.audience,"stosnet");e.connection_id=1;e.authenticated_at=100;
 e.expires_at=120;e.revocation_epoch=1;e.tls_verified=1;
 e.device_possession_verified=1;e.enrollment_approved=1;e.revocation_fresh=1;
 e.tls_channel_binding[0]=42;e.device_key_fingerprint[0]=8;binding[0]=42;
 assert(stosnet_v4_channel_decide(&e,&a,binding,"stosnet",110)==STOSNET_V4_ALLOW);count++;
 e.tls_verified=0;DENY();e.tls_verified=1;
 e.device_possession_verified=0;DENY();e.device_possession_verified=1;
 e.enrollment_approved=0;DENY();e.enrollment_approved=1;
 e.revocation_fresh=0;DENY();e.revocation_fresh=1;
 e.expires_at=110;DENY();e.expires_at=120;
 e.revocation_epoch=0;DENY();e.revocation_epoch=1;
 e.device_key_fingerprint[0]=0;DENY();e.device_key_fingerprint[0]=8;
 binding[0]=43;DENY();binding[0]=42;
 strcpy(e.audience,"other");DENY();strcpy(e.audience,"stosnet");
 yes=0;DENY();yes=1;
 a.recheck=NULL;DENY();a.recheck=recheck;
 a.trusted_ctx=NULL;DENY();a.trusted_ctx=&yes;
 e.connection_id=0;DENY();e.connection_id=1;
 e.authenticated_at=111;DENY();e.authenticated_at=100;
 e.abi=3;DENY();e.abi=4;
 printf("PASS: %d v0.4 synthetic assertions\n",count);
 return 0;
}
