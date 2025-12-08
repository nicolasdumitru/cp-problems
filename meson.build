project(
  'CP-Problems',
  'cpp',
  version: '0.0.0',
  default_options : [
    'cpp_std=c++20',
    'warning_level=3',
    'b_sanitize=undefined',
    'b_lundef=false'
  ]
)

extra_warning_flags = [
  '-pedantic',
  '-Wshadow',
  '-Wconversion',
  '-Wfloat-equal',
]

add_project_arguments(extra_warning_flags, language: 'cpp')

src = files('src/main.cpp')
executable('main', src)
