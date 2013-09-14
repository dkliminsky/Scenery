#include "image.h"
#include <QDebug>

Image::Image()
{
    initDefault();
    create(0, 0, 4);
}

Image::Image(Image *image)
{
    initDefault();
    _mat = image->mat().clone();
}

Image::Image(int width, int height, int channels)
{
    initDefault();
    create(width, height, channels);
}

Image::Image(const QString &fileName)
{
    initDefault();
    load(fileName);
}

Image::~Image()
{
    if (saveImageThread) {
        saveImageThread->wait();
    }
}

void Image::set(IplImage *ipl)
{
    // Тормозит!
    //cv::Mat newMat(ipl);
    //_mat = newMat.clone();

    create(ipl->width, ipl->height, ipl->nChannels);
    _mat.data = reinterpret_cast<uchar *>(ipl->imageData);
}

void Image::bind()
{
    if (width() && height()) {

        int internalformat;
        int format;
        if (channels() == 4) {
            internalformat = GL_RGBA;
            format = GL_BGRA;
        }
        else if (channels() == 3) {
            internalformat = GL_RGB;
            format = GL_BGR;
        }
        else {
            qDebug() << "Image: Error channels";
            return;
        }

        if (!bindId || width() != bindWidth || height() != bindHeight ||
            channels() != bindChannels) {

            if (bindId) {
                glDeleteTextures(1, &bindId);
            }

            glEnable(GL_TEXTURE_2D);
            GLuint gl_id;
            glGenTextures(1, &gl_id);
            glBindTexture(GL_TEXTURE_2D, gl_id);
            glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width(), height(),
                         0, format, GL_UNSIGNED_BYTE, data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // задаём линейную фильтрацию вдали:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glDisable(GL_TEXTURE_2D);

            bindId = gl_id;
            bindWidth = width();
            bindHeight = height();
            bindChannels = channels();

            qDebug() << "Bind Image" << gl_id << width() << height() << channels();
        }
        else {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, bindId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0.0f, 0.0f, width(), height(),
                            format, GL_UNSIGNED_BYTE, data());
            glDisable(GL_TEXTURE_2D);
        }
    }
}

void Image::create(int width, int height, int channels)
{
    _mat.create(height, width, CV_8UC(channels));
}

void Image::load(const QString &fileName)
{
    LoadImageThread::loadImage(_mat, fileName);


    //_mat = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_UNCHANGED);


    //IplImage ipl = mat;
    //create(mat.cols, mat.rows, mat.channels());
    //_iplImage->imageData =  reinterpret_cast<char *>(mat.data);
    //cvCopy(&ipl, _iplImage);
}

void Image::save(const QString &fileName)
{
    //cv::Mat mat(_iplImage);
    SaveImageThread::saveImage(_mat, fileName);

    /*
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(3);
    cv::imwrite(fileName.toStdString(), mat, compression_params);
    */
}

void Image::saveThread(const QString &fileName)
{
    if (saveImageThread) {
        saveImageThread->wait();
        delete saveImageThread;
    }
    saveImageThread = new SaveImageThread(_mat, fileName);
    saveImageThread->start();
}

void Image::saveWait()
{
    if (saveImageThread) {
        saveImageThread->wait();
    }
}

void Image::initDefault()
{
    _fileName = "";
    saveImageThread = 0;

    bindId = 0;
    bindWidth = 0;
    bindHeight = 0;
    bindChannels = 0;
}

