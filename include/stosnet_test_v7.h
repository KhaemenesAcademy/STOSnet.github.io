#ifndef STOSNET_TEST_V7_H
#define STOSNET_TEST_V7_H
#include <stdint.h>
typedef enum { STOSNET_V7_DENY=0, STOSNET_V7_TEST_ONLY=1 } stosnet_v7_result;
typedef struct {
    uint16_t port;
    uint8_t explicit_test_approval;
    uint8_t loopback_only;
    uint8_t tls13_required;
    uint8_t peer_certificate_required;
    uint8_t identity_selected;
    uint8_t app_routes_disabled;
    uint8_t proxy_disabled;
    uint8_t storage_disabled;
    uint8_t local_authority_disabled;
} stosnet_v7_test_config;
stosnet_v7_result stosnet_v7_test_config_check(const stosnet_v7_test_config *cfg);
#endif
