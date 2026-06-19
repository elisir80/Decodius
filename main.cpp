// main.cpp — DECODIUS (C++/Qt6/QML)
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QFileInfo>
#include <QUrl>
#include <QtGlobal>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("Decodius");
    app.setApplicationVersion("1.12 Alpha");   // mostrata nella UI (Qt.application.version)
    app.setOrganizationName("Decodius");
    // Icona di finestra/taskbar (l'icona del file .exe arriva dalla risorsa .rc).
    const QString iconPath = app.applicationDirPath() + QStringLiteral("/decodius.ico");
    if (QFileInfo::exists(iconPath))
        app.setWindowIcon(QIcon(iconPath));

    QQmlApplicationEngine engine;
    // I tipi AudioAnalyzer e Assistant sono registrati via QML_ELEMENT (qt_add_qml_module).
    engine.addImportPath(QStringLiteral("qrc:/qt/qml"));
    engine.addImportPath(QStringLiteral("qrc:/"));

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    engine.loadFromModule("Decodius", "Main");
#else
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/Decodius/Main.qml")));
    if (engine.rootObjects().isEmpty())
        engine.load(QUrl(QStringLiteral("qrc:/Decodius/Main.qml")));
#endif

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
