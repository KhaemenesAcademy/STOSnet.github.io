#include "stosnet_evidence_v3.h"
#include <string.h>
static int terminated_nonempty(const char *s, size_t cap) {
  size_t i;
  if (!s || !cap || !s[0]) return 0;
  for (i=0; i<cap; ++i) {
    if (s[i]=='\0') return 1;
    if ((unsigned char)s[i]<0x20 || (unsigned char)s[i]==0x7f) return 0;
  }
  return 0;
}
static int valid_request(const stosnet_v3_request *r) {
  return r && r->abi==STOSNET_EVIDENCE_ABI &&
    terminated_nonempty(r->request_id,sizeof r->request_id) &&
    terminated_nonempty(r->method,sizeof r->method) &&
    terminated_nonempty(r->route,sizeof r->route) &&
    r->route[0]=='/' &&
    terminated_nonempty(r->origin,sizeof r->origin) &&
    terminated_nonempty(r->audience,sizeof r->audience) &&
    /* Device hint is optional; the authoritative identity must come from
       independently verified context, not this field. */
    memchr(r->device_hint,'\0',sizeof r->device_hint)!=NULL;
}
stosnet_v3_result stosnet_v3_decide(const stosnet_v3_request *r,
                                   const stosnet_v3_adapters *a) {
  stosnet_v3_result result = {STOSNET_V3_DENY,STOSNET_VERIFY_TRANSPORT,0};
  size_t i;
  if (!valid_request(r) || !a || a->abi!=STOSNET_EVIDENCE_ABI)
    return result;
  for (i=0; i<STOSNET_VERIFY_COUNT; ++i) {
    result.first_failed_check=(stosnet_v3_check)i;
    if (!a->verify[i] || !a->trusted_ctx[i] ||
        a->verify[i](a->trusted_ctx[i],r)!=1)
      return result;
    ++result.checks_passed;
  }
  result.decision=STOSNET_V3_ALLOW;
  result.first_failed_check=STOSNET_VERIFY_COUNT;
  return result;
}
const char *stosnet_v3_check_name(stosnet_v3_check check) {
  static const char *const names[] = {
    "transport","enrollment","revocation","session","avouch","klik",
    "destination","origin","csrf","replay","storage"
  };
  if (check<0 || check>=STOSNET_VERIFY_COUNT) return "invalid";
  return names[check];
}
