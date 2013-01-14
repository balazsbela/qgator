#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "contentproviders/aggregator.h"
#include "contentproviders/icontentprovider.h"
#include <QtQuick>
#include <QQmlContext>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<Aggregator>("org.balazsbela.aggregator",1,0,"ContentProvider");

    QtQuick2ApplicationViewer* viewer = new QtQuick2ApplicationViewer();
    viewer->setMainQmlFile(QStringLiteral("qml/qGator/qGator.qml"));
    viewer->setResizeMode(QtQuick2ApplicationViewer::SizeRootObjectToView);       

    Aggregator* aggregator = new Aggregator(viewer);
    viewer->rootContext()->setContextProperty("contentProvider", aggregator);
    aggregator->retrieveContent();


    return app.exec();
}
