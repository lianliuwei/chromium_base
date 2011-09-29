// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/i18n/case_conversion.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

#include "base/string16.h"
// #include "unicode/unistr.h"


namespace base {
namespace i18n {

// string16 ToLower(const StringPiece16& string) {
//   icu::UnicodeString unicode_string(string.data(), string.size());
//   unicode_string.toLower();
//   return string16(unicode_string.getBuffer(), unicode_string.length());
// }
// 
// string16 ToUpper(const StringPiece16& string) {
//   icu::UnicodeString unicode_string(string.data(), string.size());
//   unicode_string.toUpper();
//   return string16(unicode_string.getBuffer(), unicode_string.length());
//}
string16 ToLower(const StringPiece16& string)
{
    // WLW TODO: fix it.
    string16 lower(string.data());
    CharLowerW(const_cast<LPWSTR>(lower.c_str()));
    return lower;
}

string16 ToUpper(const StringPiece16& string)
{
    // WLW TODO: fix it.
    string16 upper(string.data());
    CharUpperW(const_cast<LPWSTR>(upper.c_str()));
    return upper;
}

}  // namespace i18n
}  // namespace base
