#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "rrtmgp.hpp"

namespace {

TEST_CASE("Rrtmgp", "stub") {
  int val = scream::rrtmgp::rrtmgp_stub();
  REQUIRE(val == 42);
}

} // empty namespace
