//  Copyright (c) 2017-present The storage Authors.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>
#include <cstring>
#include <cmath>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace storage {

  uint32_t Digits10(uint64_t v);
  int Int64ToStr(char* dst, size_t dstlen, int64_t svalue);
  int StrToInt64(const char *s, size_t slen, int64_t *value);
  int StringMatch(const char *pattern, int pattern_len, const char *string,
                  int string_len, int nocase);
  int StrToLongDouble(const char* s, size_t slen, long double* ldval);
  int LongDoubleToStr(long double ldval, std::string* value);
  int do_mkdir(const char *path, mode_t mode);
  int mkpath(const char *path, mode_t mode);
  int delete_dir(const char* dirname);
  int is_dir(const char* filename);
  int CalculateMetaStartAndEndKey(const std::string& key, std::string* meta_start_key, std::string* meta_end_key);
  int CalculateDataStartAndEndKey(const std::string& key, std::string* data_start_key, std::string* data_end_key);
  bool isTailWildcard(const std::string& pattern);
  void GetFilepath(const char *path, const char *filename,  char *filepath);
  bool DeleteFiles(const char* path);
}

#endif  //  SRC_UTIL_H_
