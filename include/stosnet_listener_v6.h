#ifndef STOSNET_LISTENER_V6_H
#define STOSNET_LISTENER_V6_H
#include <stddef.h>
#include <stdint.h>
/* No network calls from this C17 boundary. Deny-by-default configuration. */
typedef enum { STOSNET_V6_DENY=0, STOSNET_V6_ELIGIBLE=1 } stosnet_v6_decision;
typedef struct {
 uint16_t port;
 uint16_t max_connections;
 uint32_t handshake_deadline_ms;
 uint32_t idle_deadline_ms;
 uint32_t max_request_bytes;
 uint8_t operator_approved;
 uint8_t identity_available;
 uint8_t tls13_enforced;
 uint8_t peer_auth_required;
 uint8_t independent_authority_online;
 uint8_t loopback_only;
 uint8_t production_route_enabled;
} stosnet_v6_config;
stosnet_v6_decision stosnet_v6_config_check(const stosnet_v6_config *cfg);
#endif
