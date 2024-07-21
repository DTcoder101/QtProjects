QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MainWindowWorkThread/openproloadthread.cpp \
    View/CreateProWizardView/CreateProWizardPage/confirmpage.cpp \
    View/CreateProWizardView/CreateProWizardPage/prosetpage.cpp \
    View/CreateProWizardView/wizard.cpp \
    View/PictureDisplay/CustomBtn/browsepicbtn.cpp \
    View/PictureDisplay/picturedisplaydialog.cpp \
    View/ProTree/CustemTreeWidget/RemoveProDlg/removeprodialog.cpp \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomAnimationWidget/customslideanimationwidget.cpp \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomSlideListWidget/CustomListWidgetItem/slidepiclistwidgetitem.cpp \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomSlideListWidget/slidepiclistwidget.cpp \
    View/ProTree/CustemTreeWidget/SlideShowDlg/slideshowdialog.cpp \
    View/ProTree/CustemTreeWidget/TreeWidgetItem/ProItemWorkThread/importactionthread.cpp \
    View/ProTree/CustemTreeWidget/TreeWidgetItem/protreeitem.cpp \
    View/ProTree/CustemTreeWidget/protreewidget.cpp \
    View/ProTree/protree.cpp \
    main.cpp \
    mainwindow.cpp

INCLUDEPATH += \
    View/CreateProWizardView/CreateProWizardPage \
    View/CreateProWizardView \
    View/PictureDisplay \
    View/PictureDisplay/CustomBtn \
    View/ProTree \
    View/ProTree/CustemTreeWidget \
    View/ProTree/CustemTreeWidget/RemoveProDlg \
    View/ProTree/CustemTreeWidget/SlideShowDlg \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomAnimationWidget \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomSlideListWidget \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomSlideListWidget/CustomListWidgetItem \
    View/ProTree/CustemTreeWidget/TreeWidgetItem \
    View/ProTree/CustemTreeWidget/TreeWidgetItem/ProItemWorkThread \
    PublicDef \
    MainWindowWorkThread \



HEADERS += \
    MainWindowWorkThread/openproloadthread.h \
    PublicDef/ConstDef.h \
    View/CreateProWizardView/CreateProWizardPage/confirmpage.h \
    View/CreateProWizardView/CreateProWizardPage/prosetpage.h \
    View/CreateProWizardView/wizard.h \
    View/PictureDisplay/CustomBtn/browsepicbtn.h \
    View/PictureDisplay/picturedisplaydialog.h \
    View/ProTree/CustemTreeWidget/RemoveProDlg/removeprodialog.h \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomAnimationWidget/customslideanimationwidget.h \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomSlideListWidget/CustomListWidgetItem/slidepiclistwidgetitem.h \
    View/ProTree/CustemTreeWidget/SlideShowDlg/CustomSlideListWidget/slidepiclistwidget.h \
    View/ProTree/CustemTreeWidget/SlideShowDlg/slideshowdialog.h \
    View/ProTree/CustemTreeWidget/TreeWidgetItem/ProItemWorkThread/importactionthread.h \
    View/ProTree/CustemTreeWidget/TreeWidgetItem/protreeitem.h \
    View/ProTree/CustemTreeWidget/protreewidget.h \
    View/ProTree/protree.h \
    mainwindow.h

FORMS += \
    View/CreateProWizardView/CreateProWizardPage/confirmpage.ui \
    View/CreateProWizardView/CreateProWizardPage/prosetpage.ui \
    View/CreateProWizardView/wizard.ui \
    View/PictureDisplay/picturedisplaydialog.ui \
    View/ProTree/CustemTreeWidget/RemoveProDlg/removeprodialog.ui \
    View/ProTree/CustemTreeWidget/SlideShowDlg/slideshowdialog.ui \
    View/ProTree/protree.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/rs.qrc
