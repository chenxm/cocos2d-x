#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__
#include <string>
#include <vector>
#include "cocos2d.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class CC_DLL FileUtilsImpl : public FileUtils
{
    friend class FileUtils;
    FileUtilsImpl();

public:
    /* override funtions */
    virtual bool init();
    virtual std::string getWritablePath() const;
    virtual bool isFileExistInternal(const std::string& strFilePath) const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __FILEUTILS_H__

