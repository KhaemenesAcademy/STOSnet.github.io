# STOSnet architecture — candidate

## Roles
- STOSnet Control: owner-approved device registration, revocation, policies,
  connection inventory, and health. Authority must live off-controller.
- STOSnet Transport: encrypted, mutually authenticated peer channels;
  no cryptography implemented in v0.1.0.
- STOSnet Edge: least-privilege bridge from authorized private channel to
  Mac-local 127.0.0.1:9844; no wildcard bind of Gateway.
- STOSnet Client: Linux browser access via an authenticated local endpoint,
  only after origin/CSRF/session and web security are reviewed.
- STOSnet Recovery: process recovery, state reconciliation, and signed receipts.

## Intended first route
Linux client -> authenticated STOSnet channel -> Mac STOSnet edge
-> 127.0.0.1:9844 (Gateway remains loopback-only).

No public exposure, reverse tunnel, NAT traversal, DNS update, port forwarding,
or LAN binding is implemented by this package.

## Quadrangulation
Mac, Linux, Windows, Android are candidate nodes. Independent serving,
authoritative state replication, lease/fencing, DNS/routing failover, Android
background constraints, and split-brain handling require separate gates.
A browser connection to Mac is NOT Linux independent hosting or failover.

## Lifecycle
DISCOVER -> DESIGN REVIEW -> SYNTHETIC TEST -> OWNER APPROVAL ->
CONTROLLED COMMISSION -> RECOVERY SEAL -> MULTI-DEVICE EXPANSION.
