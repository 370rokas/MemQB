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

    std::vector<std::string> line_vec = this->string_to_vector(line, ',', '\\');

    for (auto substr : line_vec) {
        std::vector<std::string>* vect = new std::vector<std::string>;
        this->csvFile.insert({substr, vect});
    }
}

std::vector<std::string> CSVReader::string_to_vector(std::string& s,
                                                     const char delimiter,
                                                     const char escape) {
    size_t prev(0), pos(0), from(0);
    std::vector<std::string> v;
    while ((pos = s.find(delimiter, from)) != s.npos) {
        if (pos == 0 || s[pos - 1] != escape) {
            s[pos] = 0;
            v.push_back(&s[prev]);
            prev = pos + 1;
        }
        from = pos + 1;
    }
    v.push_back(&s[prev]);
    return v;
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

    std::vector<std::string> line_vec = this->string_to_vector(line, ',', '\\');

    // For each header
    auto colIdx = 0;
    for (auto kv : csvFile) {
        kv.second->push_back(line_vec[colIdx++]);
    }
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