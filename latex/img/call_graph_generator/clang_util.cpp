// clang_util.cpp

#include "clang_util.h"

#include <algorithm>
#include <iomanip>

using namespace std;

CXIndex index;
TUs tus;

Mangle get_mangle(CXCursor c) {
  if (clang_Cursor_isNull(c)) return "";
  return to_string(clang_Cursor_getMangling(c));
}

auto get_TU = [](const string &filename) {
    return clang_parseTranslationUnit(index,
                filename.c_str(),
                compile_options,
                1,
                0,0,
                CXTranslationUnit_KeepGoing);
};

void init() {
  index = clang_createIndex(0,0);
  auto files = get_all_files();
  for (auto &&file : files) { 
    CXTranslationUnit tu = get_TU(file);
    if (!tu) {
      cerr << "error parsing: " << file << endl;
    } else {
      tus[file] = tu;
    }
  }
}

void cleanup() {
  for (auto kv : tus) { clang_disposeTranslationUnit(kv.second); }
  clang_disposeIndex(index);
}

//const std::string cpp_dir{"/home/uphill/programming/mwt/cpp/"};
const std::string cpp_dir{"../../../cpp/"};
const std::string inc_dir{cpp_dir + "include/"};
const std::string src_dir{cpp_dir + "src/"};
const std::string test_dir{cpp_dir + "testing/"};
const std::string cmp_I1{"-I" + inc_dir};
const std::string cmp_I2{"-I" + test_dir};

std::vector<std::string> mwt_files {
  src_dir + "polyhedra.cpp"s,
  src_dir + "fourier_motzkin.cpp"s,
  src_dir + "linear_algebra.cpp"s,
  inc_dir + "polyhedra.h"s,
  inc_dir + "fourier_motzkin.h"s,
  inc_dir + "linear_algebra.h"s,
};

std::vector<std::string> test_files {
  test_dir + "test_functions.cpp"s,
  test_dir + "test_functions.h"s
};

vector<string> get_all_files() {
  vector<string> result;
  for (auto &&file : mwt_files)  result.push_back(file);
  for (auto &&file : test_files) result.push_back(file);
  return result;
}

bool cursor_is_in_my_files(CXCursor c, const vector<string> &files) {
  cursor_loc loc{c};
  return find(files.begin(), files.end(), loc.file) != files.end();
}

const char* compile_options[]{
  cmp_I1.c_str(),
  cmp_I2.c_str(),
};

string to_string(CXString s) {
  string result{clang_getCString(s)};
  clang_disposeString(s);
  return result;
}

ostream &operator<<(ostream &o, CXString s) {
  o << to_string(s);
  return o;
}

cursor_loc::cursor_loc(CXCursor c) {
  CXSourceRange range = clang_getCursorExtent(c);
  CXFile f{};
  clang_getSpellingLocation(clang_getRangeStart(range),0,&firstline,0,0);
  clang_getSpellingLocation(clang_getRangeEnd(range),&f,&lastline,0,0);
  file = f ? to_string(clang_getFileName(f)) : "";
}

ostream &operator<<(ostream &o, const cursor_loc &loc) {
  return o << "\t\tfilename=\"" << loc.file << "\",\n\t\tfirstline=" << loc.firstline 
           << ",\n\t\tlastline=" << loc.lastline;
}

ostream &operator<<(ostream &o, const cx_attrs &attrs) {
  //return o << setw(40) << left << attrs.mangle 
  //return o << setw(10) << left << attrs.def_kind  << endl;
  return o << "[\n\t\t" << "label=\"" << attrs.name << "\",\n"
           << attrs.loc << "\n\t]";
}

std::string get_def_kind(CXCursor c) {
  if        (clang_getCursorKind(c) == CXCursor_FunctionDecl) {
    return "function";
  } else if (clang_getCursorKind(c) == CXCursor_StructDecl) {
    return "struct";
  } else if (clang_getCursorKind(c) == CXCursor_ClassDecl) {
    return "class";
  } else {
    return "unk";
  }
}
