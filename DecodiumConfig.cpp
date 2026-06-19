// DecodiumConfig.cpp — vedi DecodiumConfig.h
#include "DecodiumConfig.h"
#include "ConfigPaths.h"
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

    // 1) File decodius_decodium.txt nei path portabili di Decodius.
    QFile f(decodiusConfigFilePath(QStringLiteral("decodius_decodium.txt")));
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
    // 2) Windows: completa i campi mancanti dal registro di Decodium 4, con fallback
    //    a Decodium 3 per compatibilità con installazioni vecchie.
    auto fillFromRegistry = [&](const QString& appName) {
        QSettings s(QStringLiteral("Decodium"), appName);
        if (!hasWebPort) {
            const int p = s.value(QStringLiteral("WebServerPort")).toInt();
            if (p > 0) { c.webPort = p; hasWebPort = true; }
        }
        if (!hasWebToken) {
            const QString token = s.value(QStringLiteral("WebServerAccessToken")).toString().trimmed();
            if (!token.isEmpty()) { c.webToken = token; hasWebToken = true; }
        }
        if (!hasCmdPort) {
            const int p = s.value(QStringLiteral("RemoteHttpPort")).toInt();
            if (p > 0) { c.cmdPort = p; hasCmdPort = true; }
        }
        if (!hasCmdUser) {
            const QString user = s.value(QStringLiteral("RemoteUser")).toString().trimmed();
            if (!user.isEmpty()) { c.cmdUser = user; hasCmdUser = true; }
        }
        if (!hasCmdToken) {
            const QString token = s.value(QStringLiteral("RemoteToken")).toString().trimmed();
            if (!token.isEmpty()) { c.cmdToken = token; hasCmdToken = true; }
        }
    };
    fillFromRegistry(QStringLiteral("Decodium4"));
    fillFromRegistry(QStringLiteral("Decodium3"));
    Q_UNUSED(hasHost);
#else
    // 3) Linux/altro: i default valgono già; il file è la fonte primaria.
    Q_UNUSED(hasHost); Q_UNUSED(hasWebPort); Q_UNUSED(hasWebToken);
    Q_UNUSED(hasCmdPort); Q_UNUSED(hasCmdUser); Q_UNUSED(hasCmdToken);
#endif

    return c;
}
