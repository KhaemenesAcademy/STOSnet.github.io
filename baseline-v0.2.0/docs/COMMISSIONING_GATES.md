# STOSnet commissioning gates — ALL HOLD

[ ] 01 Read-only inventory of existing STOS transport/identity/policy primitives
[ ] 02 Architecture and dependency policy approved by owner
[ ] 03 Cryptographic transport selected, audited, threat-modeled, approved
[ ] 04 Authenticated device enrollment and revocation tested with synthetic IDs
[ ] 05 STOS Gateway stays loopback-only; edge route explicitly allowlisted
[ ] 06 Linux client authentication and browser session security verified
[ ] 07 Unauthorized Linux peer denied; no anonymous LAN access
[ ] 08 Origin, CSRF, replay, downgrade, and DNS rebinding defenses tested
[ ] 09 Off-controller durable policy/identity authority proven with readback
[ ] 10 No production family/student data in synthetic tests
[ ] 11 Mac crash/reboot recovery and client reconnection tested
[ ] 12 Network loss, revocation, storage loss all fail closed
[ ] 13 No unexpected listeners, dependencies, credentials or local authority
[ ] 14 Audit receipts, rollback plan, and explicit owner approval recorded

Passing Linux browser access does not pass independent Linux hosting/failover.
