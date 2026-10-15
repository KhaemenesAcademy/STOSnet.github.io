#include "stosnet_boundary.h"
stosnet_decision stosnet_route_decide(const stosnet_evidence *e) {
  if (!e || e->abi != STOSNET_BOUNDARY_ABI) return STOSNET_DENY;
  if (!e->transport_authenticated || !e->device_enrolled ||
      !e->device_not_revoked || !e->fresh_session ||
      !e->request_validated || !e->policy_available ||
      !e->policy_explicit_allow || !e->destination_explicit_allow ||
      !e->origin_validated || !e->csrf_validated ||
      !e->replay_check_passed || !e->storage_authority_verified)
    return STOSNET_DENY;
  return STOSNET_ALLOW;
}
