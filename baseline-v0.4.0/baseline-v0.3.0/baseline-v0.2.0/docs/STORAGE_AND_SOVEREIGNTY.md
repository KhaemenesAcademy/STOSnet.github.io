# Storage and sovereignty boundary

Authoritative STOSnet policy, identity metadata, enrollment/revocation records,
audit, and recovery receipts must be off-controller in verified STOS-managed
storage. The current Mac filesystem is not an acceptable permanent authority.

Ephemeral process memory is permitted for runtime execution. Any temporary
OS artifacts must be inventoried and explicitly governed; do not claim
zero local footprint while Mac-hosted code is running.

GitHub repositories may hold versioned source and signed release artifacts,
but must not be presumed to provide transactional live identity storage,
private key custody, or shared filesystem semantics.

No migration or removal until destination authentication, hash/readback,
recovery, crash restart, and independent operation have been proven.
Deletion requires separate owner authorization.

Never use Mini Cloud browser localStorage as authoritative private cloud.
Account Cloud retains separate family/student authority and transaction gates.
