test_lib_sources = files(
    '../buf.c',
)

dep_cmocka = dependency('cmocka')
yaml = dependency('yaml-0.1')
test_deps = [
  dep_cmocka,
  yaml,
]

tests = [
  'simple',
]

test_lib = static_library(
  'test_lib',
  sources: test_lib_sources,
  include_directories: [yaml2xml_inc],
  dependencies: test_deps
)

foreach t : tests
  test(
    'test_@0@'.format(t),
    executable(
      'test_@0@'.format(t),
      sources: '@0@.c'.format(t),
      link_with: [test_lib],
    ),
    is_parallel: false,
  )
endforeach
