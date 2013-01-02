#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "contentproviders/hncontentprovider.h"
#include "contentproviders/icontentprovider.h"
#include <QtQuick>
#include <QQmlContext>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<HNContentProvider>("HNContentProvider",1,0,"ContentProvider");

    QtQuick2ApplicationViewer* viewer = new QtQuick2ApplicationViewer();
    viewer->setMainQmlFile(QStringLiteral("qml/qGator/qGator.qml"));
    viewer->setResizeMode(QtQuick2ApplicationViewer::SizeRootObjectToView);
    IContentProvider* provider = new HNContentProvider(viewer);
    viewer->rootContext()->setContextProperty("contentProvider", provider);
    provider->retrieveContent();

    return app.exec();
}
