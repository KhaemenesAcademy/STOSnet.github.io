# STOSnet v0.1.0 — Sovereign Private Network Manager

Status: DESIGN / AUDIT FOUNDATION — HOLD. Not commissioned, not a functioning VPN or proxy.

STOSnet is the proposed STOS-native private network management layer for Mac, Linux,
Windows, and Android. Its first milestone is secure Linux browser access to the
Mac-hosted STOS Gateway (currently bound to 127.0.0.1:9844).

## Sovereignty
- No Headscale, Tailscale, Caddy, Docker, FastAPI, or external SaaS control plane.
- No new authoritative Mac-local persistent store.
- No public listener, routing, or firewall change without explicit owner approval.
- No bundled credentials, private keys, student/family records, or live endpoints.
- No silent installation, service activation, or deletion.
- Use existing STOS identity, policy, and validation components where certified;
  verify availability before implementation, never assume.
- Do not write a bespoke cryptographic primitive. A cryptographic design and
  vetted platform implementation must be explicitly approved before networking.

## Current verified baseline (2026-10-15)
Mac 192.168.1.198 and Linux 192.168.1.124 reachable on 192.168.1.0/24.
STOS Gateway healthy on Mac 127.0.0.1:9844, PID 776 after crash recovery.
No STOSnet listener or secure cross-device route commissioned.

## Deliverables
docs/ARCHITECTURE.md
docs/SECURITY_CONTRACT.md
docs/STORAGE_AND_SOVEREIGNTY.md
docs/COMMISSIONING_GATES.md
docs/RECOVERY_AND_FAILOVER.md
docs/INTEGRATION_MAP.md
docs/DECISIONS_REQUIRED.md
contracts/STOSNET_PROTOCOL_V0_1.md
inventory/BASELINE.json

This package is documentation-only by design. No executable or network service
is included; that prevents a false claim of secure connectivity.

## Next action
Read-only audit of STOS's existing Viaduct, Buddy, Klik, Avouch, Nexus, and
transport implementations. Choose and verify a cryptographic transport and
device identity strategy. Only then create native source behind acceptance gates.
