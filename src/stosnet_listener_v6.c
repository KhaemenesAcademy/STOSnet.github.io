#include "stosnet_listener_v6.h"
stosnet_v6_decision stosnet_v6_config_check(const stosnet_v6_config *c) {
 if (!c || !c->operator_approved || !c->identity_available ||
     !c->tls13_enforced || !c->peer_auth_required ||
     !c->independent_authority_online || !c->loopback_only ||
     c->production_route_enabled) return STOSNET_V6_DENY;
 if (c->port < 1024 || c->max_connections == 0 || c->max_connections > 8 ||
     c->handshake_deadline_ms < 1000 || c->handshake_deadline_ms > 10000 ||
     c->idle_deadline_ms < 1000 || c->idle_deadline_ms > 30000 ||
     c->max_request_bytes < 1024 || c->max_request_bytes > 65536)
   return STOSNET_V6_DENY;
 return STOSNET_V6_ELIGIBLE;
}
