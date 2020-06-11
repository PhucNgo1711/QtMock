#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "ApplicationPreferences.h"
#include "qzipreader.h"
#include <QFile>
#include "ExtractInBackground.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //! load preferences
    ApplicationPreferences::GetInstance()->DeSerializePreferences();
    ApplicationPreferences::GetInstance()->DisplayPreferences();

    appDlg = new fAppDownloadDialog();

    //mDownloadLink = "ftp://www.nitrc.org/home/groups/captk/downloads/models/SBRT.zip";
    mDownloadLink = "https://github.com/PhucNgo1711/precompiledBinaries/raw/master/windows/confetti.zip";
    mDownloadFolder = "/Users/phucngo/Downloads";

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(OnAppDownloadButtonClicked()));
    connect( appDlg, SIGNAL(doneDownload(QString, QString)), this, SLOT(startUnzip(QString, QString)));
    // connect( &appDownloadDialog, SIGNAL(doneDownload(QString, QString)), this, SLOT(startUnzip(QString, QString)));   

}

MainWindow::~MainWindow()
{
    delete ui;

    ApplicationPreferences::GetInstance()->SerializePreferences();
}

void MainWindow::OnAppDownloadButtonClicked()
{
    appDlg->SetPaths(mDownloadFolder.toStdString());

    appDlg->SetDownloadLink(mDownloadLink.toStdString());
    appDlg->show();
}

// void MainWindow::appDownload()
// {
// 	// std::string linkyml = "";

// 	// #ifdef _WIN32
// 	// linkyml = "Windows";
// 	// #elif __APPLE__
// 	// linkyml = "macOS";
// 	// #else
// 	// linkyml = "Linux";
// 	// #endif

// 	std::string downloadLink = m_appDownloadConfigs["apps"][this->m_AppName.toStdString()][linkyml].as<std::string>();

// 	appDownloadDialog = new fAppDownloadDialog();
// 	appDownloadDialog.SetPaths(downloadFolder);
// 	appDownloadDialog.SetDownloadLink(downloadLink);
// 	appDownloadDialog.exec();

// }

void MainWindow::startUnzip(QString fullPath, QString extractPath) 
{
	if (QFile::exists(fullPath)) {

		ExtractInBackground* asyncExtract = new ExtractInBackground();

		connect(asyncExtract, SIGNAL(resultReady(QString)), this, SLOT(doneUnzip()));
		connect(asyncExtract, &ExtractInBackground::finished, asyncExtract, &QObject::deleteLater);

		asyncExtract->setFullPath(fullPath);
		asyncExtract->setExtractPath(extractPath);
		asyncExtract->setAppName("confetti");

		asyncExtract->start();
	}
}

void MainWindow::doneUnzip() {

    QMessageBox::information(NULL, tr("Extraction"),"Extraction done");

}