# Isolated synthetic test
From package root, if a local C17 compiler is already available:
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -Iinclude src/stosnet_boundary.c tests/test_boundary.c -o /tmp/stosnet-boundary-test
/tmp/stosnet-boundary-test
This is a policy-gate unit test, not a security certification. It makes no network connections.
No compilation or service activation is needed to inspect the source.
