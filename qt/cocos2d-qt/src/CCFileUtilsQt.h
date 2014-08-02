#ifndef __CC_FILEUTILSQT_H__
#define __CC_FILEUTILSQT_H__

#include "platform/CCFileUtils.h"
#include "cocos2d.h"
#include <string>
#include <vector>

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class CC_DLL CCFileUtilsQt : public FileUtils
{
    friend class FileUtils;
    CCFileUtilsQt();

public:
    /* override funtions */
    bool init();
    virtual std::string getWritablePath() const;
    virtual bool isFileExistInternal(const std::string& strFilePath) const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILSQT_H__

