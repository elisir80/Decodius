#pragma once

#include <QString>
#include <QStringList>

QStringList decodiusConfigCandidatePaths(const QString& fileName);
QString decodiusConfigFilePath(const QString& fileName);
QString decodiusWritableConfigFilePath(const QString& fileName);
