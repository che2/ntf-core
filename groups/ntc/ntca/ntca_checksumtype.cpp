// Copyright 2020-2023 Bloomberg Finance L.P.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <ntca_checksumtype.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(ntca_checksumtype_cpp, "$Id$ $CSID$")

#include <bdlb_string.h>
#include <bsls_assert.h>
#include <bsl_ostream.h>

namespace BloombergLP {
namespace ntca {

int ChecksumType::fromInt(ChecksumType::Value* result, int number)
{
    switch (number) {
    case ChecksumType::e_UNDEFINED:
    case ChecksumType::e_ADLER32:
    case ChecksumType::e_CRC32:
    case ChecksumType::e_XXH32:
        *result = static_cast<ChecksumType::Value>(number);
        return 0;
    default:
        return -1;
    }
}

int ChecksumType::fromString(ChecksumType::Value*     result,
                             const bslstl::StringRef& string)
{
    if (bdlb::String::areEqualCaseless(string, "UNDEFINED")) {
        *result = e_UNDEFINED;
        return 0;
    }
    if (bdlb::String::areEqualCaseless(string, "ADLER32")) {
        *result = e_ADLER32;
        return 0;
    }
    if (bdlb::String::areEqualCaseless(string, "CRC32")) {
        *result = e_CRC32;
        return 0;
    }
    if (bdlb::String::areEqualCaseless(string, "XXH32")) {
        *result = e_XXH32;
        return 0;
    }

    return -1;
}

const char* ChecksumType::toString(ChecksumType::Value value)
{
    switch (value) {
    case e_UNDEFINED: {
        return "UNDEFINED";
    } break;
    case e_ADLER32: {
        return "ADLER32";
    } break;
    case e_CRC32: {
        return "CRC32";
    } break;
    case e_XXH32: {
        return "XXH32";
    } break;
    }

    BSLS_ASSERT(!"invalid enumerator");
    return 0;
}

bsl::ostream& ChecksumType::print(bsl::ostream&       stream,
                                  ChecksumType::Value value)
{
    return stream << toString(value);
}

bsl::ostream& operator<<(bsl::ostream& stream, ChecksumType::Value rhs)
{
    return ChecksumType::print(stream, rhs);
}

}  // close package namespace
}  // close enterprise namespace
