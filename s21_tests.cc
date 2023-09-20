#include "tests/array_test.cc"
#include "tests/list_test.cc"
#include "tests/map_test.cc"
#include "tests/set_stack_queue_test.cc"
#include "tests/vector_test.cc"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}