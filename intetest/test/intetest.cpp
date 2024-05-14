#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <array>
#include <memory>

namespace fs = std::filesystem;

// 函数：执行外部程序并获取其输出
std::string executeCommand(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;

    // 使用popen打开一个进程，并读取其输出
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // 读取输出
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

int main() {
    std::string directory = "../../intetest"; // 目标目录
    std::string outputDir = "../../intetest/output"; // 输出目录

    // 创建输出目录
    fs::create_directory(outputDir);

    // 遍历目录中的所有文件
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".pas") {
            std::string filePath = entry.path().string();
            std::string fileName = entry.path().filename().string();
            
            // 构建外部程序命令
            std::string command = "../pascc -i " + filePath;

            try {
                // 执行命令并获取输出
                std::cout<<"InputFile: "<<fileName<<std::endl;

                std::string output = executeCommand(command);
                // 仅在输出不为空时写入新文件
                if (!output.empty()) {
                    // 构建输出文件路径
                    std::string outputFilePath = outputDir + "/" + fileName + ".out";

                    // 将输出写入新文件
                    std::ofstream outFile(outputFilePath);
                    if (outFile.is_open()) {
                        outFile << output;
                        outFile.close();
                        std::cout<< "****************************"<<std::endl;
                        std::cout << "Error Occured in Compiling"<< std::endl;
                        std::cout<< "****************************"<<std::endl;
                    } else {
                        std::cerr << "Unable to Open File: " << outputFilePath << std::endl;
                    }
                } else {
                    std::cout << "Compile Passed" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error occured in excution: " << e.what() << std::endl;
            }
        }
    }

    return 0;
}
