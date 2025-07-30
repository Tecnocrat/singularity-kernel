// Path: singularity-kernel/md/CMake_Intellisense_Checklist.md
# CMake/Intellisense Sync Checklist for VSCode

1. After editing CMakeLists.txt, always run:
   - "CMake: Configure" (Command Palette)
   - "CMake: Build" (Command Palette)

2. If you add/remove source or header files:
   - Update CMakeLists.txt accordingly.
   - Re-run "CMake: Configure".

3. If you add/remove dependencies (e.g., OpenCV, nlohmann_json):
   - Ensure find_package() and target_link_libraries() are correct in CMakeLists.txt.
   - Re-run "CMake: Configure".

4. If Intellisense is out of sync or shows errors:
   - Run "C/C++: Reset IntelliSense Database" (Command Palette).
   - Reload the VSCode window.

5. If you use vcpkg or other toolchains:
   - Ensure .vscode/settings.json has the correct CMAKE_TOOLCHAIN_FILE.
   - Re-run "CMake: Configure" after any toolchain or dependency change.

6. For fallback navigation if CMake is incomplete:
   - Maintain a minimal includePath in .vscode/c_cpp_properties.json as a backup.

7. If you move or rename folders/files:
   - Update both CMakeLists.txt and c_cpp_properties.json (if using manual includePath).

8. For persistent issues:
   - Delete the build/ directory and reconfigure from scratch.
   - Check CMake output for missing includes or libraries.

---

This checklist ensures your CMake, build, and Intellisense environments stay in sync for reliable development and code navigation.
