#ifndef PRISM_SYSTEM_TEMP_DIR
#define PRISM_SYSTEM_TEMP_DIR

#include <prism/global>
#include <string>
#include <fstream>
#include <cstdio>
#if defined _Win32
#       include <windows.h>
#elif defined __APPLE__
#       include <stdlib.h> // for realpath()
#endif

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class SystemTempDir
{
public:
        static const std::string path()
        {
                #if defined _WIN32
                        return std::string(getenv("TMP"));
                #elif defined __APPLE__
                        char buff[PATH_MAX];
                        realpath(getenv("TMPDIR"), buff);
                        return std::string(buff);
                #endif
        }

        static const bool newFileWithContent(const std::string& filename, const std::string& content)
        {
                bool success{false};
                const std::string pathFilename = SystemTempDir::path() + "/" + filename;

                std::fstream fs(pathFilename, std::fstream::out);
                if (fs.is_open())
                {
                        fs << content;
                        success = true;
                }
                else success = false;

                fs.close();
                return success;
        }

        static void deleteFile(const std::string& filename)
        {
                #if defined _Win32
                        const std::string sep = "\\"
                #elif defined __APPLE__
                        const std::string sep = "/";
                #endif
                const std::string pathFilename = SystemTempDir::path() + sep + filename;
                std::remove(pathFilename.c_str());
        }
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif
