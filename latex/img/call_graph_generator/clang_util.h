// clang_util.h

#include "clang-c/Index.h"

#include <vector>
#include <unordered_map>
#include <iostream>

using Mangle = std::string;
using TUs = std::unordered_map<std::string, CXTranslationUnit>;

Mangle get_mangle(CXCursor c);

extern CXIndex index;
extern TUs tus;

void init();
void cleanup();

extern const std::string cpp_dir;
extern const std::string inc_dir;
extern const std::string src_dir;
extern const std::string cmp_I;

extern std::vector<std::string> mwt_files;
extern std::vector<std::string> test_files;
std::vector<std::string> get_all_files();

bool cursor_is_in_my_files(CXCursor c, const std::vector<std::string>&);

extern const char* compile_options[];

std::string to_string(CXString s);
std::ostream &operator<<(std::ostream &o, CXString s);

struct cursor_loc {
  std::string file;
  unsigned firstline;
  unsigned lastline;
  cursor_loc(CXCursor c);
};

std::ostream &operator<<(std::ostream &o, const cursor_loc &loc);

std::string get_def_kind(CXCursor);

struct cx_attrs {
  cursor_loc loc;
  std::string name;
  Mangle mangle;
  std::string def_kind;
  cx_attrs(CXCursor c) : loc{c}, name{to_string(clang_getCursorSpelling(c))}, 
                         mangle{get_mangle(c)}, def_kind{get_def_kind(c)} {}
};

std::ostream &operator<<(std::ostream &, const cx_attrs&);

