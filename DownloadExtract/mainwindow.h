#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fAppDownloadDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnAppDownloadButtonClicked();

private:
    Ui::MainWindow *ui;
    fAppDownloadDialog *appDlg;
    QString mDownloadLink;
    QString mDownloadFolder;
    // void appDownload();

private slots:
	void startUnzip(QString fullPath, QString extractPath);
	void doneUnzip();
};

#endif // MAINWINDOW_H
