# Darwin inbound TLS contract — v0.5 candidate
Status: **NOT IMPLEMENTED / NOT COMMISSIONED**.

## Platform
Use Apple's **Network.framework** and **Security.framework**, not custom crypto or
third-party application runtimes. Darwin adapter is Objective-C/C bridge and is
currently a fail-closed stub. This package has **no TLS listener**.

## Required before implementation is considered valid
1. Operator-approved server `SecIdentityRef` certificate and private key;
   no auto-generated unreviewed trust root, no private-key export in logs.
2. TLS 1.3 minimum; fail closed on downgrade, handshake failure, or missing
   trust evaluation. Validate actual macOS SDK API availability on target.
3. Authenticated device identity via separately approved certificate-based
   client authentication or application-level key possession proof bound to
   the specific TLS channel. A certificate fingerprint alone is not proof.
4. Real channel binding must be derived from reviewed TLS API/exporter semantics.
   Never substitute a random value, connection ID, IP address or unverified header.
   If unavailable, deny.
5. Enrollment/revocation freshness from independent STOS authority, not a
   local Mac authoritative database or remote client assertions.
6. Nexus may receive only explicitly mapped routes after authorization; no
   proxy to 127.0.0.1:9844 and no elevation into Abby/Buddy local IPC.
7. Timeouts, bounded concurrent handshakes, bounded requests, strict origin,
   CSRF protection, no plaintext fallback, no anonymous administrative access.
8. Independent macOS handshake and negative tests (untrusted client, replay,
   wrong device, revoked device, stale authority, wrong origin, restart).
9. Explicit operator approval before LAN bind, installation, or commissioning.

## Evidence caveat
The v0.5 C17 gate checks *values*, not their provenance. Callers must never
copy evidence from untrusted HTTP headers, JSON, or application input.
The v0.3/v0.4 contracts remain necessary and are not replaced by this gate.
