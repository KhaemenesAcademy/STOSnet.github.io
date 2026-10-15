# STOSnet v0.4.0 — Native Transport & Device Identity Contract Candidate
**SOURCE-ONLY · NOT COMMISSIONED · NO TLS SERVER · NO LISTENER**

Preserves the v0.3.0 source candidate under `baseline-v0.3.0/`; adds `stosnet_transport_v4.h`, `stosnet_transport_v4.c`, a synthetic test harness, and a transport identity contract.

The v0.4 C17 gate rejects absent/invalid trusted evidence, mismatched channel binding or audience, expired evidence, missing enrollment/revocation signals, and unavailable authority callback. All signals remain *unverified unless independently established by reviewed real integrations*. No security certification is claimed.

No runtime dependencies beyond C17 libc for the new library. Compiler required to build tests. No services installed, no network ports opened, no STOS storage modified. Production HOLD.
