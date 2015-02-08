#include "fpvgui.h"
#include "ui_fpvgui.h"

FPVGUI::FPVGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPVGUI)
{
    ui->setupUi(this);
}

FPVGUI::~FPVGUI()
{
    delete ui;
}
