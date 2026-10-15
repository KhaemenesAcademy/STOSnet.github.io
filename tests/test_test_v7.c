#include "stosnet_test_v7.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    stosnet_v7_test_config c = {18443,1,1,1,1,1,1,1,1,1};
    assert(stosnet_v7_test_config_check(NULL)==STOSNET_V7_DENY);
    assert(stosnet_v7_test_config_check(&c)==STOSNET_V7_TEST_ONLY);
    c.port=9844; assert(stosnet_v7_test_config_check(&c)==STOSNET_V7_DENY);
    c.port=80; assert(stosnet_v7_test_config_check(&c)==STOSNET_V7_DENY);
    c.port=18443;
    for (int i=0;i<9;i++) {
        stosnet_v7_test_config x=c;
        uint8_t *flags[]={&x.explicit_test_approval,&x.loopback_only,
          &x.tls13_required,&x.peer_certificate_required,&x.identity_selected,
          &x.app_routes_disabled,&x.proxy_disabled,&x.storage_disabled,
          &x.local_authority_disabled};
        *flags[i]=0;
        assert(stosnet_v7_test_config_check(&x)==STOSNET_V7_DENY);
    }
    puts("STOSnet v0.7: 12 fail-closed synthetic assertions passed");
    return 0;
}
