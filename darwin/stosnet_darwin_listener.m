/*
 * macOS Network.framework listener construction candidate.
 * NOT RUNNABLE: no nw_listener_start call, no public accept handler,
 * no certificate provisioning, and no claimed client-authentication.
 * macOS SDK compilation and API availability require target verification.
 */
#if defined(__APPLE__)
#import <Foundation/Foundation.h>
#import <Network/Network.h>
#import <Security/Security.h>
#import <Security/SecProtocolOptions.h>
/* A deliberately non-starting TLS parameter factory. The caller owns the result.
 * It cannot grant STOSnet access or expose an interface. */
nw_parameters_t stosnet_v6_darwin_tls_parameters(void) {
    nw_parameters_t parameters = nw_parameters_create_secure_tcp(
        ^(nw_protocol_options_t tls_options) {
            sec_protocol_options_t options =
                nw_tls_copy_sec_protocol_options(tls_options);
            sec_protocol_options_set_min_tls_protocol_version(
                options, tls_protocol_version_TLSv13);
            sec_protocol_options_set_max_tls_protocol_version(
                options, tls_protocol_version_TLSv13);
            /* No identity or peer-auth callback is supplied: not operational. */
        },
        NW_PARAMETERS_DEFAULT_CONFIGURATION);
    if (parameters) nw_parameters_set_local_only(parameters, true);
    return parameters;
}
#else
int stosnet_v6_darwin_tls_parameters_unavailable(void) { return -1; }
#endif
