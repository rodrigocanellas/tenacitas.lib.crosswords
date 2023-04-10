/// \copyright This file is under GPL 3 license. Please read the \p LICENSE file
/// at the root of \p tenacitas directory

/// \author Rodrigo Canellas - rodrigo.canellas at gmail.com

#include <cstdint>
#include <iterator>
#include <string>

#include <tenacitas/lib/crosswords/typ/grid.h>
#include <tenacitas/lib/log/alg/logger.h>
#include <tenacitas/lib/program/alg/options.h>
#include <tenacitas/lib/test/alg/tester.h>

using namespace tenacitas::lib;

struct test_000 {
  static std::string desc() { return "'layout' creation"; }

  bool operator()(const program::alg::options &) {
    using namespace crosswords::typ;
    entries _entries{
        {"open", "expl 1"}, {"window", "expl 2"}, {"door", "expl 3"}};

    layout _layout(std::next(_entries.begin(), 1));
    _layout.set_row(2);
    _layout.set_col(3);
    _layout.set_orientation(orientation::hori);

    TNCT_LOG_TST(_layout);

    return (_layout.get_word() == "window") && (_layout.get_row() == 2) &&
           (_layout.get_col() == 3) &&
           (_layout.get_orientation() == orientation::hori);
  }
};

struct test_001 {
  static std::string desc() { return "complex 'grid' creation"; }

  bool operator()(const program::alg::options &) {
    using namespace crosswords;
    typ::entries _entries{
        {"open", "expl 1"}, {"window", "expl 2"}, {"door", "expl 3"}};

    typ::entries::const_entry_ite _begin{_entries.begin()};

    typ::permutation _permutation;
    _permutation.push_back(std::next(_begin, 2));
    _permutation.push_back(std::next(_begin, 0));
    _permutation.push_back(std::next(_begin, 1));

    typ::grid _grid(_permutation, typ::index{11}, typ::index{8});

    _grid.set(_grid.begin(), typ::index{1}, typ::index{3},
              typ::orientation::vert);
    _grid.set(std::next(_grid.begin(), 1), typ::index{6}, typ::index{1},
              typ::orientation::hori);
    _grid.set(std::next(_grid.begin(), 2), typ::index{2}, typ::index{7},
              typ::orientation::vert);

    TNCT_LOG_TST(_grid);
    typ::grid::layouts::const_iterator _g_begin = _grid.begin();

    return (

        (_g_begin->get_word() == "door") && (_g_begin->get_row() == 1) &&
        (_g_begin->get_col() == 3) &&
        (_g_begin->get_orientation() == typ::orientation::vert)

        &&

        (std::next(_g_begin, 1)->get_word() == "open") &&
        (std::next(_g_begin, 1)->get_row() == 6) &&
        (std::next(_g_begin, 1)->get_col() == 1) &&
        (std::next(_g_begin, 1)->get_orientation() == typ::orientation::hori)

        &&

        (std::next(_g_begin, 2)->get_word() == "window") &&
        (std::next(_g_begin, 2)->get_row() == 2) &&
        (std::next(_g_begin, 2)->get_col() == 7) &&
        (std::next(_g_begin, 2)->get_orientation() == typ::orientation::vert)

    );
  }
};

struct test_002 {
  static std::string desc() { return "simple 'grid' creation"; }

  bool operator()(const program::alg::options &) {
    using namespace crosswords;
    typ::entries _entries{{"open", "expl 1"}};

    typ::entries::const_entry_ite _begin{_entries.begin()};

    typ::permutation _permutation;
    _permutation.push_back(std::next(_begin, 0));

    typ::grid _grid(_permutation, typ::index{11}, typ::index{7});

    _grid.set(_grid.begin(), typ::index{1}, typ::index{3},
              typ::orientation::vert);

    TNCT_LOG_TST(_grid);
    typ::grid::layouts::const_iterator _g_begin = _grid.begin();

    return ((_g_begin->get_word() == "open") && (_g_begin->get_row() == 1) &&
            (_g_begin->get_col() == 3) &&
            (_g_begin->get_orientation() == typ::orientation::vert));
  }
};

int main(int argc, char **argv) {

  tester::alg::test _test(argc, argv);

  run_test(_test, test_000);
  run_test(_test, test_001);
  run_test(_test, test_002);
}
