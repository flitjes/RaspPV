#include "videodialog.h"
#include "ui_videodialog.h"

videoDialog::videoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoDialog)
{
    ui->setupUi(this);
}

videoDialog::~videoDialog()
{
    delete ui;
}

/*udpsrc -> rtph264depay -> ffdec_h264 -> ffmpegcolorspace -> autovideosink*/
void videoDialog::on_pushButton_clicked()
{
    m_pipeline = Pipeline::create("RaspFV");
    ElementPtr rtpudpsrc, rtph264depay, ffdec_h264, ffmpegcolorspace, autovideosink;


    rtpudpsrc = ElementFactory::make("udpsrc");
    if (!rtpudpsrc){
        qFatal("Failed to create udpsrc. Aborting...");
    }

    rtpudpsrc->setProperty("port", "9000");
    rtpudpsrc->setProperty("caps", Caps::fromString("application/x-rtp,"
                                                          "media=(string)video,"
                                                          "clock-rate=(int)90000,"
                                                          "encoding-name=(string)H264"));
    m_pipeline->add(rtpudpsrc);

    rtph264depay = ElementFactory::make("rtph264depay");
    if (!rtph264depay){
        qFatal("Failed to create rtph264depay");
    }
    m_pipeline->add(rtph264depay);
    rtpudpsrc->link(rtph264depay);

    ffdec_h264 = ElementFactory::make("ffdec_h264");
    if (!ffdec_h264){
        qFatal("Failed to create ffdec_h264");
    }
    m_pipeline->add(ffdec_h264);
    rtph264depay->link(ffdec_h264);

    ffmpegcolorspace = ElementFactory::make("ffmpegcolorspace");
    if (!ffmpegcolorspace){
        qFatal("Failed to create ffmpegcolorspace");
    }
    m_pipeline->add(ffmpegcolorspace);
    ffdec_h264->link(ffmpegcolorspace);

    autovideosink = ElementFactory::make("autovideosink");
    if (!autovideosink){
        qFatal("Failed to create autovideosink");
    }
    m_pipeline->add(autovideosink);
    ffmpegcolorspace->link(autovideosink);

    //ui->videoWidget->watchPipeline(m_pipeline);
    m_pipeline->setState(QGst::StatePlaying);
    printf("Started!\n");
}

