#ifndef FPVGUI_H
#define FPVGUI_H

#include <QMainWindow>

namespace Ui {
class FPVGUI;
}

class FPVGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FPVGUI(QWidget *parent = 0);
    ~FPVGUI();
    
private:
    Ui::FPVGUI *ui;
};

#endif // FPVGUI_H
