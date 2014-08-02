#include "CCFileUtilsQt.h"
#include "platform/CCCommon.h"

// Qt
#include <QObject>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>

using namespace std;

NS_CC_BEGIN

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == NULL) {
        s_sharedFileUtils = new CCFileUtilsQt();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsQt::CCFileUtilsQt()
{
}

bool CCFileUtilsQt::init()
{
    QDir _execDir(qApp->applicationDirPath());
    QDir _resourceDir(_execDir);
    _resourceDir.cdUp();
    _resourceDir.cd("Resources");
    QString _path = _resourceDir.absolutePath();
    if (_path.endsWith("/", Qt::CaseInsensitive) == false) {
        _path.append("/");
    }
    _defaultResRootPath = _path.toStdString();

//    CCLOG("%s", _defaultResRootPath.c_str());

    return FileUtils::init();
}

bool CCFileUtilsQt::isFileExistInternal(const std::string& strFilePath) const
{
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, _defaultResRootPath);
    }
    QFileInfo fileInfo(strPath.c_str());
    return fileInfo.exists();
}

bool CCFileUtilsQt::isAbsolutePath(const std::string& strPath) const
{
    QFileInfo fileInfo(strPath.c_str());
    return fileInfo.isAbsolute();
}

std::string
CCFileUtilsQt::getWritablePath() const
{
    std::string ret(qApp->applicationDirPath().toLocal8Bit().constData());
    return ret;
}

NS_CC_END
