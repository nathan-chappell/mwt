// graph.cpp

#include "graph.h"

#include <algorithm>

using namespace std;

vector<string> excluded_names {
  "",
  "operator>>",
  "operator<<",
  "usage",
  "read_dimension",
  "get_d",
  "log"
};

bool is_fn_def(CXCursor c, const vector<string> &filenames) {
  return clang_getCursorKind(c) == CXCursor_FunctionDecl &&
         clang_equalCursors(c, clang_getCursorDefinition(c)) &&
         cursor_is_in_my_files(c, filenames);
}

bool excluded_name(CXCursor c) {
  string name{to_string(clang_getCursorSpelling(c))};
  return find(excluded_names.begin(), 
              excluded_names.end(), name) != excluded_names.end();
}

bool is_fn_call(CXCursor c) {
  return clang_getCursorKind(c) == CXCursor_CallExpr;
}

// data is graph
CXChildVisitResult get_graph_nodes(CXCursor c, CXCursor p, CXClientData data) {
  graph &g = *static_cast<graph*>(data);
  if (is_fn_def(c, g.filenames)) {
    g.add_N(c);
    return CXChildVisit_Continue;
  }
  return CXChildVisit_Recurse;
}

// data is graph
CXChildVisitResult get_graph_edges(CXCursor c, CXCursor p, CXClientData data) {
  graph &g = *static_cast<graph*>(data);
  if (g.set_cur(c)) {
    clang_visitChildren(c, add_calls_to_graph, &g);
    return CXChildVisit_Continue;
  }
  return CXChildVisit_Recurse;
}

// data is graph
CXChildVisitResult add_calls_to_graph(CXCursor c, CXCursor p, CXClientData data) {
  graph &g = *static_cast<graph*>(data);
  CXCursor c_ref = clang_getCursorReferenced(c);
  if (is_fn_call(c) && g.in_N(c_ref)) {
    g.add_E(c_ref); // adds based on g.cur
  }
  return CXChildVisit_Recurse;
}

bool graph::add_N(CXCursor c) {
  if (excluded_name(c)) return false;
  if (is_fn_def(c, filenames)) {
    N.emplace(get_mangle(c), c);
    return true;
  }
  return false;
}

void graph::add_E(CXCursor head) {
  if (in_N(head)) {
    E[get_mangle(cur)].insert(get_mangle(head));
  }
}

bool graph::in_N(CXCursor c) {
  if (excluded_name(c)) return false;
  if (get_mangle(c) == "") { return false; }
  return N.count(get_mangle(c));
}

bool graph::set_cur(CXCursor c) {
  if (in_N(c)) {
    cur = c;
    return true;
  }
  return false;
}

graph graph::create_from_filenames(const vector<string> &filenames) {
  graph g;
  g.filenames = filenames;
  // add all nodes
  cerr << "adding nodes" << endl;
  for (auto &&file : filenames) {
  cerr << file << endl;
    clang_visitChildren(
      clang_getTranslationUnitCursor(tus[file]), get_graph_nodes, &g);
  }
  cerr << "adding edges" << endl;
  // look for edges
  for (auto &&file : filenames) {
  cerr << file << endl;
    clang_visitChildren(
      clang_getTranslationUnitCursor(tus[file]), get_graph_edges, &g);
  }
  return g;
}

ostream &operator<<(ostream &o, const graph &g) {
  o << "strict digraph {\n";
  o << "\tgraph [rankdir=LR]\n";
  o << "\tnode [shape=\"rectangle\", fontname=\"Courier\"]\n";
  for (auto &&kv : g.N) { o << "\t" << kv.first << " " << kv.second << "\n"; }
  o << "\n";
  for (auto &&kv : g.E) { 
    for (auto &&head : kv.second) {
      o << "\t" << kv.first << " -> " << head << "\n"; 
    }
  }
  return o << "}";
}
