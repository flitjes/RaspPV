#ifndef VIDEODIALOG_H
#define VIDEODIALOG_H

#include <QDialog>

#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Init>
#include <QGst/Bus>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Message>
#include <QGst/Structure>

using namespace QGst;

namespace Ui {
class videoDialog;
}

class videoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit videoDialog(QWidget *parent = 0);
    ~videoDialog();
    
private Q_SLOTS:
    void on_pushButton_clicked();

private:
    Ui::videoDialog *ui;
    QGst::PipelinePtr m_pipeline;
};

#endif // VIDEODIALOG_H
