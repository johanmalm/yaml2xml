project(
  'yaml2xml',
  'c',
  version: '0.1.0',
  license: 'GPL-2.0-only',
  default_options: [
    'c_std=c11',
    'warning_level=2',
  ],
)

yaml = dependency('yaml-0.1')

yaml2xml_inc = include_directories('.')
subdir('t')

executable(
  meson.project_name(),
  sources: files(
    'main.c',
    'parse.c',
    'buf.c',
  ),
  dependencies: yaml,
  install: true,
)
