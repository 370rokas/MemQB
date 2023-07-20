#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

class CSVReader {
public:
    /*
     * @brief: Constructor for CSVReader Class
     */
    CSVReader() = default;

    /*
     * @brief: destructor for CSVReader Class
     */
    ~CSVReader();

    /*
     * @brief: Open the file
     * @param filepath: The file to open
     */
    void openFile(std::filesystem::path& filepath);

    /*
     * @brief: Read the next line of the file that was opened earlier
     * @param vec: The vector to which the next line is to be pushed
     */
    void readLine(std::vector<std::string>& vec);

private:
    std::ifstream filePointer;
};

#endif // CSVREADER_HPP