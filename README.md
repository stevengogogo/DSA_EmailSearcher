# Email Searcher

[![Ubuntu](https://github.com/stevengogogo/CProjectTemplate/actions/workflows/ci.yml/badge.svg)](https://github.com/stevengogogo/CProjectTemplate/actions/workflows/ci.yml)[![codecov](https://codecov.io/gh/stevengogogo/CProjectTemplate/branch/main/graph/badge.svg?token=5F6B6C9M1K)](https://codecov.io/gh/stevengogogo/CProjectTemplate)[![Doxygen Action](https://github.com/stevengogogo/CProjectTemplate/actions/workflows/doc.yml/badge.svg?branch=main)](https://github.com/stevengogogo/CProjectTemplate/actions/workflows/doc.yml)[![Dev](https://img.shields.io/badge/docs-dev-blue.svg)](https://stevengogogo.github.io/CProjectTemplate/)

An email searcher toolbox implemented in c (See [problem statement](https://github.com/stevengogogo/DSA_EmailSearcher/discussions/13))


Final Report
------------

[![](https://img.shields.io/badge/Overleaf%20-Open%20as%20Template-46a247?logo=overleaf&style=flat-square)](https://www.overleaf.com/project/60a600583dd777ff5c8c78fa)


Usage
------

- Build main
    - `make build`
- Unit testing
    - `make test`
- Scoring
    - `make score`
- Test for memory leak
    - `make leak`


Deployment
----------
- Create new [release](https://github.com/stevengogogo/DSA_EmailSearcher/releases)
- Download the `main.c` for uploading.


How to use this project?
-------------------------
- See [CProjectTemplate](https://github.com/stevengogogo/CProjectTemplate)


Environment
-----------
- Linux
- Setup
    ```
    sudo apt-get update -y
    sudo apt-get install -y build-essential
    sudo apt-get install -y valgrind
    ```
