#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

class TranscriptStealer {
public:
    std::string getTranscript(const std::string& videoUrl) {
        // Use youtube-dl to download subtitles in VTT format
        //std::string url = "https://www.youtube.com/watch?v=7E-cwdnsiow";
        //std::string url = "https://www.youtube.com/watch?v=X66eSpblAN4&ab_channel=TopGear";
        std::string command = "youtube-dl --skip-download --write-sub --sub-lang en --output \"%(title)s.%(ext)s\" " + videoUrl;
        std::system(command.c_str());
        std::cout << command.c_str() << std::endl;
        // Dynamically look for the VTT file in the current directory
        std::string vttFileName;
        for (const auto& entry : std::__fs::filesystem::directory_iterator(".")) {
            if (entry.is_regular_file() && entry.path().extension() == ".vtt") {
                vttFileName = entry.path().filename().string();
                break;
            }
        }

        if (vttFileName.empty()) {
            std::cerr << "Error: VTT file not found." << std::endl;
            return "";
        }

        // Read and parse the VTT file
        std::ifstream vttFile(vttFileName);
        if (!vttFile.is_open()) {
            std::cerr << "Error opening VTT file." << std::endl;
            return "";
        }

        std::stringstream transcript;
        bool inTranscript = false;
        std::string line;

        while (std::getline(vttFile, line)) {
            if (line.empty()) {
                inTranscript = false;
            } else if (line.find("-->") != std::string::npos) {
                inTranscript = true;
            } else if (inTranscript) {
                transcript << line << ' ';
            }
        }
        std::cout << vttFileName << std::endl;
        vttFile.close();

        // Delete the VTT file
        deleteFile(vttFileName);

        return transcript.str();
    }

private:
    void deleteFile(const std::string& fileName) {
        if (std::__fs::filesystem::exists(fileName)) {
            std::__fs::filesystem::remove(fileName);
            std::cout << "Deleted file: " << fileName << std::endl;
        }
    }
};








//#ifndef HELLOSFML_TRANSCRIPTSTEALER_H
//#define HELLOSFML_TRANSCRIPTSTEALER_H
//
//#include <iostream>
//#include <cstdio>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <sstream>
//#include <fstream>
//#include <filesystem>
//
//class TranscriptStealer {
//public:
//    std::string getTranscript(const std::string& videoUrl) {
//        // Use youtube-dl to download subtitles in VTT format
//        std::string command = "youtube-dl --skip-download --write-sub --sub-lang en --output \"%(title)s.%(ext)s\" " + videoUrl;
//        std::system(command.c_str());
//
//        // Dynamically look for the VTT file in the current directory
//        std::string vttFileName;
//        for (const auto& entry : std::filesystem::directory_iterator(".")) {
//            if (entry.is_regular_file() && entry.path().extension() == ".vtt") {
//                vttFileName = entry.path().filename().string();
//                break;
//            }
//        }
//
//        if (vttFileName.empty()) {
//            std::cerr << "Error: VTT file not found." << std::endl;
//            return "";
//        }
//
//        // Read and parse the VTT file
//        std::ifstream vttFile(vttFileName);
//        if (!vttFile.is_open()) {
//            std::cerr << "Error opening VTT file." << std::endl;
//            return "";
//        }
//
//        std::stringstream transcript;
//        bool inTranscript = false;
//        std::string line;
//
//        while (std::getline(vttFile, line)) {
//            if (line.empty()) {
//                inTranscript = false;
//            } else if (line.find("-->") != std::string::npos) {
//                inTranscript = true;
//            } else if (inTranscript) {
//                transcript << line << ' ';
//            }
//        }
//
//        vttFile.close();
//
//        // Delete the VTT file
//        deleteFile(vttFileName);
//
//        return transcript.str();
//    }
//
//private:
//    void deleteFile(const std::string& fileName) {
//        if (std::filesystem::exists(fileName)) {
//            std::filesystem::remove(fileName);
//            std::cout << "Deleted file: " << fileName << std::endl;
//        }
//    }
//};
////    std::string getTranscript(const std::string& videoUrl) {
////        // Use youtube-dl to download subtitles in VTT format
////        std::string ytUrl = "https://www.youtube.com/watch?v=7E-cwdnsiow";
////        std::string command = "youtube-dl --skip-download --write-sub --sub-lang en --output \"%(title)s.%(ext)s\" " + ytUrl;
////        std::system(command.c_str());
////
////        // Read and parse the VTT file
////        std::ifstream vttFile("A.P.J.Abdul kalam Inspirational lesson for lifetime- How to manage failure and success.en.vtt");
////        if (!vttFile.is_open()) {
////            std::cerr << "Error opening VTT file." << std::endl;
////            return "";
////        }
////
////        std::stringstream transcript;
////        bool inTranscript = false;
////        std::string line;
////
////        while (std::getline(vttFile, line)) {
////            if (line.empty()) {
////                inTranscript = false;
////            } else if (line.find("-->") != std::string::npos) {
////                inTranscript = true;
////            } else if (inTranscript) {
////                transcript << line << ' ';
////            }
////        }
////
////        vttFile.close();
////
////        return transcript.str();
////    }
//};
//
//
//
//#endif //HELLOSFML_TRANSCRIPTSTEALER_H
