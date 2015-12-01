/*  =========================================================================
    zeb_handler - Handler for XRAP requests

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of ZWEBRAP.                                      
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef ZEB_HANDLER_H_INCLUDED
#define ZEB_HANDLER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  @warning THE FOLLOWING @INTERFACE BLOCK IS AUTO-GENERATED BY ZPROJECT!
//  @warning Please edit the model at "api/zeb_handler.xml" to make changes.
//  @interface
// Handle an incomming XRAP request. Callee keeps ownership of the request.
typedef xrap_msg_t * (zeb_handler_handle_request_fn) (
    xrap_msg_t *xrequest);

// Checks if the request etag matches our current one. Returns true if etags
// match, otherwise false.                                                  
typedef bool (zeb_handler_check_etag_fn) (
    const char *etag);

// Checks if the request last modified timestamp matches our current one.
// Returns true if timestamps match, otherwise false.                    
typedef bool (zeb_handler_check_last_modified_fn) (
    const uint64_t last_modified);

//  Create a new zeb_handler
ZWEBRAP_EXPORT zeb_handler_t *
    zeb_handler_new (const char *endpoint);

//  Destroy the zeb_handler
ZWEBRAP_EXPORT void
    zeb_handler_destroy (zeb_handler_t **self_p);

//  Add a new offer this handler will handle. Returns 0 if successful,
//  otherwise -1.                                                     
ZWEBRAP_EXPORT int
    zeb_handler_add_offer (zeb_handler_t *self, int method, const char *uri);

//  Add a new accept type that this handler can deliver. May be a regular
//  expression. Returns 0 if successfull, otherwise -1.                  
ZWEBRAP_EXPORT int
    zeb_handler_add_accept (zeb_handler_t *self, const char *accept);

//  Set a callback handler to handle incoming requests. Returns the response
//  to be send back to the client.                                          
ZWEBRAP_EXPORT void
    zeb_handler_set_handle_request_fn (zeb_handler_t *self, zeb_handler_handle_request_fn *handle_request_fn);

//  Set a callback handler to check if provided etag matches the current one.
//  Returns true if etags match, otherwise false.                            
ZWEBRAP_EXPORT void
    zeb_handler_set_check_etag_fn (zeb_handler_t *self, zeb_handler_check_etag_fn *check_etag_fn);

//  Set a callback handler to check if provided last_modified timestamp matches
//  the current one. Returns true if timestamp match, otherwise false.         
ZWEBRAP_EXPORT void
    zeb_handler_set_check_last_modified_fn (zeb_handler_t *self, zeb_handler_check_last_modified_fn *last_modified_fn);

//  Self test of this class.
ZWEBRAP_EXPORT void
    zeb_handler_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
