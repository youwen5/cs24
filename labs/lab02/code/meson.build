project(
  'intlist_project',
  'cpp',
  default_options: ['warning_level=1', 'cpp_std=c++11'],
)

intlist_sources = ['intlist.cpp']
testlist_sources = ['testlist.cpp']
testrest_sources = ['testrest.cpp']

executable('testlist', testlist_sources + intlist_sources, install: true)

executable('testrest', testrest_sources + intlist_sources, install: true)
