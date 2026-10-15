# STOSnet v0.6.0 — Darwin TLS listener preparation candidate
**SOURCE ONLY / NOT COMMISSIONED / NO LISTENER START / NO REMOTE ACCESS**

Preserves the v0.5.0 package unchanged in `baseline-v0.5.0/`.
Adds a C17 fail-closed configuration gate and Apple Network.framework TLS 1.3
parameter factory (not compiled on macOS here). No server identity, client
authentication, real TLS handshake, remote-device enrollment, revocation,
channel binding, route integration or storage authority is implemented.
