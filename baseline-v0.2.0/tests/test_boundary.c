#include "stosnet_boundary.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
  stosnet_evidence e = {STOSNET_BOUNDARY_ABI,1,1,1,1,1,1,1,1,1,1,1,1};
  assert(stosnet_route_decide(NULL)==STOSNET_DENY);
  assert(stosnet_route_decide(&e)==STOSNET_ALLOW);
  e.abi=999; assert(stosnet_route_decide(&e)==STOSNET_DENY);
  e.abi=STOSNET_BOUNDARY_ABI;
  int *fields[] = {
    &e.transport_authenticated,&e.device_enrolled,&e.device_not_revoked,
    &e.fresh_session,&e.request_validated,&e.policy_available,
    &e.policy_explicit_allow,&e.destination_explicit_allow,
    &e.origin_validated,&e.csrf_validated,&e.replay_check_passed,
    &e.storage_authority_verified
  };
  for (size_t i=0;i<sizeof(fields)/sizeof(fields[0]);i++){
    *fields[i]=0; assert(stosnet_route_decide(&e)==STOSNET_DENY); *fields[i]=1;
  }
  puts("PASS: 15 synthetic fail-closed assertions (null, ABI, 12 gates, all-pass)");
  return 0;
}
