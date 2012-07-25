
#ifndef REPLAYGAINSCANNER_H
#define REPLAYGAINSCANNER_H

#include <KDialog>

class Config;
class Logger;
class ComboButton;
class ReplayGainFileList;

class QCheckBox;
class KPushButton;
class QProgressBar;
class QTreeWidget;
class KFileDialog;


/**
 * @short The Replay Gain Tool
 * @author Daniel Faust <hessijames@gmail.com>
 */
class ReplayGainScanner : public KDialog
{
    Q_OBJECT
public:
    ReplayGainScanner( Config*, Logger*, QWidget *parent=0, Qt::WFlags f=0 );
    ~ReplayGainScanner();

    void addFiles( KUrl::List urls );

private slots:
    void addClicked( int );
    void showDirDialog();
    void showFileDialog();
    void fileDialogAccepted();
    void showHelp();
    void calcReplayGainClicked();
    void removeReplayGainClicked();
    void cancelClicked();
    void processStarted();
    void processStopped();
    void updateProgress( int progress, int totalSteps );

private:
    ComboButton *cAdd;
    QCheckBox *cForce;
    ReplayGainFileList *fileList;
    QProgressBar *pProgressBar;
    KPushButton *pTagVisible;
    KPushButton *pRemoveTag;
    KPushButton *pCancel;
    KPushButton *pClose;
    KFileDialog *fileDialog;

    Config *config;
    Logger *logger;

signals:
    void addFile( const QString& );
    void addDir( const QString&, const QStringList& filter = QStringList(), bool recursive = true );
    void calcAllReplayGain( bool force );
    void removeAllReplayGain();
    void cancelProcess();
};

#endif // REPLAYGAINSCANNER_H
