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
    QGst::PipelinePtr m_pipeline_right;
    QGst::PipelinePtr m_pipeline_left;
    void onBusErrorMessage(const QGst::MessagePtr & msg);
    void create_udp_rtp_video_pipeline(QGst::PipelinePtr pipeline);
};

#endif // VIDEODIALOG_H
