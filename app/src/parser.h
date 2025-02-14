/*******************************************************************************
 *   (c) 2019 Zondax GmbH
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "crypto.h"
#include "hexutils.h"
#include "parser_common.h"
#include "parser_txdef.h"

extern parser_tx_t parser_state;
const char *parser_getErrorDescription(parser_error_t err);

//// parses a tx buffer
parser_error_t parser_parse(parser_context_t *ctx, const uint8_t *data, size_t dataLen);

//// verifies tx fields
parser_error_t parser_validate(const parser_context_t *ctx);

//// returns the number of items in the current parsing context
parser_error_t parser_getNumItems(const parser_context_t *ctx, uint8_t *num_items);

// retrieves a readable output for each field / page
parser_error_t parser_getItem(const parser_context_t *ctx, uint16_t displayIdx, char *outKey, uint16_t outKeyLen,
                              char *outVal, uint16_t outValLen, uint8_t pageIdx, uint8_t *pageCount);

/// Gets the transaction authorization type
parser_error_t parser_tx_auth_flag(uint8_t *flag);

/// Gets the origin fee as bytes
uint8_t parser_tx_fee(uint8_t *fee, uint16_t fee_len);

/// Gets the origin nonce as bytes
uint8_t parser_tx_nonce(uint8_t *nonce, uint16_t nonce_len);

// Writes in buf the authorization fields that are zeroize according
// to the documentation. returns the amount of bytes written
// the passes_in buffer is the second block for hashing
uint16_t parser_presig_hash_data(uint8_t *buf, uint16_t bufLen);

// When signing the full transaction, The transaction hash has to be done in blocks.
// this function returns a pointer to the last transaction block and its lenght
uint16_t parser_last_transaction_block(uint8_t **last_block);

// Returns 1 if the transaction is multisig, 0 otherwise
int8_t parser_is_transaction_multisig();

// Returns # of fields in a multisig spending condition, or 0 if not multisig
uint32_t parser_num_multisig_fields();

// Fill in multisig field id and data pointer for field `index`
parser_error_t parser_get_multisig_field(uint32_t index, uint8_t *id, uint8_t **data);

// Get transaction's spending condition hash mode field
parser_error_t parser_hash_mode(uint8_t *hash_mode);

// Gets a pointer to the previous signer signature, post_sig_hash and pubkey type
// that is the last part of a lultisig transaction buffer
uint16_t parser_previous_signer_data(uint8_t **data);

void parser_resetState();

transaction_type_t parser_get_transaction_type();

zxerr_t parser_structured_msg_hash(uint8_t *out, uint16_t out_len);

#ifdef __cplusplus
}
#endif
