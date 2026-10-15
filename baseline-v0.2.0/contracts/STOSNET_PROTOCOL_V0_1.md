# STOSnet protocol v0.1 — non-wire contract

No wire format is defined and no service is implemented.

Required operations (conceptual):
- enroll_request(device_public_identity, owner_authorization)
- enroll_approve(request_id, scoped_capabilities)
- revoke(device_id, reason, signed_receipt)
- route_authorize(peer_id, destination, session_context)
- session_health(peer_id)
- audit_append(event, idempotency_key)
- policy_readback(version)

All writes require durable audit and fail-closed semantics. Exact schemas,
algorithms, identity keys, transaction model, and transport are TBD following
existing STOS source review. Never treat this as interoperable protocol code.
