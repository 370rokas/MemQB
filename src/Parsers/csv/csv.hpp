#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace MemQB::IO {

enum class APIType { MMAP, STREAM };

class CSVReader {
public:
    /*
     * @brief: Constructor for CSVReader Class
     */
    CSVReader(APIType _API);

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
     */
    void readLine();

    /*
     * @brief: Read the next line of the file that was opened earlier
     * @param vec: The vector to which the next line is to be pushed
     */
    std::vector<std::string>* getCSVHeader();

    void loadFileIntoMemory();

    std::map<std::string, std::vector<std::string>*> csvFile;

    std::vector<std::string> getRow(size_t row);
    size_t getNumRows();

    std::vector<std::string>
    string_to_vector(std::string& s, const char delimiter, const char escape);

private:
    APIType API;

    std::ifstream filePointer;
    std::vector<std::string> csvHeader;

    /*
    abc, xyz, dingding
    1,   2  , 3
    1,   2  , 3
    1,   2  , 3
    1,   2  , 3
    */
};

} // namespace MemQB::IO

#endif // CSVREADER_HPP