#include "fpvgui.h"
#include <QApplication>

#include <QtGStreamer/QGst/Pipeline>
#include <QtGStreamer/QGst/ElementFactory>
#include <QtGStreamer/QGst/Init>

using namespace QGst;
class FPVStream{
private:
    QGst::PipelinePtr m_pipeline;
public:
    FPVStream();
};

FPVStream::FPVStream(){
    m_pipeline = QGst::Pipeline::create("RaspFV");
    QGst::ElementPtr rtpudpsrc, rtph264depay, ffdec_h264, ffmpegcolorspace, autovideosink;

    
    rtpudpsrc = QGst::ElementFactory::make("udpsrc");
    if (!rtpudpsrc){
        qFatal("Failed to create udpsrc. Aborting...");
    }

    rtpudpsrc->setProperty("port", "9000");
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

    ffdec_h264 = QGst::ElementFactory::make("ffdec_h264");
    if (!ffdec_h264){
        qFatal("Failed to create ffdec_h264");
    }
    m_pipeline->add(ffdec_h264);
    rtph264depay->link(ffdec_h264);

    ffmpegcolorspace = QGst::ElementFactory::make("ffmpegcolorspace");
    if (!ffmpegcolorspace){
        qFatal("Failed to create ffmpegcolorspace");
    }
    m_pipeline->add(ffmpegcolorspace);
    ffdec_h264->link(ffmpegcolorspace);

    autovideosink = QGst::ElementFactory::make("autovideosink");
    if (!autovideosink){
        qFatal("Failed to create autovideosink");
    }
    m_pipeline->add(autovideosink);
    ffmpegcolorspace->link(autovideosink);

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FPVGUI w;
    FPVStream* stream;
    QGst::init(&argc, &argv);

    stream = new FPVStream();
    w.show();
    
    return a.exec();
}
