#include "processwindow.h"
#include "ui_processwindow.h"
#include <QSettings>
#include <QDir>
#include <QDebug>

ProcessWindow::ProcessWindow(Process *process, QString file, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessWindow)
{
    ui->setupUi(this);
    this->process = process;
    this->file = file;

    connect(ui->saveButton, SIGNAL(pressed()), SLOT(saveParam()));

    // Mode
    QStringList modes;
    modes << "None" << "Color" << "Motion" << "Haar" << "Contour" << "HoughCircles";
    ui->modeBox->addItems(modes);
    connect(ui->modeBox, SIGNAL(activated(QString)), SLOT(slotMode(QString)));

    // Color
    connect(ui->colorInvertCheck, SIGNAL(clicked()), SLOT(slotColorRangeParam()));
    connect(ui->colorHminSlider, SIGNAL(valueChanged(int)), SLOT(slotColorRangeParam()));
    connect(ui->colorHmaxSlider, SIGNAL(valueChanged(int)), SLOT(slotColorRangeParam()));
    connect(ui->colorSminSlider, SIGNAL(valueChanged(int)), SLOT(slotColorRangeParam()));
    connect(ui->colorSmaxSlider, SIGNAL(valueChanged(int)), SLOT(slotColorRangeParam()));
    connect(ui->colorVminSlider, SIGNAL(valueChanged(int)), SLOT(slotColorRangeParam()));
    connect(ui->colorVmaxSlider, SIGNAL(valueChanged(int)), SLOT(slotColorRangeParam()));

    connect(ui->colorHminSlider, SIGNAL(valueChanged(int)),
            ui->colorHminLabel,  SLOT(setNum(int)));
    connect(ui->colorHmaxSlider, SIGNAL(valueChanged(int)),
            ui->colorHmaxLabel,  SLOT(setNum(int)));
    connect(ui->colorSminSlider, SIGNAL(valueChanged(int)),
            ui->colorSminLabel,  SLOT(setNum(int)));
    connect(ui->colorSmaxSlider, SIGNAL(valueChanged(int)),
            ui->colorSmaxLabel,  SLOT(setNum(int)));
    connect(ui->colorVminSlider, SIGNAL(valueChanged(int)),
            ui->colorVminLabel,  SLOT(setNum(int)));
    connect(ui->colorVmaxSlider, SIGNAL(valueChanged(int)),
            ui->colorVmaxLabel,  SLOT(setNum(int)));

    // Motion
    connect(ui->motionSensitivitySlider, SIGNAL(valueChanged(int)), SLOT(slotMotionParam()));
    connect(ui->motionSensitivitySlider, SIGNAL(valueChanged(int)),
            ui->motionSensitivityLabel, SLOT(setNum(int)));

    // Haar
    QDir dir;
    dir.cd("haarcascades");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.xml";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();

    ui->haarFileCombo->addItem("None", "");

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        QString fileName = fileInfo.fileName();
        QString filePath = fileInfo.filePath();

        ui->haarFileCombo->addItem(fileName, filePath);
    }
    connect(ui->haarFileCombo, SIGNAL(activated(int)), SLOT(slotHaarFile(int)));

    connect(ui->haarScaleDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotHaarParam()));
    connect(ui->haarMinXSpin, SIGNAL(valueChanged(int)), SLOT(slotHaarParam()));
    connect(ui->haarMinYSpin, SIGNAL(valueChanged(int)), SLOT(slotHaarParam()));
    connect(ui->haarMaxXSpin, SIGNAL(valueChanged(int)), SLOT(slotHaarParam()));
    connect(ui->haarMaxYSpin, SIGNAL(valueChanged(int)), SLOT(slotHaarParam()));

    // Contour

    connect(ui->contourThreshold1Slider, SIGNAL(valueChanged(int)),
            ui->contourThreshold1Label, SLOT(setNum(int)));
    connect(ui->contourThreshold2Slider, SIGNAL(valueChanged(int)),
            ui->contourThreshold2Label, SLOT(setNum(int)));

    connect(ui->contourThreshold1Slider, SIGNAL(valueChanged(int)),
            SLOT(slotContourParam()));
    connect(ui->contourThreshold2Slider, SIGNAL(valueChanged(int)),
            SLOT(slotContourParam()));

    // HoughCircles

    connect(ui->houghCirclesParam1Slider, SIGNAL(valueChanged(int)),
            ui->houghCirclesParam1Label, SLOT(setNum(int)));
    connect(ui->houghCirclesParam2Slider, SIGNAL(valueChanged(int)),
            ui->houghCirclesParam2Label, SLOT(setNum(int)));


    connect(ui->houghCirclesInverceRatioDoubleSpin, SIGNAL(valueChanged(double)),
            SLOT(slotHoughCircleParam()));
    connect(ui->houghCirclesMinDistanceSpin, SIGNAL(valueChanged(int)),
            SLOT(slotHoughCircleParam()));
    connect(ui->houghCirclesParam1Slider, SIGNAL(valueChanged(int)),
            SLOT(slotHoughCircleParam()));
    connect(ui->houghCirclesParam2Slider, SIGNAL(valueChanged(int)),
            SLOT(slotHoughCircleParam()));
    connect(ui->houghCirclesMinRadiusSpin, SIGNAL(valueChanged(int)),
            SLOT(slotHoughCircleParam()));
    connect(ui->houghCirclesMaxRadiusSpin, SIGNAL(valueChanged(int)),
            SLOT(slotHoughCircleParam()));

    // Clustering
    QStringList clusterModes;
    clusterModes << "None" << "Simple" << "Table";
    ui->clusterModeBox->addItems(clusterModes);
    connect(ui->clusterModeBox, SIGNAL(activated(QString)), SLOT(slotClusterMode(QString)));

    connect(ui->clusterSimpleDistanceSpin, SIGNAL(valueChanged(int)), SLOT(slotClusterSimple()));
    connect(ui->clusterSimpleLimitSpin, SIGNAL(valueChanged(int)), SLOT(slotClusterSimple()));
    connect(ui->clusterSimpleDensitySpin, SIGNAL(valueChanged(int)), SLOT(slotClusterSimple()));
    connect(ui->clusterTableWidthSpin, SIGNAL(valueChanged(int)), SLOT(slotClusterTable()));
    connect(ui->clusterTableHeightSpin, SIGNAL(valueChanged(int)), SLOT(slotClusterTable()));
    connect(ui->clusterTableDensitySpin, SIGNAL(valueChanged(int)), SLOT(slotClusterTable()));

    // Sequences
    connect(ui->seqAreaCountSpin, SIGNAL(valueChanged(int)), SLOT(slotSeqArea()));
    connect(ui->seqAreaLenghtLimitDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotSeqArea()));

    connect(ui->filterSeqAreaBufferSizeSpin, SIGNAL(valueChanged(int)), SLOT(slotFilterSeqArea()));

    // transform2D
    connect(ui->transform2DMxDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DMyDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DSxDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DSyDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DThetaDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DHDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DGDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));

    connect(ui->transform2DDeepHxDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DDeepHyDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));
    connect(ui->transform2DDeepHsDoubleSpin, SIGNAL(valueChanged(double)), SLOT(slotTransform2D()));

    loadParam();
}

