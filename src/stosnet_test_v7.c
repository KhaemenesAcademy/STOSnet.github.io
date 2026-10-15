#include "stosnet_test_v7.h"
stosnet_v7_result stosnet_v7_test_config_check(const stosnet_v7_test_config *c) {
    if (!c) return STOSNET_V7_DENY;
    if (c->port < 1024 || c->port == 9844) return STOSNET_V7_DENY;
    if (c->explicit_test_approval != 1 || c->loopback_only != 1 ||
        c->tls13_required != 1 || c->peer_certificate_required != 1 ||
        c->identity_selected != 1 || c->app_routes_disabled != 1 ||
        c->proxy_disabled != 1 || c->storage_disabled != 1 ||
        c->local_authority_disabled != 1) return STOSNET_V7_DENY;
    return STOSNET_V7_TEST_ONLY;
}
