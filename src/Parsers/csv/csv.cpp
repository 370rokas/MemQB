#include "csv.hpp"

using namespace MemQB::IO;

/*
 * @brief: Constructor for CSVReader Class
 */
CSVReader::CSVReader(APIType API) : API(API) {}

/*
 * @brief: Open the file
 * @param filepath: The file to open
 */
void CSVReader::openFile(std::filesystem::path& filepath) {
    this->filePointer = std::ifstream(filepath);

    if (!this->filePointer.is_open()) {
        throw std::runtime_error("Could not open the specified file");
    }

    if (!this->filePointer.is_open()) {
        throw std::runtime_error("No files have been opened");
    }

    std::string line{};
    std::getline(this->filePointer, line);
    std::stringstream ss(line);

    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, ',');
        std::vector<std::string>* vect = new std::vector<std::string>;
        this->csvFile.insert({substr, vect});
    }
}

/*
 * @brief: Read the next line of the file that was opened earlier
 * @param vec: The vector to which the next line is to be pushed
 */
void CSVReader::readLine() {
    if (this->API == APIType::MMAP) {
        throw std::runtime_error(
            "This function can't be used with the MMAP API.");
        return;
    }

    if (!this->filePointer.is_open()) {
        throw std::runtime_error("No files have been opened");
    }

    std::string line{};
    std::getline(this->filePointer, line);

    auto headers = this->getCSVHeader();

    std::stringstream ss(line);
    size_t valIdx = 0;
    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, ',');

        auto currentColumn = csvFile.at(headers->at(valIdx));
        currentColumn->push_back(substr);

        valIdx++;
    }

    this->lineNumber++;
}

void CSVReader::loadFileIntoMemory(std::filesystem::path& fpath) {
    if (this->API == APIType::STREAM) {
        throw std::runtime_error(
            "This function can't be used with the STREAM API.");
        return;
    }

    // create hashmap of vectors
}

/*
 * @brief: Read the next line of the file that was opened earlier
 * @param vec: The vector to which the next line is to be pushed
 */
std::vector<std::string>* CSVReader::getCSVHeader() {

    if (this->csvHeader.empty()) {
        this->csvHeader.reserve(this->csvFile.size());

        for (auto kv : this->csvFile) {
            this->csvHeader.push_back(kv.first);
        }
    }

    return &this->csvHeader;
}

/*
 * @brief: destructor for CSVReader Class
 */
CSVReader::~CSVReader() {
    if (this->filePointer.is_open()) {
        this->filePointer.close();
    }

    for (auto kv : this->csvFile) {
        delete kv.second;
    }
}