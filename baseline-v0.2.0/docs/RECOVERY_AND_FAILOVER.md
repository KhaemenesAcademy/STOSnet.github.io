# Recovery and failover

Observed Mac boot 2026-10-15 12:12:28; Gaffer PID 740 started 12:17:51;
Gateway PID 776 started 12:18:53; HTTP 200 and healthy reported.
This establishes Gateway recovery, not STOSnet recovery or unattended login.

STOSnet must preserve existing Gaffer supervision and Gateway availability.
Future recovery: deterministic startup, idempotent enrollment state,
revocation replay, policy readback, edge health, reconnection without privilege
escalation, and signed recovery evidence.

Four-device failover is a separate project phase: authoritative replicated state,
fencing/leases, split-brain prevention, routable discovery, session continuity,
Android lifecycle limitations, and tested operator rollback.
