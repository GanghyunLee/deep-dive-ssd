#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <windows.h>

#include "ILogger.h"

using namespace std;

const string LOG_FILE = "latest.log";
const size_t MAX_LOG_SIZE = 10 * 1024; // 10KB

class DualBuffer : public streambuf {
public:
    void addStream(ostream* os) {
        streams.push_back(os);
    }

protected:
    int overflow(int ch) override {
        for (auto& stream : streams) {
            stream->put(ch);
        }
        return ch;
    }

private:
    vector<ostream*> streams;
};

class DualStream : public ostream {
public:
    // DualStream은 복사 불가능
    DualStream(ostream& s1, ostream& s2) : ostream(&buffer), out1(s1), out2(s2) {
        rdbuf(&buffer);
        buffer.addStream(&out1);
        buffer.addStream(&out2);
    }

    // 복사 방지
    DualStream(const DualStream&) = delete;
    DualStream& operator=(const DualStream&) = delete;

    void flush() const
    {
	    out1.flush();
	    out2.flush();
    }

    ostream& GetOut1Stream() { return out1; }

private:
    DualBuffer buffer;
    ostream& out1;
    ostream& out2;
};

class DualLogger : public ILogger {
public:
    DualLogger(const string& fileName = LOG_FILE) : fileStream(fileName, ios::app), dualStream(cout, fileStream) {}

    ostream& getMainOstream() override {
        rotateIfNeeded();
        return dualStream.GetOut1Stream();
    }

    void print(const std::string& className, const std::string& functionName,
        const std::string& message, bool printLogInfo = DEFAULT_PRINT_LOG_INFO_VALUE) override {
        rotateIfNeeded();

        // 여기서는 콘솔에서는 로그 정보를 출력하지 않도록 한다.
        if (printLogInfo)
        {
            string logLine = className + "." + functionName;
            fileStream << getTimestamp() << " " << left << setw(40) << logLine << "    :  ";
            fileStream.flush();
        }

        dualStream << message;
        dualStream.flush();
    }

    void printLine() override
    {
        dualStream << std::endl;
    }

private:
    ofstream fileStream;
    DualStream dualStream;

    string getTimestamp() {
        time_t now = time(nullptr);
        tm local;
        localtime_s(&local, &now);
        stringstream ss;
        ss << '['
            << setfill('0') << setw(2) << (local.tm_year % 100) << '.'
            << setw(2) << (local.tm_mon + 1) << '.'
            << setw(2) << local.tm_mday << ' '
            << setw(2) << local.tm_hour << ':'
            << setw(2) << local.tm_min << ']';
        return ss.str();
    }

    void rotateIfNeeded() {
        fileStream.flush(); // 크기 확인 전 버퍼 플러시
        WIN32_FILE_ATTRIBUTE_DATA fileInfo;
        wstring wLogFile = std::wstring(LOG_FILE.begin(), LOG_FILE.end()); // std::string을 std::wstring으로 변환

        if (GetFileAttributesExW(wLogFile.c_str(), GetFileExInfoStandard, &fileInfo) != 0) {
            unsigned long long fileSize = ((static_cast<unsigned long long>(fileInfo.nFileSizeHigh) << 32)) + fileInfo.nFileSizeLow;
            if (fileSize > MAX_LOG_SIZE) {
                fileStream.close();
                string rotatedName = getRotatedFileName();
                wstring wRotatedName = std::wstring(rotatedName.begin(), rotatedName.end()); // .log 파일명을 wstring으로 변환
                if (MoveFileW(wLogFile.c_str(), wRotatedName.c_str()) == 0) { // MoveFileW 사용
                    cerr << "!Failed to rename the file: " << rotatedName << endl;
                }
                fileStream.open(LOG_FILE, ios::app);
            }
        }
        compressOldLogIfNeeded();
    }

    string getRotatedFileName() {
        time_t now = time(nullptr);
        tm local;
        localtime_s(&local, &now);
        stringstream ss;
        ss << "until_"
            << setfill('0') << setw(2) << (local.tm_year % 100)
            << setw(2) << (local.tm_mon + 1)
            << setw(2) << local.tm_mday << '_'
            << setw(2) << local.tm_hour
            << setw(2) << local.tm_min
            << setw(2) << local.tm_sec << ".log";
        return ss.str();
    }

    void compressOldLogIfNeeded() {
        // 디렉터리 내에서 .log 파일들을 찾기
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(L"until_*.log", &findFileData); // L"" 사용하여 wchar_t 문자열

        if (hFind != INVALID_HANDLE_VALUE) {
            vector<wstring> logFiles; // vector를 wstring으로 사용
            do {
                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    logFiles.push_back(findFileData.cFileName); // wstring을 vector에 추가
                }
            } while (FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);

            for (const wstring& file : logFiles) {
                // .log 확장자만을 .zip으로 변경
                wstring zipFile = file;

                // 파일 확장자가 .log라면, .zip으로 변경
                if (zipFile.size() >= 4 && zipFile.substr(zipFile.size() - 4) == L".log") {
                    zipFile.replace(zipFile.size() - 4, 4, L".zip");
                }

                // 파일 이름을 변경
                if (MoveFileW(file.c_str(), zipFile.c_str()) == 0) {
                    wcerr << L"Failed to rename the file: " << file << L" -> " << zipFile << endl;
                }
                else {
                    wcout << L"File renamed successfully: " << file << L" -> " << zipFile << endl;
                }
            }
        }
    }

    int compareFileCreationTime(const wstring& file1, const wstring& file2) {
        // 두 파일의 생성 시간을 비교하는 함수
        FILETIME fileTime1, fileTime2;
        HANDLE hFile1 = CreateFileW(file1.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
        HANDLE hFile2 = CreateFileW(file2.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hFile1 == INVALID_HANDLE_VALUE || hFile2 == INVALID_HANDLE_VALUE) {
            return 0;
        }
        GetFileTime(hFile1, &fileTime1, NULL, NULL);
        GetFileTime(hFile2, &fileTime2, NULL, NULL);
        CloseHandle(hFile1);
        CloseHandle(hFile2);

        return CompareFileTime(&fileTime1, &fileTime2);
    }
};
