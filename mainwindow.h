#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDesktopServices>
#include <QUrl>
#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QTextCursor>
#include <QToolButton>
#include <QToolBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontComboBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QTextCharFormat>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void open_outside_web();
    void open_file();
    void save_file();
    void save_file_As();

    void ShowPrintText();

    void ExportToPDF();

    void exit_find_file();
    void clear_edit();

    void ShowFindDiag();
    void reject();
    void ShowFindText();
    void find_file();

    void ShowReplaceDiag();
    void ShowReplaceText();
    void ShowReplaceText2();
    void ShowFindStr2();
    void ShowReplaceResult();

    void FontSizeSet();
    void FontColorset();

    void ShowFontComboBox(QString);
    void ShowSizeComboBox(QString);
    void ShowBoldBtn();
    void ShowitalicBtn();
    void ShowunderBtn();

    void AboutAuthorMessage();


protected:
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void InitStatusBar();
    void CreateFontSetting();
    void createactions();
    void createmenus();
    void CreateToolBar();

    QString path;

    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *exitAction;
    QAction *clearAction;
    QAction *FindAction;
    QAction *ReplaceAction;

    //打印文本
    QAction *PrintTextAction;
    QAction *PDFAction;

    //字体
    QAction *FontSize;
    QAction *FontColor;

    QAction *AboutAuthor;
    QAction *AboutQt;

    //撤销和回复
    QAction *undoAction;
    QAction *redoAction;

    //剪切 复制 粘贴
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;

    QTextEdit *textedit;

    int key_ctrl_release;

    //查找对话框
    QString str;
    QLabel *lineLabel;
    QLineEdit *lineEdit;
    QPushButton *findNextBtn;
    QPushButton *cancelBtn;

    QRadioButton *upRadio;
    QRadioButton *downRadio;

    QCheckBox *lowOrUpperBox;

    QButtonGroup *UpDownGroup;

    //替换对话框
    QString str2;
    QString str3;
    QLabel *lineLabel21;           //查找
    QLineEdit *lineEdit21;          //查找内容
    QLabel *lineLabel22;           //替换
    QLineEdit *lineEdit22;          //替换内容
    QPushButton *findNextBtn2;     //查找下一个
    QPushButton *ReplaceBtn;          //替换按钮
    QPushButton *cancelBtn2;

    QLabel *directLabel2;
    QCheckBox *lowOrUpperBox2;
    bool findjudge;

    //字体设置
    QLabel *fontlabel;
    QFontComboBox *fontComboBox;                //字体选框
    QComboBox *sizeComboBox;            //字体大小选择框

    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underBtn;

    //Tool button
    QToolBar *filebar;
    QToolBar *doToolBar;
    QToolBar *extendBar;
    QToolBar *fontToolBar;

    //statusBar显示作者信息
    QLabel *AuthorInfo;
    QLabel *Hyperlink;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
