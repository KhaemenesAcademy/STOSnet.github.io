# STOSnet v0.7 — Darwin loopback TLS handshake candidate

**STATUS: SOURCE ONLY. NOT MACOS SDK-COMPILED. NOT HANDSHAKE-TESTED. NOT COMMISSIONED.**

## Intent
An isolated Network.framework TLS 1.3 listener candidate bound to
`127.0.0.1:18443`, requiring an existing operator-selected Keychain
`SecIdentityRef`, requiring peer certificate authentication, and using
system trust verification. The listener cancels authenticated connections
without reading application bytes or serving any routes. This is **not**
a remote access service, enrollment system, device-authority proof or proxy.

## Build validation on the target Mac — separate approval required
Review the SDK APIs, minimum OS version and entitlement constraints before
compiling. Proposed command (do **not** run until approved):

```sh
clang -std=c17 -Wall -Wextra -Werror -Iinclude -c src/stosnet_test_v7.c -o /tmp/stosnet_v7_gate.o
clang -fobjc-arc -fblocks -Iinclude -framework Foundation -framework Network -framework Security   darwin/stosnet_v7_loopback_listener.m /tmp/stosnet_v7_gate.o -o /tmp/stosnet_v7_test
```

Do not execute the listener without separately approving test identity,
client trust policy, firewall constraints, and test timing. It has an
explicit `--run-test --identity-label LABEL` switch and requires
`STOSNET_V7_TEST_APPROVED=YES`. No identity is generated or imported.

## Critical limitations
- Apple SDK build and handshake are **unverified** in this environment.
- `SecTrustEvaluateWithError` uses system trust; it does **not** verify
  STOS enrollment, device key pinning, revocation authority or channel binding.
- System trust alone is insufficient for remote STOS access.
- Certificate policy (EKU, intended CA, client identity and revocation)
  needs review before any live handshake.
- No evidence is emitted to the v0.3/v0.4 gate; no trusted identity is asserted.
- TLS handshake timeout, certificate rotation, asynchronous trust latency,
  bounded queue behavior, interruption cleanup and memory review remain gates.
- No Mac-local authoritative enrollment or revocation persistence.
- No Nexus, xkyoot, Buddy HYBRID, Wend, storage or production integration.
- LAN exposure, service installation, production commissioning and storage
  migration remain **HOLD**.

## Negative test plan
1. Missing `--run-test` and approval env: listener must not start.
2. Missing Keychain identity: listener must not start.
3. Wrong client trust root: handshake must fail.
4. No client certificate: handshake must fail.
5. TLS 1.2-only client: handshake must fail.
6. Verify actual socket bind is **only** 127.0.0.1:18443.
7. Even trusted client: connection closes with no application response.
8. Existing 127.0.0.1:9844 gateway remains unchanged.
9. Stop test listener and confirm no background process or persistence.
10. Test on real Mac SDK before claiming any of the above passed.

## Platform disclosure
C17 policy gate uses standard C. Darwin adapter uses Apple Network.framework,
Security.framework, Foundation and libdispatch. No Node, npm, Python runtime,
Docker, proxy service, OpenSSL or package manager is required by this adapter.
These are Apple platform dependencies, not a claim of pure portable C17 TLS.
