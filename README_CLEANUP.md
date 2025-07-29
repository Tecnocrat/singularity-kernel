# Codebase Cleanup Log

## Removed from root (now only in src/):
- coherence.h
- phantom.h
- seed.h
- ai_interface/
- core/

## Kept in root:
- main.cpp
- CMakeLists.txt
- README.md
- singularity.md

## All implementation and headers are now in src/ (with subfolders as needed).

## Next steps:
- Update all includes in main.cpp to use src/ paths.
- Ensure CMakeLists.txt in root and src/ are aligned.