ProcessWindow::~ProcessWindow()
{
    delete ui;
}

void ProcessWindow::closeEvent(QCloseEvent *)
{

}

void ProcessWindow::loadParam()
{
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("/Process");

        QString mode = settings.value("/Mode").toString();
        if ( mode == "None" ) {
            ui->modeBox->setCurrentIndex(0);
        }
        else if ( mode == "Color" ) {
            ui->modeBox->setCurrentIndex(1);
        }
        else if ( mode == "Motion" ) {
            ui->modeBox->setCurrentIndex(2);
        }
        else if ( mode == "Haar" ) {
            ui->modeBox->setCurrentIndex(3);
        }
        else if ( mode == "Contour" ) {
            ui->modeBox->setCurrentIndex(4);
        }
        else if ( mode == "HoughCircles" ) {
            ui->modeBox->setCurrentIndex(5);
        }
        else {
            mode = "None";
            ui->modeBox->setCurrentIndex(0);
        }
        slotMode(mode);

        settings.beginGroup("/Color");
            ui->colorInvertCheck->setChecked( settings.value("/Invert").toBool() );
            ui->colorHminSlider->setValue( settings.value("/Hmin").toInt() );
            ui->colorHmaxSlider->setValue( settings.value("/Hmax").toInt() );
            ui->colorSminSlider->setValue( settings.value("/Smin").toInt() );
            ui->colorSmaxSlider->setValue( settings.value("/Smax").toInt() );
            ui->colorVminSlider->setValue( settings.value("/Vmin").toInt() );
            ui->colorVmaxSlider->setValue( settings.value("/Vmax").toInt() );
            slotColorRangeParam();
        settings.endGroup();

        settings.beginGroup("/Motion");
            ui->motionSensitivitySlider->setValue( settings.value("/Sensitiviy").toInt() );
            slotMotionParam();
        settings.endGroup();

        settings.beginGroup("/Haar");
            QString file = settings.value("/File").toString();

            int index = ui->haarFileCombo->findData(file);
            if ( index!=-1) {
                ui->haarFileCombo->setCurrentIndex(index);
                slotHaarFile(index);
            }

            ui->haarScaleDoubleSpin->setValue( settings.value("/Scale").toDouble() );
            ui->haarMinXSpin->setValue( settings.value("MinX").toInt() );
            ui->haarMinYSpin->setValue( settings.value("MinY").toInt() );
            ui->haarMaxXSpin->setValue( settings.value("MaxX").toInt() );
            ui->haarMaxYSpin->setValue( settings.value("MaxY").toInt() );
            slotHaarParam();
        settings.endGroup();

        settings.beginGroup("/HoughCircles");
            ui->houghCirclesInverceRatioDoubleSpin->setValue( settings.value("/InverceRatio").toDouble() );
            ui->houghCirclesMinDistanceSpin->setValue( settings.value("MinDistance").toInt() );
            ui->houghCirclesParam1Slider->setValue( settings.value("Param1").toInt() );
            ui->houghCirclesParam2Slider->setValue( settings.value("Param2").toInt() );
            ui->houghCirclesMinRadiusSpin->setValue( settings.value("MinRadius").toInt() );
            ui->houghCirclesMaxRadiusSpin->setValue( settings.value("MaxRadius").toInt() );
        settings.endGroup();

        settings.beginGroup("/Clustering");
            mode = settings.value("/Mode").toString();
            if ( mode == "None" ) {
                ui->clusterModeBox->setCurrentIndex(0);
            }
            else if ( mode == "Simple" ) {
                ui->clusterModeBox->setCurrentIndex(1);
            }
            else if ( mode == "Table" ) {
                ui->clusterModeBox->setCurrentIndex(2);
            }
            else {
                mode = "None";
            }
            slotClusterMode(mode);

            ui->clusterSimpleDistanceSpin->setValue( settings.value("/Distance").toInt() );
            ui->clusterSimpleLimitSpin->setValue( settings.value("/Limit").toInt() );
            ui->clusterSimpleDensitySpin->setValue( settings.value("/SimpleDensity").toInt() );
            slotClusterSimple();

            ui->clusterTableWidthSpin->setValue( settings.value("/Width").toInt() );
            ui->clusterTableHeightSpin->setValue( settings.value("/Height").toInt() );
            ui->clusterTableDensitySpin->setValue( settings.value("/TableDensity").toInt() );
            slotClusterTable();
        settings.endGroup();

        settings.beginGroup("/Sequences");
            ui->seqAreaCountSpin->setValue( settings.value("/Count").toInt() );
            ui->seqAreaLenghtLimitDoubleSpin->setValue( settings.value("/LenghtLimit").toDouble() );
            slotSeqArea();
        settings.endGroup();

        settings.beginGroup("/Transform2D");
            ui->transform2DMxDoubleSpin->setValue( settings.value("/Mx").toDouble());
            ui->transform2DMyDoubleSpin->setValue( settings.value("/My").toDouble());
            ui->transform2DSxDoubleSpin->setValue( settings.value("/Sx").toDouble());
            ui->transform2DSyDoubleSpin->setValue( settings.value("/Sy").toDouble());

            ui->transform2DThetaDoubleSpin->setValue( settings.value("/Theta").toDouble());
            ui->transform2DHDoubleSpin->setValue( settings.value("/H").toDouble());
            ui->transform2DGDoubleSpin->setValue( settings.value("/G").toDouble());

            ui->transform2DDeepHxDoubleSpin->setValue( settings.value("/DeepHx").toDouble());
            ui->transform2DDeepHyDoubleSpin->setValue( settings.value("/DeepHy").toDouble());
            ui->transform2DDeepHsDoubleSpin->setValue( settings.value("/DeepHs").toDouble());

            slotTransform2D();
        settings.endGroup();

    settings.endGroup();
}

