#include "userdialog.h"
#include "ui_UserDialog.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);

    recorder = new QAudioRecorder(this);
    probe = new QAudioProbe(this);
    client = new QTcpSocket(this);

    probe->setSource(recorder);

    ui->hostText->setText("192.168.0.10");
    ui->portText->setText("3333");

    connect(probe, &QAudioProbe::audioBufferProbed, this, &UserDialog::processBuffer);

}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::on_connectBtn_clicked()
{
    QString portStr = ui->portText->toPlainText();
    QString hostStr = ui->hostText->toPlainText();

    QPushButton *sender = static_cast<QPushButton *>(QObject::sender());
    sender->setEnabled(false);

    int port = portStr.toInt();
    connect_server(hostStr, port);

}

void UserDialog::processBuffer(const QAudioBuffer &buffer){
    QByteArray byteArr;
    byteArr.append(buffer.constData<char>(), buffer.byteCount());
    client->write(byteArr);

}

void UserDialog::connect_server(QString host, int port){
    try {
        client->connectToHost(host, quint16(port));
        QMessageBox box;
        box.setText(("Connected!"));
        box.exec();
    } catch (...) {

    }
}

void UserDialog::on_recordBtn_clicked()
{
    if(recorder->state() == QMediaRecorder::StoppedState){
        QAudioEncoderSettings settings;
        settings.setSampleRate(32000);
        settings.setBitRate(16);
        settings.setChannelCount(1);
        settings.setCodec("Default");

        recorder->setEncodingSettings(settings);

        recorder->setAudioInput("Default");
        recorder->record();

        QPushButton *sender = static_cast<QPushButton *>(QObject::sender());
        sender->setText("Stop");

    }
    else{
        recorder->stop();
        client->write(end.toUtf8());

        QPushButton *sender = static_cast<QPushButton *>(QObject::sender());
        sender->setText("Record");

    }
}
