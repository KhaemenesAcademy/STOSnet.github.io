# Local synthetic test
From this package root:
```sh
cc -std=c17 -Wall -Wextra -Werror -pedantic -Iinclude src/stosnet_evidence_v3.c tests/test_evidence_v3.c -o /tmp/stosnet-v3-synthetic
/tmp/stosnet-v3-synthetic
```
No external libraries or network required. Test binary is not included in release ZIP. For production: add adversarial integration, cryptographic, concurrency, origin/CSRF, replay, enrollment/revocation and lifecycle tests; this synthetic test does not cover them.
