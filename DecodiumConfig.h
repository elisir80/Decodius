// DecodiumConfig.h — configurazione per raggiungere Decodium 4 (lettura + comandi),
// portabile tra Windows e Linux/Raspberry Pi.
//
// Ordine di risoluzione:
//   1) file decodius_decodium.txt nei path di configurazione Decodius
//      (config utente, cartella eseguibile, bundle Resources, directory .app), es.:
//        host=192.168.1.20
//        web_port=8080
//        web_token=<64 hex>           (token API web, se richiesto)
//        cmd_port=19091
//        cmd_user=admin
//        cmd_token=<token>            (vuoto su loopback)
//   2) su WINDOWS, i campi mancanti si leggono dal registro di Decodium
//      (HKCU\Software\Decodium\Decodium4 o Decodium3): WebServerAccessToken, RemoteHttpPort,
//      RemoteUser, RemoteToken.
//   3) default: host 127.0.0.1, porte 8080/19091, user admin.
//
// Sul Pi, Decodium gira su un PC Windows della LAN: basta creare il file con
// host=<IP del PC> e gli eventuali token.
#pragma once
#include <QString>

struct DecodiumConfig {
    QString host     = QStringLiteral("127.0.0.1");
    int     webPort  = 8080;
    QString webToken;                       // token per /api/state, /api/decodes
    int     cmdPort  = 19091;
    QString cmdUser  = QStringLiteral("admin");
    QString cmdToken;                       // Bearer per /api/v1/commands (vuoto su loopback)

    QString webBase() const { return QStringLiteral("http://%1:%2").arg(host).arg(webPort); }
    QString cmdBase() const { return QStringLiteral("http://%1:%2").arg(host).arg(cmdPort); }
};

// Carica la configurazione secondo l'ordine descritto sopra.
DecodiumConfig loadDecodiumConfig();
