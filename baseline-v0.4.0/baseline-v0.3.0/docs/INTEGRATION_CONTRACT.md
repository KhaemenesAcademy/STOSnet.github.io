# STOSnet v0.3.0 — Native evidence adapter contract (CANDIDATE)
This is a **non-operational** interface demonstration. It does not authenticate any device, terminate TLS, check a signature, fetch revocations, contact Klik, or establish off-controller authority. Synthetic callbacks are deliberately fake. Passing the test is NOT a security certification.

## Baseline preservation
`baseline-v0.2.0/` is an unmodified copy of the uploaded GitHub repository snapshot. v0.3 code is additive and lives in `include/`, `src/`, `tests/`. No production paths or listeners are modified.

## Integration contract
- Treat `stosnet_v3_request` as **untrusted** and bounded. Its device_hint, request_id, origin, method and audience are hints, not proofs. Caller must obtain authenticated connection metadata separately.
- Every callback MUST be a trusted adapter, linked/registered by the owning STOS process from reviewed code, not selected by a browser, plugin, dynamic request or unauthenticated local client.
- The generic gate invokes 11 callbacks, requiring exact `1` results. Missing adapter/context, failure or unavailable authority denies. The 12 v0.2 Boolean gates are mapped to 11 adapter families because policy availability and explicit policy ALLOW must be established together by the single Klik callback. **The API cannot enforce independence or provenance of callbacks.**
- Callbacks MUST bind verification to the exact request, authenticated channel, verified device identity, service audience, destination, current time, and independently verified policy state. The request_id is not a replay token.
- No callback may elevate remote browser evidence into Buddy OS/HYBRID or Abby private IPC proof. Secure Server protected routes remain inaccessible.
- Storage callback MUST verify off-controller authority and freshness, never treat Mac-local browser localStorage, repository files or local intake staging as authoritative.
- Origin and CSRF validation are mandatory for browser mutations; these callbacks must implement actual browser-specific rules, not unconditional success.
- Prevent TOCTOU: verified evidence and route authorization must be bound to the **same** request, connection and destination. Production implementation must define immutable context, synchronized revocation snapshots, proof expiry and race handling.
- Fail closed on network loss, stale revocation, unavailable Klik or storage authority, missing TLS verification, and clock uncertainty.
- For privacy, the generic result contains only a decision, first failing check category and count. Do not log tokens, student data, or device keys.

## Implementation gap
No production adapters exist in this package. Callback registration alone is not trust. Native TLS and enrollment, session binding, revocation, Avouch, Klik, CSRF, replay, verified off-controller storage and service lifecycle remain HOLD. No open port, daemon, private credential, remote control plane or network access is introduced.

## Platform policy
C17 core has no external runtime dependency. macOS Apple system TLS is a candidate for the inbound transport. Linux browser-compatible TLS requires an approved, maintained TLS provider or verified host-native equivalent; do not implement custom cryptography. Windows/Android are separate acceptance targets.
