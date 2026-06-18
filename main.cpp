// main.cpp — DECODIUS (C++/Qt6/QML)
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QFileInfo>
#include <QDir>
#include <QUrl>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("Decodius");
    app.setOrganizationName("Decodius");
    // Icona di finestra/taskbar (l'icona del file .exe arriva dalla risorsa .rc).
    QString iconPath = app.applicationDirPath() + QStringLiteral("/decodius.ico");
#ifdef Q_OS_MACOS
    if (!QFileInfo::exists(iconPath))
        iconPath = QDir(app.applicationDirPath()).absoluteFilePath(QStringLiteral("../Resources/decodius.ico"));
#endif
    if (QFileInfo::exists(iconPath))
        app.setWindowIcon(QIcon(iconPath));

    QQmlApplicationEngine engine;
    // I tipi AudioAnalyzer e Assistant sono registrati via QML_ELEMENT (qt_add_qml_module).
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    engine.loadFromModule("Decodius", "Main");
#else
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/Decodius/Main.qml")));
#endif

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
