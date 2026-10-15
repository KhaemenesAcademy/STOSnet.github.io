# STOSnet v0.7.0 — Isolated Darwin TLS handshake candidate

**SOURCE ONLY · UNCOMMISSIONED · MAC SDK BUILD UNVERIFIED · NO LIVE HANDSHAKE CLAIM**

Preserves the uploaded v0.6.0 GitHub repository baseline.
Adds `include/stosnet_test_v7.h`, `src/stosnet_test_v7.c`,
`tests/test_test_v7.c`, and a Darwin Network.framework
loopback-only TLS 1.3 test listener candidate with an operator-selected
Keychain server identity and required peer certificate trust.

The listener has no STOS routes and immediately cancels TLS-ready
connections. It does not perform STOS enrollment, device revocation,
channel binding, Klik authorization or remote storage operations.

C17 synthetic configuration tests are locally compiled and run.
Darwin adapter is source-only and must be reviewed/compiled on the
target macOS SDK under separate approval before any handshake test.
Production Gateway 9844 is untouched.
