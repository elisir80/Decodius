#include "ConfigPaths.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QSet>
#include <QStandardPaths>

static void addConfigPath(QStringList& paths, QSet<QString>& seen, const QString& path)
{
    if (path.trimmed().isEmpty()) return;
    const QString clean = QDir::cleanPath(QFileInfo(path).absoluteFilePath());
    if (seen.contains(clean)) return;
    seen.insert(clean);
    paths.append(clean);
}

QStringList decodiusConfigCandidatePaths(const QString& fileName)
{
    QStringList paths;
    QSet<QString> seen;

    auto addDir = [&](const QString& dir) {
        if (!dir.trimmed().isEmpty())
            addConfigPath(paths, seen, QDir(dir).filePath(fileName));
    };

    const QString appConfig = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    addDir(appConfig);

    const QString appDir = QCoreApplication::applicationDirPath();
    addDir(appDir);
    addDir(QDir(appDir).filePath(QStringLiteral("../Resources")));
    addDir(QDir(appDir).filePath(QStringLiteral("../../..")));
    addDir(QDir(appDir).filePath(QStringLiteral("../../../..")));

    addDir(QDir::currentPath());

    const QString genericConfig = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    addDir(QDir(genericConfig).filePath(QStringLiteral("Decodius")));

    return paths;
}

QString decodiusConfigFilePath(const QString& fileName)
{
    const QStringList paths = decodiusConfigCandidatePaths(fileName);
    for (const QString& path : paths) {
        if (QFileInfo::exists(path))
            return path;
    }
    return paths.isEmpty() ? fileName : paths.first();
}

QString decodiusWritableConfigFilePath(const QString& fileName)
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (!dir.isEmpty()) {
        QDir().mkpath(dir);
        return QDir(dir).filePath(fileName);
    }
    return decodiusConfigFilePath(fileName);
}
