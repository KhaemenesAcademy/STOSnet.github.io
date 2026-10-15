#ifndef STOSNET_EVIDENCE_V3_H
#define STOSNET_EVIDENCE_V3_H
#include <stddef.h>
#include <stdint.h>
#define STOSNET_EVIDENCE_ABI 3u
#define STOSNET_MAX_REQUEST_ID 64u
#define STOSNET_MAX_ROUTE 128u
#define STOSNET_MAX_METHOD 12u
#define STOSNET_MAX_ORIGIN 256u
#define STOSNET_MAX_DEVICE 96u
#define STOSNET_MAX_AUDIENCE 96u
#define STOSNET_MAX_POLICY 96u
typedef enum {
  STOSNET_V3_DENY = 0,
  STOSNET_V3_ALLOW = 1
} stosnet_v3_decision;
/* Request is untrusted input. No field represents proof of authentication. */
typedef struct {
  uint32_t abi;
  char request_id[STOSNET_MAX_REQUEST_ID];
  char method[STOSNET_MAX_METHOD];
  char route[STOSNET_MAX_ROUTE];
  char origin[STOSNET_MAX_ORIGIN];
  char device_hint[STOSNET_MAX_DEVICE];
  char audience[STOSNET_MAX_AUDIENCE];
  uint64_t observed_time;
} stosnet_v3_request;
typedef enum {
  STOSNET_VERIFY_TRANSPORT = 0,
  STOSNET_VERIFY_ENROLLMENT,
  STOSNET_VERIFY_REVOCATION,
  STOSNET_VERIFY_SESSION,
  STOSNET_VERIFY_AVOUCH,
  STOSNET_VERIFY_KLIK,
  STOSNET_VERIFY_DESTINATION,
  STOSNET_VERIFY_ORIGIN,
  STOSNET_VERIFY_CSRF,
  STOSNET_VERIFY_REPLAY,
  STOSNET_VERIFY_STORAGE,
  STOSNET_VERIFY_COUNT
} stosnet_v3_check;
/* Each callback is a TRUSTED, independently reviewed integration, not a
 * request-controlled flag or a generic string-claim checker.
 * Verification MUST bind to the exact request and independently established
 * cryptographic/session context. Return 1 only for verified success.
 * An absent callback, unavailable authority, or any other result denies.
 * This API cannot prove callback trustworthiness by itself.
 */
typedef int (*stosnet_v3_verify_fn)(void *trusted_ctx,
                                    const stosnet_v3_request *request);
typedef struct {
  uint32_t abi;
  stosnet_v3_verify_fn verify[STOSNET_VERIFY_COUNT];
  void *trusted_ctx[STOSNET_VERIFY_COUNT];
} stosnet_v3_adapters;
typedef struct {
  stosnet_v3_decision decision;
  stosnet_v3_check first_failed_check;
  uint32_t checks_passed;
} stosnet_v3_result;
/* Zero initialized outputs; never emits secrets or raw evidence. */
stosnet_v3_result stosnet_v3_decide(const stosnet_v3_request *request,
                                   const stosnet_v3_adapters *adapters);
const char *stosnet_v3_check_name(stosnet_v3_check check);
#endif
