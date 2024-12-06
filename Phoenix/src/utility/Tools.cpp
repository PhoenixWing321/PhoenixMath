#include <filesystem>
#include <iostream>
#include <sstream>

#include "utility/Tools.h"

namespace Phoenix {
// Initialize static member variables
std::string Tools::path_project = Tools::get_ctest_project_path("project"); // Project path
std::string Tools::path_build   = Tools::path_project + "/build";           // Build path

namespace fs = std::filesystem;

//------------------------------------------
std::string Tools::find_build_directory(const std::string& startPath) {

    fs::path currentPath(startPath);
    int      counter = 0;
    // Traverse parent directories until the build directory is found or the root directory is
    // reached
    while (currentPath.has_parent_path()) {
        counter++;

        std::string pathStr = currentPath.string();
        if (pathStr.length() < 5) break; // Handle special case for root path

        currentPath = currentPath.parent_path();
        if ((currentPath.filename() == "build" || currentPath.filename() == "Build")) {
            return currentPath.string();
        }

        if (counter > 100) break; // Prevent infinite loop
    }

    return "";
}
//------------------------------------------
std::string Tools::get_ctest_project_path(const std::string& folder_type) {
    // Such as "simulate", "modules"

    // Get current working directory
    auto current_path = fs::current_path();

    // Find build directory
    auto build = Tools::find_build_directory(current_path.string());
    if (build.length() < 5) build = current_path.string();

    // Build directory
    if (folder_type == "build") {
        return build;
    }

    // Project directory
    fs::path project_path_(build);
    if (project_path_.has_parent_path()) project_path_ = project_path_.parent_path();

    if (folder_type == "project") {
        return project_path_.string();
    }

    return project_path_.string();
}

} // namespace Phoenix