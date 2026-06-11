// DecodiumConfig.cpp — vedi DecodiumConfig.h
#include "DecodiumConfig.h"
#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#ifdef Q_OS_WIN
#include <QSettings>
#endif

DecodiumConfig loadDecodiumConfig()
{
    DecodiumConfig c;
    bool hasHost = false, hasWebPort = false, hasWebToken = false,
         hasCmdPort = false, hasCmdUser = false, hasCmdToken = false;

    // 1) File decodius_decodium.txt accanto all'eseguibile.
    QFile f(QCoreApplication::applicationDirPath() + QStringLiteral("/decodius_decodium.txt"));
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        const QStringList lines = QString::fromUtf8(f.readAll()).split('\n');
        for (const QString& raw : lines) {
            const QString l = raw.trimmed();
            if (l.isEmpty() || l.startsWith('#')) continue;
            const int eq = l.indexOf('=');
            if (eq < 0) continue;
            const QString k = l.left(eq).trimmed().toLower();
            const QString v = l.mid(eq + 1).trimmed();
            if (k == QLatin1String("host"))       { c.host = v; hasHost = true; }
            else if (k == QLatin1String("web_port"))  { c.webPort = v.toInt(); hasWebPort = true; }
            else if (k == QLatin1String("web_token")) { c.webToken = v; hasWebToken = true; }
            else if (k == QLatin1String("cmd_port"))  { c.cmdPort = v.toInt(); hasCmdPort = true; }
            else if (k == QLatin1String("cmd_user"))  { c.cmdUser = v; hasCmdUser = true; }
            else if (k == QLatin1String("cmd_token")) { c.cmdToken = v; hasCmdToken = true; }
        }
        f.close();
    }

#ifdef Q_OS_WIN
    // 2) Windows: completa i campi mancanti dal registro di Decodium.
    QSettings s(QStringLiteral("Decodium"), QStringLiteral("Decodium3"));
    if (!hasWebToken)
        c.webToken = s.value(QStringLiteral("WebServerAccessToken")).toString().trimmed();
    if (!hasCmdPort) {
        const int p = s.value(QStringLiteral("RemoteHttpPort"), 19091).toInt();
        c.cmdPort = (p > 0) ? p : 19091;
    }
    if (!hasCmdUser)
        c.cmdUser = s.value(QStringLiteral("RemoteUser"), QStringLiteral("admin")).toString();
    if (!hasCmdToken)
        c.cmdToken = s.value(QStringLiteral("RemoteToken")).toString().trimmed();
    Q_UNUSED(hasHost); Q_UNUSED(hasWebPort);
#else
    // 3) Linux/altro: i default valgono già; il file è la fonte primaria.
    Q_UNUSED(hasHost); Q_UNUSED(hasWebPort); Q_UNUSED(hasWebToken);
    Q_UNUSED(hasCmdPort); Q_UNUSED(hasCmdUser); Q_UNUSED(hasCmdToken);
#endif

    return c;
}
