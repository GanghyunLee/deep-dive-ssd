#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <windows.h>

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
    DualStream(ostream& s1, ostream& s2) : ostream(nullptr), out1(s1), out2(s2) {
        rdbuf(&buffer);
        buffer.addStream(&out1);
        buffer.addStream(&out2);
    }

    // 복사 방지
    DualStream(const DualStream&) = delete;
    DualStream& operator=(const DualStream&) = delete;

private:
    DualBuffer buffer;
    ostream& out1;
    ostream& out2;
};

class DualLogger {
public:
    DualLogger(const string& fileName) : fileStream(fileName, ios::app), dualStream(cout, fileStream) {}

    // ostream을 반환할 때는 참조로 반환합니다.
    ostream& getOstream() {
        rotateIfNeeded();
        return dualStream;
    }

    void print(const string& className, const string& functionName, const string& message) {
        rotateIfNeeded();
        // string logLine = getTimestamp() + " " + className + "." + functionName + "    : " + message;
        string logLine = className + "." + functionName;
        fileStream << getTimestamp() << " " << left << setw(40) << logLine << "    :  " << message << endl;
        // cout << logLine << endl;
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
            DWORD fileSize = (fileInfo.nFileSizeHigh << 32) + fileInfo.nFileSizeLow;
            if (fileSize > MAX_LOG_SIZE) {
                fileStream.close();
                string rotatedName = getRotatedFileName();
                wstring wRotatedName = std::wstring(rotatedName.begin(), rotatedName.end()); // .log 파일명을 wstring으로 변환
                if (MoveFileW(wLogFile.c_str(), wRotatedName.c_str()) == 0) { // MoveFileW 사용
                    cerr << "파일 이름 변경 실패: " << rotatedName << endl;
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

            if (logFiles.size() >= 2) {
                // 가장 오래된 파일 찾기
                wstring oldestFile = logFiles[0];
                for (const wstring& file : logFiles) {
                    if (compareFileCreationTime(file, oldestFile) < 0) {
                        oldestFile = file;
                    }
                }
                string zipFile = string(oldestFile.begin(), oldestFile.end()) + ".zip"; // wstring을 string으로 변환
                if (MoveFileW(oldestFile.c_str(), wstring(zipFile.begin(), zipFile.end()).c_str()) == 0) { // MoveFileW 사용
                    cerr << "파일 이름 변경 실패: " << zipFile << endl;
                }
                else {
                    cout << "파일 이름 변경 성공: " << string(oldestFile.begin(), oldestFile.end()) << " -> " << zipFile << endl;
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
