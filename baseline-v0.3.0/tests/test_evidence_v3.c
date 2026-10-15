#include "stosnet_evidence_v3.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef struct { int allow; unsigned called; } fixture;
static int fake_adapter(void *ctx,const stosnet_v3_request *r) {
  fixture *f=(fixture *)ctx;
  ++f->called;
  return f->allow && strcmp(r->request_id,"req-001")==0;
}
static stosnet_v3_request make_request(void) {
  stosnet_v3_request r;
  memset(&r,0,sizeof r);
  r.abi=STOSNET_EVIDENCE_ABI;
  strcpy(r.request_id,"req-001");
  strcpy(r.method,"GET");
  strcpy(r.route,"/health");
  strcpy(r.origin,"https://test.example");
  strcpy(r.audience,"stosnet-test");
  return r;
}
int main(void) {
  stosnet_v3_request r=make_request();
  stosnet_v3_adapters a;
  stosnet_v3_result out;
  fixture f[STOSNET_VERIFY_COUNT];
  size_t i,j;
  memset(&a,0,sizeof a);
  a.abi=STOSNET_EVIDENCE_ABI;
  for(i=0;i<STOSNET_VERIFY_COUNT;i++) {
    f[i].allow=1;f[i].called=0;
    a.verify[i]=fake_adapter;a.trusted_ctx[i]=&f[i];
  }
  assert(stosnet_v3_decide(NULL,&a).decision==STOSNET_V3_DENY);
  assert(stosnet_v3_decide(&r,NULL).decision==STOSNET_V3_DENY);
  r.abi=2;
  assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
  r.abi=STOSNET_EVIDENCE_ABI;
  a.abi=2;
  assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
  a.abi=STOSNET_EVIDENCE_ABI;
  out=stosnet_v3_decide(&r,&a);
  assert(out.decision==STOSNET_V3_ALLOW && out.checks_passed==STOSNET_VERIFY_COUNT);
  for(i=0;i<STOSNET_VERIFY_COUNT;i++) {
    f[i].allow=0;
    out=stosnet_v3_decide(&r,&a);
    assert(out.decision==STOSNET_V3_DENY && out.first_failed_check==(stosnet_v3_check)i);
    f[i].allow=1;
    a.verify[i]=NULL;
    assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
    a.verify[i]=fake_adapter;
    a.trusted_ctx[i]=NULL;
    assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
    a.trusted_ctx[i]=&f[i];
  }
  r.route[0]='x';
  assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
  r=make_request();
  memset(r.request_id,'A',sizeof r.request_id);
  assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
  r=make_request();
  r.request_id[0]='\n';
  assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
  r=make_request();
  strcpy(r.request_id,"attacker-controlled");
  assert(stosnet_v3_decide(&r,&a).decision==STOSNET_V3_DENY);
  r=make_request();
  for(j=0;j<STOSNET_VERIFY_COUNT;j++) assert(f[j].called>0);
  assert(strcmp(stosnet_v3_check_name(STOSNET_VERIFY_KLIK),"klik")==0);
  puts("PASS: v0.3 synthetic evidence boundary (no production authority adapters)");
  return 0;
}
