# Security contract (requirements, not implementation)

1. Deny by default; no unauthenticated network listeners.
2. Mutually authenticated peers, verified cryptographic identities, short-lived
   sessions, explicit revocation and key rotation.
3. Do not invent encryption or handshake protocols. Select an audited, vetted
   implementation compatible with sovereignty requirements before coding.
4. Buddy identity, Klik authorization, Avouch validation, Nexus transport
   integration are candidates, subject to read-only source audit.
5. Gateway 127.0.0.1:9844 must remain loopback-only until a separate
   security review explicitly authorizes a change.
6. Reject replay, downgrade, unauthorized route, origin confusion, DNS rebinding,
   CSRF, cross-device session fixation, and stale device credentials.
7. Do not place family/student data, credentials, private keys, or bearer tokens
   in browser storage, logs, Git repositories, or the package.
8. Explicit device enrollment and owner-visible revocation receipts.
9. No exposure to WAN, router port forwarding, or wildcard interfaces by default.
10. Test fail-closed behavior on network loss and policy-service unavailability.
