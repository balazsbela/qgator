# Add more folders to ship with the application, here
folder_01.source = qml/qGator
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    contentproviders/hncontentprovider.cpp \
    models/listmodel.cpp \
    models/articleitem.cpp \
    contentproviders/redditcontentprovider.cpp \
    contentproviders/aggregator.cpp \
    storage/datamanager.cpp

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()


OTHER_FILES += \
    qml/qGator/qGator.qml \
    loader.js \
    application.rc \
    gator.ico

HEADERS += \
    contentproviders/hncontentprovider.h \
    contentproviders/icontentprovider.h \
    models/listmodel.h \
    models/articleitem.h \
    contentproviders/redditcontentprovider.h \
    contentproviders/aggregator.h \
    storage/datamanager.h \
    storage/storage.h \
    storage/articleitemmodel.h

QT += webkit webkitwidgets declarative sql

RC_FILE = application.rc

CONFIG -= incremental

