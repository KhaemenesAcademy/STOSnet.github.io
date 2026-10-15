/*
 * STOSnet Darwin TLS adapter placeholder (NOT A TLS SERVER).
 * Native implementation must use Apple's Network.framework + Security.framework,
 * with TLS 1.3, a verified SecIdentityRef and peer trust verification.
 * This source deliberately has NO listener and NEVER reports authentication.
 * Requires separate macOS target compilation and integration tests.
 */
#include <stddef.h>
int stosnet_darwin_tls_available(void) { return 0; }
int stosnet_darwin_tls_open(void *configuration) {
 (void)configuration;
 return -1; /* fail closed until audited native adapter is implemented */
}
