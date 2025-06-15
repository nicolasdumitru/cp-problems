# The default recipe is always the first recipe in the justfile

# The recipe to run when just is invoked without a recipe
default: list

# List available recipes
list:
    @just --list

# Enter a development shell
develop shell='bash':
    nix develop --command '{{shell}}'
alias dev := develop

build_dir := 'target'

setup build_type=default_build_type setup_type=default_setup_type:
    meson setup {{build_dir}} --{{setup_type}} --backend=ninja --buildtype={{build_type}}
    ln -sf {{build_dir}}/compile_commands.json compile_commands.json
default_build_type := 'release'
default_setup_type := 'reconfigure'

wipe build_type=default_build_type: (setup build_type 'wipe')

build:
    meson compile -C {{build_dir}}

run args='': build
    ./{{build_dir}}/main {{args}}

clean:
    meson compile -C {{build_dir}} --clean

distclean:
    rm -rf {{build_dir}}
    rm -f compile_commands.json

# Update the lockfile and commit it
update:
    nix flake update --commit-lock-file

# Format all files
format:
    clang-format -i $(fd '\.cpp$' --full-path "$(git rev-parse --show-toplevel)")
    nixfmt $(fd '\.nix$' --full-path "$(git rev-parse --show-toplevel)")
alias fmt := format
