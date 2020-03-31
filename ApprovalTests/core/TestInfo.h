#ifndef APPROVALTESTS_CPP_TESTINFO_H
#define APPROVALTESTS_CPP_TESTINFO_H

#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/namers/HelpMessages.h"
#include <vector>

namespace ApprovalTests
{
    class TestInfo
    {
    public:
        std::vector<std::string> sections;

        const std::string& getFileName() const
        {
            checkBuildConfiguration(fileName);
            return fileName;
        }

        void setFileName(const std::string& file)
        {
            fileName = SystemUtils::checkFilenameCase(file);
        }

        static TestInfo& getCurrent()
        {
            auto currentInfoPtr = getCurrentRef();
            if (!currentInfoPtr)
            {
                throw std::runtime_error(getMisconfiguredMainHelp());
            }

            return *currentInfoPtr;
        }

        static void setCurrent(TestInfo* testInfo)
        {
            getCurrentRef() = testInfo;
        }

    private:
        std::string fileName;

        static void checkBuildConfiguration(const std::string& fileName)
        {
            if (!FileUtils::fileExists(fileName))
            {
                throw std::runtime_error(getMisconfiguredBuildHelp(fileName));
            }
        }

        static std::string getMisconfiguredBuildHelp(const std::string& fileName)
        {
            return "\n\n" + HelpMessages::getMisconfiguredBuildHelp(fileName) + "\n\n";
        }

        static std::string getMisconfiguredMainHelp()
        {
            return "\n\n" + HelpMessages::getMisconfiguredMainHelp() + "\n\n";
        }

        static TestInfo*& getCurrentRef()
        {
            static TestInfo* currentTestInfo = nullptr;
            return currentTestInfo;
        }
    };
}

#endif
