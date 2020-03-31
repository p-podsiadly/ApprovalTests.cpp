#ifndef APPROVALTESTS_CPP_APPROVALTESTNAMER_H
#define APPROVALTESTS_CPP_APPROVALTESTNAMER_H

#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/core/TestInfo.h"
#include <sstream>
#include <vector>
#include <stdexcept>
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/namers/HelpMessages.h"

namespace ApprovalTests
{
    class TestConfiguration
    {
    public:
        std::string subdirectory;
    };

    class ApprovalTestNamer : public ApprovalNamer
    {
    private:
    public:
        ApprovalTestNamer() = default;

        std::string getTestName() const
        {
            std::stringstream ext;
            const auto& test = TestInfo::getCurrent();
            for (size_t i = 0; i < test.sections.size(); i++)
            {
                if (0 < i)
                {
                    ext << ".";
                }
                ext << test.sections[i];
            }

            return convertToFileName(ext.str());
        }

        static bool isForbidden(char c)
        {
            static std::string forbiddenChars("\\/:?\"<>|' ");
            return std::string::npos != forbiddenChars.find(c);
        }

        static std::string convertToFileName(const std::string& fileName)
        {
            std::stringstream result;
            for (auto ch : fileName)
            {
                if (!isForbidden(ch))
                {
                    result << ch;
                }
                else
                {
                    result << "_";
                }
            }
            return result.str();
        }

        // Deprecated - please use getSourceFileName
        std::string getFileName() const
        {
            return getSourceFileName();
        }

        std::string getSourceFileName() const
        {
            auto file = TestInfo::getCurrent().getFileName();
            auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
            auto end = file.rfind('.');
            auto fileName = file.substr(start, end - start);
            return convertToFileName(fileName);
        }

        std::string getDirectory() const
        {
            auto file = TestInfo::getCurrent().getFileName();
            auto end = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
            auto directory = file.substr(0, end);
            if (!testConfiguration().subdirectory.empty())
            {
                directory += testConfiguration().subdirectory +
                             SystemUtils::getDirectorySeparator();
                SystemUtils::ensureDirectoryExists(directory);
            }
            return directory;
        }

        static TestConfiguration& testConfiguration()
        {
            static TestConfiguration configuration;
            return configuration;
        }

        virtual std::string getApprovedFile(std::string extensionWithDot) const override
        {

            return getFullFileName(".approved", extensionWithDot);
        }

        virtual std::string getReceivedFile(std::string extensionWithDot) const override
        {

            return getFullFileName(".received", extensionWithDot);
        }

        std::string getOutputFileBaseName() const
        {
            return getSourceFileName() + "." + getTestName();
        }

        std::string getFullFileName(const std::string& approved,
                                    const std::string& extensionWithDot) const
        {
            std::stringstream ext;
            ext << getDirectory() << getOutputFileBaseName() << approved
                << extensionWithDot;
            return ext.str();
        }
    };
}

#endif
