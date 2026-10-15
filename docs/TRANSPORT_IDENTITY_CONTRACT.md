# STOSnet v0.4.0 — native transport and device identity contract (CANDIDATE)

## Purpose
Source-only design and a fail-closed C17 contract for consuming **independently authenticated** channel evidence. No inbound TLS, listener, browser connection, cryptographic enrollment, real verifier, or network operation is implemented.

## Trust boundaries
1. Only a reviewed native TLS endpoint may establish TLS peer/server authentication and channel binding. Never accept a request header, JSON field, cookie or user-provided `stosnet_v4_channel_evidence` as proof.
2. Device-key possession requires a fresh challenge and signature verification or a reviewed certificate-bound client authentication protocol, performed by an approved cryptographic provider. This C17 package does neither.
3. Enrollment approval must originate from the existing authorized STOS administration workflow. Device key fingerprint alone is not enrollment.
4. Revocation requires fresh, authenticated, off-controller STOS-authoritative state. Fail closed on stale/unavailable state, time uncertainty or generation change. Mac-local cache must not become authoritative.
5. `tls_channel_binding` is an opaque 32-byte value from a reviewed TLS exporter or equivalent protocol-bound proof. Do not assume the platform exposes a particular exporter API. No hash of untrusted strings qualifies.
6. Recheck must bind the same live connection, device, audience, expiry, enrollment generation, revocation epoch, and current policy snapshot. The generic code cannot enforce callback trust or race freedom.
7. The expected binding must be supplied from trusted connection metadata, not request input. A caller that fabricates both sides can trivially bypass this synthetic gate.
8. Browser TLS server authentication is mandatory. Device enrollment alone does not authenticate the user. Klik, Avouch, CSRF, origin, session and storage authority remain separate v0.3 checks.
9. Never translate remote device proof into Abby local IPC or Buddy OS/HYBRID proof; no Secure Server protected private routes.
10. Gateway 127.0.0.1:9844 stays loopback-only. No generic forwarding or localStorage-to-storage authority promotion.

## Platform acceptance
- macOS: investigate supported Apple Network.framework/Security.framework TLS server APIs, key handling, certificate issuance/rotation and channel binding. System APIs are host dependencies, not independent STOS implementations.
- Linux: choose and approve a maintained TLS provider explicitly; no mandatory OpenSSL, Node, Python, Docker or package-manager-based runtime in this package. If no approved provider exists, HTTPS stays disabled.
- Windows/Android: not certified; Abby Windows loopback functions currently return ENOTSUP in inspected source.
- No bespoke TLS or cryptography. Reuse Abby's platform CSPRNG only through approved adapter boundaries.

## Pre-activation acceptance tests (NOT supplied by this package)
Known-answer and negative TLS handshake tests; certificate name/trust/expiry/rotation; mutual or proof-of-possession authentication; challenge replay; enrollment approval/revocation; session expiration; CSRF and origin; concurrency/TOCTOU; policy fail-closed; verified off-controller authority; network isolation; restart and rollback; platform-native builds.

## Status
This package's test callback is deliberately synthetic and returns a variable. Passing tests demonstrates local input validation only, **not cryptographic security**. Commissioning HOLD.
