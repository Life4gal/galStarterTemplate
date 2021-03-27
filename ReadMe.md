# A small project to learn CMAKE, can be used as a template for any CMAKE project

### Inspired by [TheLartians's ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)

### Structure
| Directory          | Description                                    |
|:------------------ |:---------------------------------------------- |
| cmake              | include some cmake scripts                     |
| include            | the header file of your library                |
| src                | the source file of your library                |
| exec               | some test file of your library                 |

### Why is the project organized like this?
If a project is not executable (or it cannot organize the entire project, 
it is only a small part of the project), so for developers, 
the cost of debugging is unpredictable.

They may wish to have a sub-project that is not part of the current project but can be used for testing, 
just like the structure of the current library.

This should be of great help to the development of some interface libraries or module libraries.


> dependencies:
> 
> [TheLartians's CPM](https://github.com/TheLartians/CPM.cmake) include in top-level project StarterTemplate
> 
> [TheLartians's PackageProject](https://github.com/TheLartians/PackageProject.cmake) include in top-level project StarterTemplate
> 
> optional:
> 
> [fmtlib's fmt](https://github.com/fmtlib/fmt) include in top-level project StarterTemplate
> 
> [nlohmann's json](https://github.com/nlohmann/json) include in top-level project StarterTemplate
> 
> [google's google-test](https://github.com/google/googletest) include in sub-project StarterTemplateTest
> 
> [jarro2783's cxxopts](https://github.com/jarro2783/cxxopts) include in sub-project StarterTemplateTest