void ProcessWindow::saveParam()
{
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup("/Process"); //+QString::number(column));

        settings.setValue("/Name", "main");

        settings.setValue("/Mode", ui->modeBox->currentText());

        settings.beginGroup("/Color");
            settings.setValue("/Invert", ui->colorInvertCheck->isChecked());
            settings.setValue("/Hmin", ui->colorHminSlider->value());
            settings.setValue("/Hmax", ui->colorHmaxSlider->value());
            settings.setValue("/Smin", ui->colorSminSlider->value());
            settings.setValue("/Smax", ui->colorSmaxSlider->value());
            settings.setValue("/Vmin", ui->colorVminSlider->value());
            settings.setValue("/Vmax", ui->colorVmaxSlider->value());
        settings.endGroup();

        settings.beginGroup("/Motion");
            settings.setValue("/Sensitiviy", ui->motionSensitivitySlider->value() );
        settings.endGroup();

        settings.beginGroup("/Haar");
            settings.setValue("/File",
                              ui->haarFileCombo->itemData(ui->haarFileCombo->currentIndex()).toString());
            settings.setValue("/Scale", ui->haarScaleDoubleSpin->value());
            settings.setValue("/MinX", ui->haarMinXSpin->value());
            settings.setValue("/MinY", ui->haarMinYSpin->value());
            settings.setValue("/MaxX", ui->haarMaxXSpin->value());
            settings.setValue("/MaxY", ui->haarMaxYSpin->value());
        settings.endGroup();

        settings.beginGroup("/HoughCircles");
            settings.setValue("/InverceRatio", ui->houghCirclesInverceRatioDoubleSpin->value());
            settings.setValue("MinDistance", ui->houghCirclesMinDistanceSpin->value());
            settings.setValue("Param1", ui->houghCirclesParam1Slider->value());
            settings.setValue("Param2", ui->houghCirclesParam2Slider->value());
            settings.setValue("MinRadius", ui->houghCirclesMinRadiusSpin->value());
            settings.setValue("MaxRadius", ui->houghCirclesMaxRadiusSpin->value());
        settings.endGroup();

        settings.beginGroup("/Clustering");
            settings.setValue("/Mode", ui->clusterModeBox->currentText());

            settings.setValue("/Distance",  ui->clusterSimpleDistanceSpin->value() );
            settings.setValue("/Limit",  ui->clusterSimpleLimitSpin->value() );
            settings.setValue("/SimpleDensity",  ui->clusterSimpleDensitySpin->value() );

            settings.setValue("/Width",  ui->clusterTableWidthSpin->value() );
            settings.setValue("/Height",  ui->clusterTableHeightSpin->value() );
            settings.setValue("/TableDensity",  ui->clusterTableDensitySpin->value() );
        settings.endGroup();

        settings.beginGroup("/Sequences");
            settings.setValue("/Distance",  ui->clusterSimpleDistanceSpin->value() );
            settings.setValue("/Limit",  ui->clusterSimpleLimitSpin->value() );
            settings.setValue("/Density",  ui->clusterSimpleDensitySpin->value() );

            settings.setValue("/Count", ui->seqAreaCountSpin->value() );
            settings.setValue("/LenghtLimit", ui->seqAreaLenghtLimitDoubleSpin->value() );
        settings.endGroup();

        settings.beginGroup("/Transform2D");
            settings.setValue("/Mx", ui->transform2DMxDoubleSpin->value());
            settings.setValue("/My", ui->transform2DMyDoubleSpin->value());
            settings.setValue("/Sx", ui->transform2DSxDoubleSpin->value());
            settings.setValue("/Sy", ui->transform2DSyDoubleSpin->value());

            settings.setValue("/Theta", ui->transform2DThetaDoubleSpin->value());
            settings.setValue("/H", ui->transform2DHDoubleSpin->value());
            settings.setValue("/G", ui->transform2DGDoubleSpin->value());

            settings.setValue("/DeepHx", ui->transform2DDeepHxDoubleSpin->value());
            settings.setValue("/DeepHy", ui->transform2DDeepHyDoubleSpin->value());
            settings.setValue("/DeepHs", ui->transform2DDeepHsDoubleSpin->value());
        settings.endGroup();

    settings.endGroup();
}

