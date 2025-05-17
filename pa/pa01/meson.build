project(
  'pa01',
  'cpp',
  default_options: ['cpp_std=c++20', 'warning_level=2', 'b_lundef=false'],
)

executable(
  'game_set',
  ['main_set.cpp', 'card.cpp', 'game_set.cpp'], # card.h is implicitly found
  install: true,
)

executable(
  'game',
  ['main.cpp', 'card_list.cpp', 'card.cpp'], # card_list.h is implicitly found
  install: true,
)

tests_exe = executable('tests', ['tests.cpp', 'card.cpp', 'card_list.cpp', 'game_set.cpp'])

test('unit_tests', tests_exe)
