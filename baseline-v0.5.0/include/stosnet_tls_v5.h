#ifndef STOSNET_TLS_V5_H
#define STOSNET_TLS_V5_H
#include <stddef.h>
#include <stdint.h>
#define STOSNET_TLS_BINDING_LEN 32u
#define STOSNET_TLS_ID_LEN 32u
typedef enum {
 STOSNET_TLS_DENY=0, STOSNET_TLS_ALLOW=1
} stosnet_tls_decision;
typedef struct {
 uint8_t channel_binding[STOSNET_TLS_BINDING_LEN];
 uint8_t device_key_id[STOSNET_TLS_ID_LEN];
 uint64_t now_seconds, expires_seconds;
 uint32_t tls_version;
 unsigned authenticated_tls:1;
 unsigned peer_key_proven:1;
 unsigned device_enrolled:1;
 unsigned device_not_revoked:1;
 unsigned origin_verified:1;
 unsigned authority_allow:1;
} stosnet_tls_evidence;
/* This function does NOT authenticate TLS or device keys.
 * Only call from a reviewed trusted evidence producer, never with client-supplied fields.
 */
stosnet_tls_decision stosnet_tls_gate(const stosnet_tls_evidence *e,
 const uint8_t expected_binding[STOSNET_TLS_BINDING_LEN],
 const uint8_t expected_device[STOSNET_TLS_ID_LEN]);
#endif
