#include <QApplication>
#include "viewcontroller.h"
#if defined(Q_OS_IOS)
extern "C" int qtmn(int argc, char **argv)
#else
int main(int argc, char *argv[])
#endif
{
    QApplication a(argc, argv);

    a.setStyleSheet("QWidget {background-color: #efeff4;}"
                        "QMainWindow {background-color: #efeff4;margin: 0 0;}"
                        "Separator {background-color: #c8c7cc; margin: 5px 5px 5px 5px;}"
                        "QLabel {font: 100 26px \"Serif\"; color: #8e8e93;}"
                        "QGroupBox {border:2px solid #c8c7cc; background-color: #efeff4; border-radius: 10px;}"
                        "QLineEdit {font: 100 26px \"Serif\";border: 2px solid #007aff; border-radius: 10px; background: #f5f5f5; color: #8e8e93;}"
                        "QSlider::groove:horizontal {border: 1px solid #007aff; background: #efeff4; height: 5px;border-radius: 2px;}"
                        "QSlider::handle:horizontal {border: 2px solid #007aff; width: 48px; height: 48px; border-radius: 25px; background: #efeff4; margin: -25px 0;}"
                        "QSlider::add-page:horizontal {background: #b5b6b5;}"
                        "QSlider::sub-page:horizontal {background: #007aff;}"
                        "QPushButton {font: 100 26px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}"
                        "QScrollArea {background-color: #efeff4; margin: 0 0; border: none;}"
                        "QScrollBar:vertical {border: 0px solid #007aff; margin: 0px 0px 0px 0px; background: #efeff4;}"
                        "QScrollBar::handle:vertical {background: #007aff; min-width: 60px; border-radius: 5px;}"
                        "QScrollBar::sub-line:vertical, QScrollBar::add-line:vertical  {border: 0px solid #007aff; background: #efeff4;}"
                        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {width: 0px; height: 0px;}"
                        "OwnCon {background-color: #efeff4;}");

    ViewController v;

    v.show();

    return a.exec();
}
