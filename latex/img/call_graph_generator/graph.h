// graph.h

#include "clang_util.h"

#include <unordered_map>
#include <set>

bool excluded_name(CXCursor c);
bool is_fn_call(CXCursor c);
bool is_fn_def(CXCursor c);

CXChildVisitResult get_graph_nodes(CXCursor c, CXCursor p, CXClientData data);
CXChildVisitResult get_graph_edges(CXCursor c, CXCursor p, CXClientData data);
CXChildVisitResult add_calls_to_graph(CXCursor c, CXCursor p, CXClientData data);

class graph {
  std::unordered_map<Mangle, cx_attrs> N;
  std::unordered_map<Mangle, std::set<Mangle>> E;
  CXCursor cur; // used as tail in add_E, invariant: in_N(cur) || null
  protected:
  graph() : cur{clang_getNullCursor()} {}
  public:
  std::vector<std::string> filenames;

  bool add_N(CXCursor c);
  void add_E(CXCursor head);
  bool in_N(CXCursor c);
  bool set_cur(CXCursor c);
  static graph create_from_filenames(const std::vector<std::string>&);
  friend std::ostream &operator<<(std::ostream &o, const graph &g);
};

std::ostream &operator<<(std::ostream &, const graph&);

