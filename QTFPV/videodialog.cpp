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

void videoDialog::onBusErrorMessage(const QGst::MessagePtr & msg)
{
    qCritical() << "Error from bus:" << msg.staticCast<QGst::ErrorMessage>()->error();
}

/*udpsrc -> rtph264depay -> avdec_h264 -> videoconvert -> autovideosink*/
void videoDialog::on_pushButton_clicked()
{
    m_pipeline = QGst::Pipeline::create("RaspFV");
    QGst::ElementPtr rtpudpsrc, rtph264depay, avdec_h264, videoconvert, autovideosink;

    //watch the bus
    m_pipeline->bus()->addSignalWatch();
    QGlib::connect(m_pipeline->bus(), "message::error", this, &videoDialog::onBusErrorMessage);

    rtpudpsrc = QGst::ElementFactory::make("udpsrc");
    if (!rtpudpsrc){
        qFatal("Failed to create udpsrc. Aborting...");
    }

    rtpudpsrc->setProperty("port", 9000);
    rtpudpsrc->setProperty("caps", QGst::Caps::fromString("application/x-rtp,"
                                                          "media=(string)video,"
                                                          "clock-rate=(int)90000,"
                                                          "encoding-name=(string)H264"));
    m_pipeline->add(rtpudpsrc);

    rtph264depay = QGst::ElementFactory::make("rtph264depay");
    if (!rtph264depay){
        qFatal("Failed to create rtph264depay");
    }
    m_pipeline->add(rtph264depay);
    rtpudpsrc->link(rtph264depay);

    avdec_h264 = QGst::ElementFactory::make("avdec_h264");
    if (!avdec_h264){
        qFatal("Failed to create avdec_h264");
    }
    m_pipeline->add(avdec_h264);
    rtph264depay->link(avdec_h264);

    videoconvert = QGst::ElementFactory::make("videoconvert");
    if (!videoconvert){
        qFatal("Failed to create videoconvert");
    }
    m_pipeline->add(videoconvert);
    avdec_h264->link(videoconvert);

    autovideosink = QGst::ElementFactory::make("autovideosink");
    if (!autovideosink){
        qFatal("Failed to create autovideosink");
    }
    m_pipeline->add(autovideosink);
    videoconvert->link(autovideosink);

    ui->videoWidget->watchPipeline(m_pipeline);
    m_pipeline->setState(QGst::StatePlaying);
    printf("Started!\n");
}

