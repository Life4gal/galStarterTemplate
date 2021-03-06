# A small project to learn CMAKE, can be used as a template for any CMAKE project

[![travis-ci](https://travis-ci.com/Life4gal/galStarterTemplate.svg?branch=master)](https://travis-ci.com/Life4gal/galStarterTemplate)
[![appveyor](https://ci.appveyor.com/api/projects/status/fay2x4i755455qyx?svg=true)](https://ci.appveyor.com/project/Life4gal/galstartertemplate)

### Inspired by [TheLartians's ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)

### Structure
| Directory          | Description                                    |
|:------------------ |:---------------------------------------------- |
| cmake              | CMAKE_MODULE_PATH                              |
| include            | the header file of your library                |
| sub-project-n      | all sub-project                                |

> dependencies:
>
> [TheLartians's CPM](https://github.com/TheLartians/CPM.cmake) include in top-level project StarterTemplate
>
> (not used now)[TheLartians's PackageProject](https://github.com/TheLartians/PackageProject.cmake) include in top-level project StarterTemplate
>
> optional:
>
> [fmtlib's fmt](https://github.com/fmtlib/fmt) include in top-level project StarterTemplate
>
> (not used now)[nlohmann's json](https://github.com/nlohmann/json) include in top-level project StarterTemplate
>
> [google's google-test](https://github.com/google/googletest) include in sub-project StarterTemplateTest
>
> (not used now)[jarro2783's cxxopts](https://github.com/jarro2783/cxxopts) include in sub-project StarterTemplateTest

# HOW TO USE IT

## start

1. see CMakeList.txt in top level of project, change the project name to your project name (current is
   galStarterTemplate)
2. change the dependencies to what you need
3. see CMakeList.txt in sub-project, change the sub-project name to your project name
4. change the dependencies to what you need
5. run it (main.cpp in sub-project)


## github action (overflows)
see ci.yml in the .github/workflow folder
the command
```bash
- name: Configure (${{ matrix.configuration }})
        run: cmake -Sexec -Bbuild -DCMAKE_BUILD_TYPE=${{ matrix.configuration }}

- name: Build with ${{ matrix.compiler }}
        run: cmake --build build
```
set the -Sexec to -S${WHERE_IS_YOUR_EXECUTABLE_PROJECT_FOLDER}

set the -Bbuild to -B${WHERE_YOU_WANT_IT_BUILD}


## CI
1. see .travis.yml in top level of project, the command
```bash
install:
  - cmake -Sexec -Bbuild -DCMAKE_BUILD_TYPE=Coverage -DCMAKE_CXX_COMPILER=$CXX_COMPILER
  - cd build
  - make
```
set the -Sexec to -S${WHERE_IS_YOUR_EXECUTABLE_PROJECT_FOLDER}

set the -Bbuild to -B${WHERE_YOU_WANT_IT_BUILD}

and the command
```bash
# Uploading report to CodeCov
  - bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
```
will upload the CodeCov report to codecov.io

DO NOT FORGET TO SET THE TOKEN (YOUR PROJECT(in github) -> Settings -> Environments -> New environment -> add your token(CODECOV_TOKEN='THIS-IS-YOUR-TOKEN-WHICH-ONLY-YOU-KNOW'))

2. see .appveyor.yml in the top level of project the command
```bash
before_build:
  - cmake -Sexec -Bbuild -A%PLATFORM% -DCMAKE_BUILD_TYPE=%configuration%

build:
  project: build/galStarterTemplateExec.sln
  parallel: true
  verbosity: minimal
```
set the -Sexec to -S${WHERE_IS_YOUR_EXECUTABLE_PROJECT_FOLDER}

set the -Bbuild to -B${WHERE_YOU_WANT_IT_BUILD}

cmake -A%PLATFORM% for Windows, it will generate a MSVC project and a .sln file for Visual Studio named ${YOUR_EXECUTABLE_PROJECT_NAME}.sln, so it you had changed the project name, 
DO NOT FORGET TO CHANGE IT!

the project build/galStarterTemplateExec.sln is ${WHERE_YOU_WANT_IT_BUILD}/${YOUR_EXECUTABLE_PROJECT_NAME}.sln
