#include "stosnet_listener_v6.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
 stosnet_v6_config c={18443,2,5000,10000,8192,1,1,1,1,1,1,0};
 assert(stosnet_v6_config_check(0)==STOSNET_V6_DENY);
 assert(stosnet_v6_config_check(&c)==STOSNET_V6_ELIGIBLE);
 c.loopback_only=0; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.loopback_only=1;
 c.peer_auth_required=0; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.peer_auth_required=1;
 c.identity_available=0; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.identity_available=1;
 c.independent_authority_online=0; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.independent_authority_online=1;
 c.operator_approved=0; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.operator_approved=1;
 c.tls13_enforced=0; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.tls13_enforced=1;
 c.production_route_enabled=1; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.production_route_enabled=0;
 c.max_connections=9; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.max_connections=2;
 c.port=443; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY); c.port=18443;
 c.max_request_bytes=65537; assert(stosnet_v6_config_check(&c)==STOSNET_V6_DENY);
 puts("STOSnet v0.6 C17 configuration boundary: 11 assertions passed");
 return 0;
}
