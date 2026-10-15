#ifndef STOSNET_TRANSPORT_V4_H
#define STOSNET_TRANSPORT_V4_H
#include <stddef.h>
#include <stdint.h>
#define STOSNET_TRANSPORT_ABI 4u
#define STOSNET_V4_BINDING_BYTES 32u
#define STOSNET_V4_DEVICE_BYTES 32u
#define STOSNET_V4_MAX_AUDIENCE 96u
typedef enum { STOSNET_V4_DENY=0, STOSNET_V4_ALLOW=1 } stosnet_v4_decision;
/* This is NOT a TLS stack or cryptographic proof. It is a policy contract.
 * Evidence must be constructed solely by reviewed, trusted platform adapters.
 * Untrusted network input MUST NOT populate the evidence struct. */
typedef struct {
 uint32_t abi;
 uint8_t tls_channel_binding[STOSNET_V4_BINDING_BYTES];
 uint8_t device_key_fingerprint[STOSNET_V4_DEVICE_BYTES];
 char audience[STOSNET_V4_MAX_AUDIENCE];
 uint64_t connection_id;
 uint64_t authenticated_at;
 uint64_t expires_at;
 uint64_t revocation_epoch;
 uint8_t tls_verified;
 uint8_t device_possession_verified;
 uint8_t enrollment_approved;
 uint8_t revocation_fresh;
} stosnet_v4_channel_evidence;
/* trusted_ctx is registered by the owning process, never supplied by client.
 * Callback must independently recheck exact binding, identity, audience,
 * expiry, revocation, and enrollment against current authoritative state.
 * 1=success, all other results=deny. */
typedef int (*stosnet_v4_recheck_fn)(void *trusted_ctx,
 const stosnet_v4_channel_evidence *e,
 const uint8_t expected_binding[STOSNET_V4_BINDING_BYTES],
 const char *expected_audience, uint64_t now);
typedef struct {
 uint32_t abi;
 stosnet_v4_recheck_fn recheck;
 void *trusted_ctx;
} stosnet_v4_authority;
stosnet_v4_decision stosnet_v4_channel_decide(
 const stosnet_v4_channel_evidence *e,
 const stosnet_v4_authority *authority,
 const uint8_t expected_binding[STOSNET_V4_BINDING_BYTES],
 const char *expected_audience, uint64_t now);
#endif