void ProcessWindow::slotMode(QString mode)
{
    qDebug() << "Set mode:" << mode;
    if ( mode == "None" ) {
        ui->modesWidget->setCurrentIndex(0);
        process->setMode(Process::ProcessNone);
    }
    else if ( mode == "Color" ) {
        ui->modesWidget->setCurrentIndex(1);
        process->setMode(Process::ProcessColor);
    }
    else if ( mode == "Motion" ) {
        ui->modesWidget->setCurrentIndex(2);
        process->setMode(Process::ProcessMotion);
    }
    else if ( mode == "Haar" ) {
        ui->modesWidget->setCurrentIndex(3);
        process->setMode(Process::ProcessHaar);
    }
    else if ( mode == "Contour" ) {
        ui->modesWidget->setCurrentIndex(4);
        process->setMode(Process::ProcessContour);
    }
    else if ( mode == "HoughCircles" ) {
        ui->modesWidget->setCurrentIndex(5);
        process->setMode(Process::ProcessHoughCircles);
    }
}

void ProcessWindow::slotColorRangeParam()
{
    Process::ColorRangeParam param;
    param.invert = ui->colorInvertCheck->isChecked();
    param.Hmin = ui->colorHminSlider->value();
    param.Hmax = ui->colorHmaxSlider->value();
    param.Smin = ui->colorSminSlider->value();
    param.Smax = ui->colorSmaxSlider->value();
    param.Vmin = ui->colorVminSlider->value();
    param.Vmax = ui->colorVmaxSlider->value();
    process->setColorRangeParam(param);
}

