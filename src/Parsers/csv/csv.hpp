#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <filesystem>
#include <fstream>
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
     * @param vec: The vector to which the next line is to be pushed
     */
    void readLine();

    /*
     * @brief: Read the next line of the file that was opened earlier
     * @param vec: The vector to which the next line is to be pushed
     */
    std::vector<std::string>* getCSVHeader();

    void loadFileIntoMemory(std::filesystem::path& fpath);

    std::map<std::string, std::vector<std::string>*> csvFile;

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

    size_t lineNumber = 0;
};

} // namespace MemQB::IO

#endif // CSVREADER_HPP