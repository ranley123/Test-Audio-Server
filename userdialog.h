#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QMediaRecorder>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QMessageBox>

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();

private slots:
    void on_connectBtn_clicked();

    void processBuffer(const QAudioBuffer&);

    void on_recordBtn_clicked();

private:
    Ui::UserDialog *ui;

    QTcpSocket *client = nullptr;
    QAudioRecorder *recorder = nullptr;
    QAudioProbe *probe = nullptr;
    QByteArray audioData;

    void connect_server(QString host, int port);

    QString EOS = "\n";
    QString end = "EOF";
};

#endif // USERDIALOG_H