void ProcessWindow::slotMotionParam()
{
    Process::MotionParam param;
    param.sensitivity = ui->motionSensitivitySlider->value();
    process->setMotionParam(param);
}

void ProcessWindow::slotHaarFile(int index)
{
    process->setHaarFile( ui->haarFileCombo->itemData(index).toString().toStdString() );
}

void ProcessWindow::slotHaarParam()
{
    Process::HaarParam param;
    param.scaleFactor = ui->haarScaleDoubleSpin->value();
    param.minSizeX = ui->haarMinXSpin->value();
    param.minSizeY = ui->haarMinYSpin->value();
    param.maxSizeX = ui->haarMaxXSpin->value();
    param.maxSizeY = ui->haarMaxYSpin->value();
    process->setHaarParam(param);
}

void ProcessWindow::slotContourParam()
{
    Process::ContourParam param;
    param.threshold1 = ui->contourThreshold1Slider->value();
    param.threshold2 = ui->contourThreshold2Slider->value();
    process->setContourParam(param);
}

void ProcessWindow::slotHoughCircleParam()
{
    Process::HoughCirclesParam param;
    param.inverseRatio = ui->houghCirclesInverceRatioDoubleSpin->value();
    param.minDistance = ui->houghCirclesMinDistanceSpin->value();
    param.param1 = ui->houghCirclesParam1Slider->value();
    param.param2 = ui->houghCirclesParam2Slider->value();
    param.minRadius = ui->houghCirclesMinRadiusSpin->value();
    param.maxRadius = ui->houghCirclesMaxRadiusSpin->value();
    process->setHoughCircleParam(param);
}

void ProcessWindow::slotClusterMode(QString mode)
{
    qDebug() << "Set clustering mode:" << mode;
    if ( mode == "None" ) {
        process->setClusterMode(Process::ClusterNone);
    }
    else if ( mode == "Simple" ) {
        process->setClusterMode(Process::ClusterSimple);
    }
    else if ( mode == "Table" ) {
        process->setClusterMode(Process::ClusterTable);
    }
}

void ProcessWindow::slotClusterSimple()
{
    Process::SimpleClusterParam param;
    param.distance = ui->clusterSimpleDistanceSpin->value();
    param.limit = ui->clusterSimpleLimitSpin->value();
    param.density = ui->clusterSimpleDensitySpin->value();
    process->setSimpleClusterParam(param);
}

void ProcessWindow::slotClusterTable()
{
    Process::TableClusterParam param;
    param.cellWidth = ui->clusterTableWidthSpin->value();
    param.cellHeight = ui->clusterTableHeightSpin->value();
    param.density = ui->clusterTableDensitySpin->value();
    process->setTableClusterParam(param);
}

void ProcessWindow::slotSeqArea()
{
    Process::SeqAreaParam param;
    param.count = ui->seqAreaCountSpin->value();
    param.lenghtLimit = ui->seqAreaLenghtLimitDoubleSpin->value();
    process->setSeqAreaParam(param);
}

void ProcessWindow::slotFilterSeqArea()
{
    Process::FilterSeqAreaParam param;
    param.buffSize = ui->filterSeqAreaBufferSizeSpin->value();
    process->setFilterSeqAreaParam(param);
}

void ProcessWindow::slotTransform2D()
{
    Process::Transform2DParam param;
    param.mx = ui->transform2DMxDoubleSpin->value();
    param.my = ui->transform2DMyDoubleSpin->value();
    param.sx = ui->transform2DSxDoubleSpin->value();
    param.sy = ui->transform2DSyDoubleSpin->value();
    param.theta = ui->transform2DThetaDoubleSpin->value();
    param.h = ui->transform2DHDoubleSpin->value();
    param.g = ui->transform2DGDoubleSpin->value();
    param.deepHx = ui->transform2DDeepHxDoubleSpin->value();
    param.deepHy = ui->transform2DDeepHyDoubleSpin->value();
    param.deepHs = ui->transform2DDeepHsDoubleSpin->value();
    process->setTransform2DParam(param);
}
