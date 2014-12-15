#include <QApplication>
#include "viewcontroller.h"
#include "documentationview.h"

#if defined(Q_OS_IOS)
extern "C" int qtmn(int argc, char **argv)
#else
int main(int argc, char *argv[])
#endif
{
    QApplication a(argc, argv);

    a.setStyleSheet(    "QWidget {background-color: #efeff4;}"
                        "QMainWindow {background-color: #efeff4;}"
                        "Separator {background-color: #c8c7cc; margin: 5px 5px 5px 5px;}"
                        "QLabel {font: 100 20px \"Serif\"; color: #8e8e93;}"
                        "QGroupBox {border:2px solid #c8c7cc; background-color: #efeff4; border-radius: 10px;}"
                        "QLineEdit {font: 100 20px \"Serif\";border: 2px solid #007aff; border-radius: 10px; background: #f5f5f5; color: #8e8e93; padding: 4px;}"
                        "QSlider::groove:horizontal {border: 1px solid #007aff; background: #efeff4; height: 5px;border-radius: 2px;}"
                        "QSlider::handle:horizontal {border: 2px solid #007aff; width: 38px; height: 38px; border-radius: 20px; background: #efeff4; margin: -20px 0;}"
                        "QSlider::add-page:horizontal {background: #b5b6b5;}"
                        "QSlider::sub-page:horizontal {background: #007aff;}"
                        "QPushButton {font: 100 20px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5; padding: 4px;}"
                        "QPushButton:pressed {color: #ffffff; background-color: #007aff;}"
                        "QPushButton#cameraButton {image: url(:/icons/specialPurposeIcons/camera.png); width: 30px; height: 30px; border: 0px; background-color: #efeff4;}"
                        "QPushButton#backButton {border: 0px; background-color: #efeff4}"
                        "QScrollArea {background-color: #efeff4; margin: 0 0; border: none;}"
                        "QScrollBar:vertical {border: 0px solid #007aff; margin: 0px 0px 0px 0px; background: #efeff4;}"
                        "QScrollBar::handle:vertical {background: #007aff; min-width: 60px; border-radius: 5px;}"
                        "QScrollBar::sub-line:vertical, QScrollBar::add-line:vertical  {border: 0px solid #007aff; background: #efeff4;}"
                        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {width: 0px; height: 0px;}"
                        "OwnCon {background-color: #efeff4;}"
                        "QTabWidget::pane {border-top: 2px solid #c8c7cc; margin-top: -35px;}"
                        "QTabWidget::tab-bar {alignment: center; }"
                        "QTabBar::Tab {border: 1px solid #007aff; border-top-left-radius: 4px; border-top-right-radius: 4px; padding: 6px; margin-bottom: -1px;}"
                        "QTabBar::Tab:selected {color: #ffffff; background-color: #007aff; margin-left: -4px; margin-right: -4px}"
                        "QTabBar::Tab:first:selected {margin-left: 0px}"
                        "QTabBar::Tab:last:selected {margin-right: 0px}"
                        "QTabBar::Tab:!selected {color: #007aff; background-color: #f5f5f5; margin-top: 2px}"
                        "QComboBox {font: 100 20px \"Serif\"; color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f4f4; padding: 4px;}"
                        "QComboBox::drop-down {background-color: #007aff;}"
                        "QComboBox::down-arrow {image: url(:/icons/specialPurposeIcons/downarrow.png);}"
                        "QComboBox::down-arrow:on {image: url(:/icons/specialPurposeIcons/downarrowon.png);}"
                        );

    /*ViewController v;

    v.show();*/

    DocumentationView d;

    d.show();


    return a.exec();
}
