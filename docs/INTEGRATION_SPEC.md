# STOSnet v0.2.0 integration specification (non-operational)
## Audited STOS roles
- Abby v0.5.0: native randomness and private local IPC; browser TCP is not local peer identity. Windows listener functions were observed returning ENOTSUP.
- Buddy v0.4.0: local OS/capability/HYBRID proofs; remote browser cannot assert local HYBRID.
- Klik: sole authorization authority; requires validated operation and verified proof.
- Avouch: bounded typed request validation.
- Nexus v0.3.0: bounded HTTP; no proven TLS listener; loopback default.
- Wend v0.2.0: memory-only session handoff; not a TLS listener.
- Egress v0.3.0: outbound HTTP/TLS; Linux default HTTPS fails closed; optional OpenSSL build.
- Floo v0.2.0: DNS semantics; not a transport.
- ViaDuct v0.3.0: verified immutable tree handoff; not a tunnel.
- Secure Server Native: protected operations only over full Abby/Buddy/Brij/Klik/Daisy private lineage.
- Gaffer/xkyoot: production Gateway loopback 127.0.0.1:9844 remains untouched.
## Trust boundaries
Remote device enrollment is an independently approved event; never infer from a client claim.
A cryptographically authenticated channel is necessary but not sufficient.
Policy and revocation must be read from independently verified off-controller STOS storage.
Never translate remote browser assertions into Buddy OS or HYBRID proof.
No generic reverse proxy to Gateway 9844; each route must be explicitly classified and independently authorized.
Origin, CSRF, replay, downgrade, DNS rebinding, cookie and session fixation tests are mandatory.
## Missing implementations
1. Reviewed native inbound TLS implementation, with browser-compatible server certificate verification.
2. Enrolled remote device key lifecycle and owner approval, revocation, rotation and receipts.
3. Cross-boundary remote identity adapter with no Buddy proof impersonation.
4. Klik policy adapter, Avouch typed request adapter, verified off-controller authority adapter.
5. Restricted route handler, secure browser origin/session model, Gaffer lifecycle and recovery.
6. Mac/Linux adversarial acceptance; Windows/Android separate targets.
No code in this package supplies any of these mechanisms.
