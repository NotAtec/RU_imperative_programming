#pragma once

#include <string>
#include <vector>

class World;

/**
 * @brief Class to abstract the saving to and loading from *.scenario file formats.
 * @note This class is not thread-safe. Using it from multiple threads may overwrite the last error message.
 * 
 */
class Scenario {
public:
    /**
     * @brief Attempts to save the world to the given file path.
     * 
     * @param path The path of the destination file.
     * @param world The world to save.
     * @return true if the world was saved successfully, false otherwise.
     */
    static bool SaveTo(std::string path, const World& world);

    /**
     * @brief Attempts to save the world to the given output stream.
     * 
     * @param os The output stream.
     * @param world The world to save.
     * @return true if the world was saved successfully, false otherwise.
     */
    static bool SaveTo(std::ostream& os, const World& world);

    /**
     * @brief Attempts to load a world from the given file path.
     * 
     * @param path The path of the source file.
     * @param world The world to load into.
     * @return true if the world was loaded successfully, false otherwise.
     */
    static bool LoadFrom(std::string path, World& world);

    /**
     * @brief Attempts to load a world from the given input stream.
     * 
     * @param is The input stream.
     * @param world The world to load into.
     * @return true if the world was loaded successfully, false otherwise.
     */
    static bool LoadFrom(std::istream& is, World& world);

    /**
     * @brief Returns the last error encountered while trying to save or load a scenario.
     * 
     * @return The last encountered error message.
     */
    static const std::string& GetLastError();

private:
    static bool LoadAndValidate(std::istream& is, std::vector<std::string>& content);
    static void CreateFromValidatedContent(const std::vector<std::string>& content, World& world);
};

std::istream& operator>>(std::istream& is, World& world);
std::ostream& operator<<(std::ostream& os, const World& world);