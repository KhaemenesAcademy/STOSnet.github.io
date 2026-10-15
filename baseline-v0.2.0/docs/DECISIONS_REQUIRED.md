# Decisions required before implementation

1. Which STOS-native cryptographic transport implementation, if any, is already
   available and reviewed? Avoid writing novel cryptography.
2. What existing STOS identity and policy APIs are actually implemented?
3. Where is the off-controller, durable STOSnet authority located?
4. Which device enrollment ceremony is acceptable to the owner?
5. How will Linux browsers connect without introducing unauthenticated
   localhost browser exposure or weakening web origin/session protections?
6. What is the first owner-approved test window and rollback procedure?

Do not install, activate, modify network bindings, or migrate data until
these decisions and commissioning gates are satisfied.
