# STOSnet v0.6.0 — Darwin TLS listener preparation

**SOURCE ONLY / NO ACTIVE LISTENER / NOT COMMISSIONED**

This candidate preserves the complete v0.5.0 baseline. It adds a C17
configuration boundary with explicit loopback-only, authority-online, identity,
TLS 1.3, peer-authentication and operator-approval requirements, and an
Apple Network.framework **parameter factory**. The factory does not create or
start a listener, configure a server SecIdentity, verify a client certificate,
implement channel binding, or authorize an application route. It cannot
establish secure remote access. The C17 test is synthetic.

## Outstanding engineering gates
- Compile Objective-C adapter on target macOS SDK and verify framework APIs.
- Provision reviewed SecIdentity via STOS-approved authority; no export of keys.
- Require and verify actual client authentication, with independently
  approved enrollment and revocation. Do not infer proof from a fingerprint.
- Establish a reviewed channel-binding mechanism; no placeholder binding.
- Implement connection lifecycle with bounded handshakes and reject-by-default.
- Review Apple trust evaluation, TLS version negotiation, replay, and downgrade.
- Implement real Klik, Avouch, Buddy, Wend integration without remote Abby
  private IPC impersonation.
- Off-controller authoritative storage and recovery certification.
- Explicit approval before compiling on Mac, starting a listener, or LAN bind.

`loopback_only` is a configuration *assertion*, not proof of the OS bind
address. A real adapter must independently enforce and verify its bind scope.
No test here proves network safety.
