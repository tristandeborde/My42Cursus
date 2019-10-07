#!/usr/bin/python3

import argparse

## This is a python script file to generate a .travis.yml file according to some contents.
## To update the .travis.yml file, you just have to run python3 .travis_gen.py > .travis.yml

LANG = "cpp"
LINUX = "linux"
OSX = "osx"
OS = [LINUX, OSX]
DIST_LINUX = "xenial"
OSX_IMG = "xcode9.4"
COMPILER = "clang"

J_BASE = "Base"
J_LINT = "Lint"
JOBS = [J_BASE, J_LINT]

# There are 2 stages,
#   - Base tests the global tests, and do some tests to prevent human errors when filling files.mk for example.
#       Linters needs files.mk to have the right filenames.
#   - Lint tests running some external tools according to filenames.

# Base is a stage that test the following things
#  - it tests if the .travis.yml file was modified directly without modifying this script.
#       We want here to modify this script instead of the .travis.yml file
#  - it tests if the project compile

SDL_DEPS = ["libsdl2-dev", "libsdl2-ttf-dev", "libglm-dev", "libglew-dev", "libassimp-dev", "libsdl2-image-dev", "libglfw3-dev"]

BASE_TASKS = [
    (J_BASE, LINUX, False, "verifying travis.yml file", [], ["python3 .travis_gen.py > expected.out", "diff .travis.yml expected.out"]),
    (J_BASE, LINUX, False, "compile bombler - Linux", SDL_DEPS, ["make re"]),
    (J_BASE, OSX, False, "compile bombler - OSX", ["SDL2", "SDL2_ttf", "glm", "glew", "glfw", "assimp", "sdl2_image"], ["make re"]),
]

# Lint is a stage that test the project using some external tools
#  - uncrustify, checks if the code respects the norm definned in the UNCRUSTIFY.cfg file
#  - cpplint, cppcheck, clang-tidy, infer, checks leaks, known errors and undefined behaviours

LINT_TASKS = [
    (J_LINT, LINUX, False, "uncrustify", [], ["make -f lint.mk uncrustify_check"]),
    (J_LINT, LINUX, False, "cpplint", ["python3-venv"], ["make -f lint.mk cpplint"]),
    (J_LINT, LINUX, False, "cppcheck", ["cppcheck"], ["make -f lint.mk cppcheck"]),
    (J_LINT, LINUX, True, "clang-tidy", ["clang-tidy-6.0", "clang-6.0"] + SDL_DEPS, ["make -f lint.mk clang_tidy"]),
]

DOCKER_EXEC_PREFIX = "docker exec -t cpp bash -c \""
DOCKER_EXEC_SUFFIX = "\""

DOCKER_BUILD = "docker build -t cpp ."
DOCKER_BACKGROUND = "docker run --rm --detach --volume `pwd`:/code --workdir /code --name cpp cpp tail -f /dev/null"
DOCKER_STOP = "docker stop cpp"

LINUX_INSTALL = "apt-get install -y --no-install-recommends"
BREW_INSTALL = "brew install"

TASKS = BASE_TASKS + LINT_TASKS


def print_travis_config():
    def print_header():
        print("language:", LANG)
        print("compiler:", COMPILER)
        print("git:")
        print("  depth: false")
        print("  gitsubmodules: false")
        print()
        print("stages:")
        for job in JOBS:
            print("  -", job)
        print()

    def print_dep(is_docker, deps, os):
        prefix = DOCKER_EXEC_PREFIX if is_docker else "sudo"
        suffix = DOCKER_EXEC_SUFFIX if is_docker else ""
        if len(deps) is not 0:
            print("      install:")
            if os == LINUX:
                print("        -", prefix, "apt update", suffix)
                print("        -", prefix, LINUX_INSTALL, " ".join(deps), suffix)
            else:
                print("        -", BREW_INSTALL, " ".join(deps))

    def print_docker_before_install():
        print("      before_install:")
        print("        - " + DOCKER_BUILD)
        print("        - " + DOCKER_BACKGROUND)

    def print_docker_after_script():
        print("      after_script:")
        print("        - " + DOCKER_STOP)

    def print_task(task):
        (stage, os, is_docker, name, dep, cmds) = task
        if is_docker and os == OSX:
            return
        print("    - name:", name)
        print("      stage:", stage)
        print("      os:", os)
        if os == LINUX:
            print("      dist:", DIST_LINUX)
        else:
            print("      osx_image:", OSX_IMG)
        if is_docker:
            print_docker_before_install()
        print_dep(is_docker, dep, os)
        prefix = DOCKER_EXEC_PREFIX if is_docker else ""
        suffix = DOCKER_EXEC_SUFFIX if is_docker else ""
        print("      script:")
        for cmd in cmds:
            print("        -", prefix, cmd, suffix)
        if is_docker:
            print_docker_after_script()

    print_header()
    print("matrix:")
    print("  include:")
    for task in TASKS:
        print_task(task)


def print_docker_local_test():
    def header_task(title):
        left = '=' * 35
        right = left
        return (left + ' ' + title + ' ' + right)

    deps = []
    for task in TASKS:
        (_, os, _, _, local_deps, _) = task
        if os == LINUX:
            deps.extend(local_deps)

    print(" ".join(deps))

    for task in TASKS:
        (_, os, _, name, _, cmds) = task
        if os == LINUX:
            print("echo \"", header_task(name), "\"")
            for cmd in cmds:
                print(cmd)

HELPER_MSG = "build the config file or the docker script to test locally"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("mode", help=HELPER_MSG, type=str, nargs='?', const=1,
                        default="config", choices={"config", "test"})
    args = parser.parse_args()

    if args.mode == "config":
        print_travis_config()
    else:
        print_docker_local_test()


if __name__ == "__main__":
    main()
