#ifndef STOSNET_BOUNDARY_H
#define STOSNET_BOUNDARY_H
#include <stddef.h>
#include <stdint.h>
#define STOSNET_BOUNDARY_ABI 1u
typedef enum {
  STOSNET_DENY=0,
  STOSNET_ALLOW=1
} stosnet_decision;
typedef struct {
  uint32_t abi;
  int transport_authenticated;
  int device_enrolled;
  int device_not_revoked;
  int fresh_session;
  int request_validated;
  int policy_available;
  int policy_explicit_allow;
  int destination_explicit_allow;
  int origin_validated;
  int csrf_validated;
  int replay_check_passed;
  int storage_authority_verified;
} stosnet_evidence;
/* Every field must be positively established by an independent trusted authority.
   No browser-provided identity assertion is evidence. */
stosnet_decision stosnet_route_decide(const stosnet_evidence *e);
#endif
