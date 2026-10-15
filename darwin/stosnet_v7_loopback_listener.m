/*
 * STOSnet v0.7 test-only Darwin TLS listener candidate.
 * NOT SDK-COMPILED OR RUN in this package. NOT commissioned.
 * NO STOS routes, proxy, storage, enrollment or authority.
 * Operator must review API compatibility, certificate policy and build before use.
 */
#import <Foundation/Foundation.h>
#import <Network/Network.h>
#import <Security/Security.h>
#import <Security/SecProtocolOptions.h>
#import <Security/SecProtocolMetadata.h>
#import <dispatch/dispatch.h>
#include <stdlib.h>
#include <string.h>
#include "stosnet_test_v7.h"

static SecIdentityRef identity_with_label(NSString *label) {
    NSDictionary *query = @{
        (__bridge id)kSecClass: (__bridge id)kSecClassIdentity,
        (__bridge id)kSecAttrLabel: label,
        (__bridge id)kSecReturnRef: @YES,
        (__bridge id)kSecMatchLimit: (__bridge id)kSecMatchLimitOne
    };
    CFTypeRef found = NULL;
    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)query, &found);
    if (status != errSecSuccess || !found) return NULL;
    if (CFGetTypeID(found) != SecIdentityGetTypeID()) {
        CFRelease(found);
        return NULL;
    }
    return (SecIdentityRef)found;
}

int main(int argc, const char *argv[]) {
    @autoreleasepool {
        if (argc != 4 || strcmp(argv[1], "--run-test") != 0 ||
            strcmp(argv[2], "--identity-label") != 0) {
            fprintf(stderr, "No listener started. Usage: %s --run-test --identity-label LABEL\n", argv[0]);
            return 2;
        }
        const char *approval = getenv("STOSNET_V7_TEST_APPROVED");
        if (!approval || strcmp(approval, "YES") != 0) {
            fprintf(stderr, "Explicit isolated test approval absent; denied.\n");
            return 3;
        }
        NSString *label = [NSString stringWithUTF8String:argv[3]];
        if (!label || label.length == 0) return 4;
        SecIdentityRef identity = identity_with_label(label);
        if (!identity) {
            fprintf(stderr, "Selected Keychain identity unavailable; denied.\n");
            return 5;
        }
        stosnet_v7_test_config gate = {18443,1,1,1,1,1,1,1,1,1};
        if (stosnet_v7_test_config_check(&gate) != STOSNET_V7_TEST_ONLY) {
            CFRelease(identity);
            return 6;
        }
        sec_identity_t tls_identity = sec_identity_create(identity);
        CFRelease(identity);
        if (!tls_identity) return 7;
        nw_parameters_t parameters = nw_parameters_create_secure_tcp(
            ^(nw_protocol_options_t options) {
                sec_protocol_options_t tls = nw_tls_copy_sec_protocol_options(options);
                sec_protocol_options_set_min_tls_protocol_version(tls, tls_protocol_version_TLSv13);
                sec_protocol_options_set_max_tls_protocol_version(tls, tls_protocol_version_TLSv13);
                sec_protocol_options_set_local_identity(tls, tls_identity);
                sec_protocol_options_set_peer_authentication_required(tls, true);
                sec_protocol_options_set_verify_block(tls,
                    ^(sec_protocol_metadata_t metadata, sec_trust_t peer_trust,
                      sec_protocol_verify_complete_t complete) {
                        (void)metadata;
                        SecTrustRef trust = sec_trust_copy_ref(peer_trust);
                        if (!trust) { complete(false); return; }
                        /* System trust alone is NOT STOS device enrollment. */
                        Boolean valid = SecTrustEvaluateWithError(trust, NULL);
                        CFRelease(trust);
                        complete(valid);
                    }, dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0));
            }, NW_PARAMETERS_DEFAULT_CONFIGURATION);
        if (!parameters) return 8;
        nw_endpoint_t local = nw_endpoint_create_host("127.0.0.1", "18443");
        nw_parameters_set_local_endpoint(parameters, local);
        nw_listener_t listener = nw_listener_create(parameters);
        if (!listener) return 9;
        dispatch_queue_t queue = dispatch_queue_create("stosnet.v7.test", DISPATCH_QUEUE_SERIAL);
        __block unsigned active = 0;
        nw_listener_set_new_connection_handler(listener, ^(nw_connection_t connection) {
            if (active >= 1) { nw_connection_cancel(connection); return; }
            active++;
            nw_connection_set_queue(connection, queue);
            nw_connection_set_state_changed_handler(connection,
                ^(nw_connection_state_t state, nw_error_t error) {
                    (void)error;
                    if (state == nw_connection_state_ready) {
                        /* TLS ready, then close. Never accept application bytes. */
                        nw_connection_cancel(connection);
                    } else if (state == nw_connection_state_failed) {
                        nw_connection_cancel(connection);
                    } else if (state == nw_connection_state_cancelled) {
                        if (active) active--;
                    }
                });
            nw_connection_start(connection);
        });
        nw_listener_set_state_changed_handler(listener,
            ^(nw_listener_state_t state, nw_error_t error) {
                (void)error;
                if (state == nw_listener_state_failed) {
                    nw_listener_cancel(listener);
                }
            });
        nw_listener_set_queue(listener, queue);
        nw_listener_start(listener);
        fprintf(stderr, "STOSnet TEST ONLY: requested 127.0.0.1:18443; no application routes.\n");
        dispatch_main();
    }
}
