#pragma once

#include <string>

namespace Phoenix {

class Tools {
public:
    static std::string find_build_directory(const std::string& start_path);

    static std::string get_ctest_project_path(const std::string& folder_type);

public:
    static std::string path_project;
    static std::string path_build;
};

} // namespace Phoenix