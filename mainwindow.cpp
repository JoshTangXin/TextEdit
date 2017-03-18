#include "mainwindow.h"
#include "mylabel.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    this->InitStatusBar();

    key_ctrl_release = 0;
    path = tr("");
    setWindowTitle(tr("Notepad(josh)"));

    delete(ui->mainToolBar);    //删除maintoolbar，之后通过addtoolbar设增加toolbar同时设置标签

    textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    CreateFontSetting();

    createactions();

    createmenus();

    CreateToolBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitStatusBar()
{
    QStatusBar *statusbar = ui->statusBar;          //获取状态栏

    AuthorInfo = new QLabel(this);
    AuthorInfo->setText("    Develop by josh    ");
    AuthorInfo->setFrameShape(QFrame::WinPanel);
    AuthorInfo->setFrameShadow(QFrame::Sunken);     //QFrame::Sunken - 框架和内容看起来凹陷

    mylabel *my_clicked_label = new mylabel;

    my_clicked_label->setText("          www.baidu.com            ");
    my_clicked_label->setStyleSheet("color:red");
    my_clicked_label->setFrameShape(QFrame::WinPanel);
    my_clicked_label->setFrameShadow(QFrame::Sunken);

    connect(my_clicked_label,SIGNAL(label_Clicked()),this,SLOT(open_outside_web()));

    statusbar->addWidget(AuthorInfo);
    statusbar->addPermanentWidget(my_clicked_label);
}

void MainWindow::CreateFontSetting()
{
    fontlabel = new QLabel(tr("Font:"));
    QFont ft;
    ft.setPointSize(14);
    fontlabel->setFont(ft);
    fontComboBox = new QFontComboBox;

    //字体选择条-->setFontFilter--接口过滤(只在下拉列表框中显示某一类字体,默认情况下为QFontComboBox::AllFonts,列出所有字体
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);
    fontComboBox->setFont(ft);

    sizeComboBox = new QComboBox;
    sizeComboBox->setFont(ft);

    //The QFontDatabase class provides information about the fonts available in the underlying window system
    QFontDatabase db;

    //standardSize(): return a list of standard font size(返回可用标准字号的列表).
    foreach (int size, db.standardSizes ())
        sizeComboBox->addItem (QString::number (size)); //将它们插入到字号下拉框中

    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon(":/icons/textbold.png"));
    boldBtn->setCheckable(true);

    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon(":/icons/textitalic.png"));
    italicBtn->setCheckable(true);

    underBtn = new QToolButton;
    underBtn->setIcon(QIcon(":/icons/textunder.png"));
    underBtn->setCheckable(true);

    connect (fontComboBox, SIGNAL(activated(QString)), this, SLOT(ShowFontComboBox(QString)));
    connect (sizeComboBox, SIGNAL(activated(QString)), this, SLOT(ShowSizeComboBox(QString)));
    connect(boldBtn,SIGNAL(clicked(bool)),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked(bool)),this,SLOT(ShowitalicBtn()));
    connect(underBtn,SIGNAL(clicked(bool)),this,SLOT(ShowunderBtn()));

}

void MainWindow::open_outside_web()
{
    const QUrl url("www.baidu.com");

    QDesktopServices::openUrl(url);
}

void MainWindow::createactions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::New);
    openAction->setStatusTip(tr("Open a new file"));
    openAction->setIcon(QIcon(":/icons/document-new.png"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open_file()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon(":/icons/document-save.png"));

    QString str = textedit->toPlainText();
//  qDebug()<<str;
    if(str == "")
    {
        this->saveAction->setEnabled(false);
    }

    saveasAction = new QAction(tr("&Save as"), this);
    saveasAction->setShortcut (tr("Ctrl+alt+S"));
    saveasAction->setStatusTip(tr("Save file..."));
    saveasAction->setIcon(QIcon(":/icons/document-save-as.png"));
    connect(saveasAction,SIGNAL(triggered()),this,SLOT(save_file_As()));

    PrintTextAction = new QAction(tr("&Print"), this);
    PrintTextAction->setShortcut(QKeySequence::Print);
    PrintTextAction->setIcon(QIcon(":/icons/print.png"));
    connect (PrintTextAction, SIGNAL(triggered()), this, SLOT(ShowPrintText()));

    PDFAction = new QAction(tr("&Export to PDF"), this);
    PDFAction->setIcon(QIcon(":/icons/PDF.png"));
    connect (PDFAction, SIGNAL(triggered()), this, SLOT(ExportToPDF()));

    FindAction = new QAction(tr("&Find..."), this);
    FindAction->setShortcut(QKeySequence::Find);
    FindAction->setIcon(QIcon(":/icons/serach.png"));
    connect(FindAction,SIGNAL(triggered()),this,SLOT(ShowFindDiag()));

    ReplaceAction = new QAction(tr("&Replace..."), this);
    ReplaceAction->setShortcut(QKeySequence::Replace);
    connect(ReplaceAction,SIGNAL(triggered()),this,SLOT(ShowReplaceDiag()));

    clearAction = new QAction(tr("&Clear"), this);
    clearAction->setStatusTip(tr("clear text edit..."));
    connect(clearAction,SIGNAL(triggered()),this,SLOT(clear_edit()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Close);
    exitAction->setStatusTip(tr("exit..."));
    exitAction->setIcon(QIcon(":/icons/shutdown.png"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exit_find_file()));

    AboutAuthor = new QAction(tr("&AboutAuthor"), this);
    connect(AboutAuthor,SIGNAL(triggered()),this,SLOT(AboutAuthorMessage()));

    AboutQt = new QAction(tr("&AboutQt"), this);
    AboutQt->setIcon(QIcon(":/icons/qt.png"));
    AboutQt->setShortcut(QKeySequence::HelpContents);
    AboutQt->setStatusTip(tr("show about Qt"));
    connect(AboutQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

    undoAction = new QAction(tr("&Undo"), this);
    undoAction->setIcon(QIcon(":/icons/edit-undo.png"));
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction,SIGNAL(triggered()),this->textedit,SLOT(undo()));

    redoAction = new QAction(tr("&Redo"), this);
    redoAction->setIcon(QIcon(":/icons/edit-redo.png"));
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction,SIGNAL(triggered()),this->textedit,SLOT(redo()));

    cutAction = new QAction(tr("&Cut"), this);
    cutAction->setIcon(QIcon(":/icons/edit-cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction,SIGNAL(triggered()),this->textedit,SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/icons/edit-copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction,SIGNAL(triggered()),this->textedit,SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/icons/edit-paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction,SIGNAL(triggered()),this->textedit,SLOT(paste()));

    FontSize = new QAction(tr("&Size"), this);
    connect(FontSize,SIGNAL(triggered(bool)),this,SLOT(FontSizeSet()));

    FontColor = new QAction(tr("&Color"), this);
    FontColor->setIcon(QIcon(":/icons/textcolor.png"));
    connect(FontColor,SIGNAL(triggered(bool)),this,SLOT(FontColorset()));
}

void MainWindow::createmenus()
{
    QMenu *File = this->menuBar()->addMenu(tr("&File"));
    File->addAction(openAction);
    File->addAction(saveAction);
    File->addAction(saveasAction);
    File->addSeparator();

    File->addAction(PrintTextAction);
    File->addAction(PDFAction);
    File->addSeparator();

    File->addAction(clearAction);
    File->addAction(exitAction);

    QMenu *Edit = this->menuBar()->addMenu(tr("&Edit"));
    Edit->addAction(undoAction);
    Edit->addAction(redoAction);
    Edit->addSeparator();

    Edit->addAction(cutAction);
    Edit->addAction(copyAction);
    Edit->addAction(pasteAction);

    Edit->addSeparator();
    Edit->addAction(FindAction);
    Edit->addAction(ReplaceAction);

    QMenu *Font = this->menuBar()->addMenu(tr("&Font"));
    Font->addAction(FontSize);
    Font->addAction(FontColor);

    QMenu *Help = this->menuBar()->addMenu(tr("&Help"));
    Help->addAction(AboutAuthor);
    Help->addAction(AboutQt);

}

void MainWindow::CreateToolBar()
{
    //file bar:包括打开，保存，查找和替换
    filebar = addToolBar("file");

    filebar->addAction(openAction);
    filebar->addAction(saveAction);
    filebar->addAction(saveasAction);
    filebar->addAction(FindAction);

    filebar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);      //Note:set open under iocn

    //doToolBar:包括撤销，回复，复制，粘贴
    doToolBar = addToolBar ("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addSeparator();
    doToolBar->addAction(redoAction);

    doToolBar->addAction(cutAction);
    doToolBar->addAction(copyAction);
    doToolBar->addAction(pasteAction);

    doToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);      //Note:set open under iocn

    //extendBar:包括打印 转换成PDF格式 退出
    extendBar = addToolBar("extend");
    extendBar->addAction(PrintTextAction);
    extendBar->addAction(PDFAction);
    extendBar->addSeparator();
    extendBar->addAction(exitAction);
    extendBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);      //Note:set open under iocn

    //字体工具条
    fontToolBar = addToolBar ("Font");
    fontToolBar->addWidget(this->fontlabel);
    fontToolBar->addWidget(this->fontComboBox);
    fontToolBar->addWidget(this->sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underBtn);
    fontToolBar->addAction(FontColor);
}

void MainWindow::open_file()
{
    path = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Text (*.*)"));

    if(!path.isEmpty())
    {
        QFile file(path);

        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("Read File"),tr("can't open file"));
            return;
        }

        QTextStream in(&file);

      //  textedit->setPlainText(in.readAll());
        textedit->setText(in.readAll());

        this->saveAction->setEnabled(true);
        connect(saveAction,SIGNAL(triggered()),this,SLOT(save_file()));
        file.close();


    }
    else
    {
        QMessageBox::warning(this,tr("Path"),tr("you didn't select anything"));
    }
}

void MainWindow::save_file()
{
    if(textedit->document()->isModified())
    {
        QFile file(path);
        if (!file.open (QIODevice::WriteOnly)) {
            QMessageBox::critical (this, tr("Error"), tr("Can't open filr success!"));
            return;
        }

        QTextStream outs(&file);
        outs << textedit->toPlainText ();
        outs.flush ();
        file.close ();

    }
    else
        save_file_As();




}

void MainWindow::save_file_As()
{
    //这个是getSaveFileName 不是getopenfilename
    QString path = QFileDialog::getSaveFileName(this, tr("Open File"),"/home",tr("Text (*.*)"));

    if(!path.isEmpty())
    {
        QFile file(path);

        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("save File"),tr("save file fail"));
            return;
        }

        QTextStream out(&file);

      //  textedit->setPlainText(in.readAll());
        out << textedit->toPlainText();
        file.close();

    }

}

//通过QPrinter，QPrintDialog来实现
void MainWindow::ShowPrintText()
{
    QPrinter printer;

    QPrintDialog printDialog(&printer,this);

    if(printDialog.exec())
    {
        //获得QTextEdit对象的文档
        QTextDocument *doc = textedit->document();
        doc->print (&printer);
    }

}

/*
Note:
-->QPrinter类可以用来将文档以pdf格式输出
-->getSaveFileName指定PDF
*/
void MainWindow::ExportToPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",QString(), "*.pdf");

    if (!fileName.isEmpty())
    {
         //如没有文件后缀时，添加后缀名pdf
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        //设置打印属
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        //开始打印
        textedit->document()->print(&printer);
    }

}

void MainWindow::exit_find_file()
{
    this->close();
}

void MainWindow::clear_edit()
{
    textedit->clear();
}

/*
    点击查找弹出查找对话框
*/
void MainWindow::ShowFindDiag()
{
    QDialog *FindDialog = new QDialog(this);
    QGridLayout *mainLayout = new QGridLayout(FindDialog);

    FindDialog->setWindowTitle("Find Diag");
    lineLabel = new QLabel(tr("Find(N): "));

    lineEdit = new QLineEdit;

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget (lineLabel);
    inputLayout->addWidget (lineEdit);

    findNextBtn = new QPushButton(tr("Find next"));
    cancelBtn = new QPushButton(tr("cancel"));
    connect (cancelBtn, SIGNAL(clicked(bool)), FindDialog, SLOT(reject()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget (findNextBtn);
    buttonLayout->addWidget (cancelBtn);

    upRadio = new QRadioButton(tr("Up"));
    downRadio = new QRadioButton(tr("Next"));

    UpDownGroup = new QButtonGroup(this);
    UpDownGroup->addButton(upRadio);
    UpDownGroup->addButton(downRadio);

    UpDownGroup->setId(this->upRadio,0);
    UpDownGroup->setId(this->downRadio,1);
    upRadio->setChecked(true);

    lowOrUpperBox = new QCheckBox(tr("Case sensitive(C)"));

    mainLayout->addLayout (inputLayout, 0, 0, 1, 3);
    mainLayout->addLayout (buttonLayout, 0, 4, 2, 1);
    mainLayout->addWidget (lowOrUpperBox, 2, 0);
    mainLayout->addWidget (upRadio, 2, 1);
    mainLayout->addWidget (downRadio, 2, 2);

    setLayout(mainLayout);

//    FindDialog->resize(200,100);
    FindDialog->show();

    connect (lineEdit, SIGNAL(textChanged(QString)), this, SLOT(ShowFindText()));
    connect (findNextBtn, SIGNAL(clicked(bool)), this, SLOT(find_file()));
}

void MainWindow::reject()
{

}

void MainWindow::ShowFindText()
{
    str = lineEdit->text();
}

/*
Note:
 -->QT RadionButton如何判断当前选中的是哪个RadionButton，先将RadionButton都加入QButtonGroup，然后通过QButtonGroup->setid给每个radiobutton设置id，检查的时候通过checkid就可以了
 -->检测CheckBox是否勾选上   if(lowOrUpperBox->checkState() == Qt::Checked)
 -->QTextDocument::FindCaseSensitively 区分大小写搜索
 -->QTextDocument::FindBackward 从下往上搜索
 -->QTextDocument::FindWholeWords 从上往下搜索

Bug:
-->想通过勾选lowOrUpperBox来区分大小写搜索，但是功能暂时还没有实现

*/
void MainWindow::find_file()
{
    int a = UpDownGroup->checkedId();

    if(!str.isEmpty())
    {

        if(a == 0)      //radiobutton up
        {
            /*
            if(lowOrUpperBox->checkState() == Qt::Checked)
            {
                if(textedit->find(str,QTextDocument::FindCaseSensitively))
                {
                    QPalette palette = textedit->palette();

                    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));

                    textedit->setPalette(palette);
                }
            }
            */
            if(textedit->find(str,QTextDocument::FindBackward))
            {
                QPalette palette = textedit->palette();

                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));

                textedit->setPalette(palette);
            }
        }
        else if(a == 1)     //radiobutton next
        {
            /*
            if(lowOrUpperBox->checkState() == Qt::Checked)
            {
                if(textedit->find(str,QTextDocument::FindCaseSensitively))
                {
                    QPalette palette = textedit->palette();

                    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));

                    textedit->setPalette(palette);
                }
            }
            */
            if(textedit->find(str,QTextDocument::FindWholeWords))
            {
                QPalette palette = textedit->palette();

                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));

                textedit->setPalette(palette);
            }
        }

    }
    else
    {
        return;
    }
}

void MainWindow::ShowReplaceDiag()
{
    QDialog *ReplaceDialog = new QDialog(this);
    QGridLayout *mainLayout = new QGridLayout(ReplaceDialog);

    ReplaceDialog->setWindowTitle("Replace Diag");

    lineLabel21 = new QLabel(tr("Find(N): "));
    lineEdit21 = new QLineEdit;

    lineLabel22 = new QLabel(tr("Replace(P): "));
    lineEdit22 = new QLineEdit;

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget (lineLabel21);
    inputLayout->addWidget (lineEdit21);

    QHBoxLayout *inputLayout2 = new QHBoxLayout;
    inputLayout2->addWidget (lineLabel22);
    inputLayout2->addWidget (lineEdit22);

    findNextBtn2 = new QPushButton(tr("Find next"));
    ReplaceBtn = new QPushButton(tr("Replace"));
    cancelBtn2 = new QPushButton(tr("Cancel"));
    connect (cancelBtn2, SIGNAL(clicked(bool)), ReplaceDialog, SLOT(reject()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget (findNextBtn2);
    buttonLayout->addWidget (ReplaceBtn);
    buttonLayout->addWidget (cancelBtn2);

    //lowOrUpperBox = new QCheckBox(tr("case sensitivity(C)"));

    mainLayout->addLayout (inputLayout, 0, 0, 1, 3);
    mainLayout->addLayout (inputLayout2, 1, 0, 1, 3);
    mainLayout->addLayout (buttonLayout, 0, 4, 3, 1);
    //mainLayout->addWidget (lowOrUpperBox, 2, 0);

    ReplaceDialog->show ();
    str2 = "";
    str3 = "";
    findjudge = false;
    connect (lineEdit21, SIGNAL(textChanged(QString)), this, SLOT(ShowReplaceText()));
    connect (lineEdit22, SIGNAL(textChanged(QString)), this, SLOT(ShowReplaceText2()));
    connect (findNextBtn2, SIGNAL(clicked(bool)), this, SLOT(ShowFindStr2()));
    connect (ReplaceBtn, SIGNAL(clicked(bool)), this, SLOT(ShowReplaceResult()));

}

void MainWindow::ShowReplaceText()
{
    str2 = lineEdit21->text ();
}

void MainWindow::ShowReplaceText2()
{
    str3 = lineEdit22->text ();
}

void MainWindow::ShowFindStr2()
{
    bool judge2;
    if (!str2.isEmpty ())
    {
            judge2 = textedit->find(str2,QTextDocument::FindWholeWords);
    }
    else
    {
        return;
    }
    if (!judge2) {
        QMessageBox::information (this, tr("Result"), tr("Don't search any thing"),
                                  QMessageBox::Yes);
    }
}

/*
  功能：全局搜索并替换
*/
void MainWindow::ShowReplaceResult()
{
    int judge2;
    QTextCursor textCur;

    if (!str2.isEmpty ())
    {
        judge2 = textedit->find (str2,QTextDocument::FindWholeWords);
        textCur = textedit->textCursor ();

    }
    else
    {
        return;
    }
    if (!judge2)
    {
        QMessageBox::information (this, tr("Result"), tr("No content to find"),
                                  QMessageBox::Yes);
    }
    else
    {
         textCur.insertText (str3);
    }
}

void MainWindow::FontSizeSet()
{

    bool ok;

    QFont Font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);

    if(ok)
    {
        textedit->setFont(Font);
    }

}

void MainWindow::FontColorset()
{
    QColor color(255,255,255);

    QColor colour = QColorDialog::getColor(color, this, "Select Color");

    if (!colour.isValid())
    {
        return;
    }

    QTextCharFormat format;
    format.setForeground(colour);

    QTextCursor cursor = textedit->textCursor();

    //检测光标是否选中了一段内容，如果是将光标处的字体格式修改并合并的文本中，达到修改颜色的效果
    if(cursor.hasSelection())
    {
        cursor.mergeCharFormat(format);
        textedit->mergeCurrentCharFormat(format);
    }

}

/*
    通过字条选择栏 选择后获得了QString
*/
void MainWindow::ShowFontComboBox(QString comboStr)
{
    QTextCharFormat fmt;            //创建一个QTextCharFormat对象
    fmt.setFontFamily(comboStr);

    QTextCursor cursor = textedit->textCursor();

    if(cursor.hasSelection())
    {
        cursor.mergeCharFormat(fmt);
        textedit->mergeCurrentCharFormat(fmt);
    }

}

void MainWindow::ShowSizeComboBox(QString ComboxValue)
{
    QTextCharFormat fmt;
    //设置字号
    fmt.setFontPointSize (ComboxValue.toFloat ());
    textedit->mergeCurrentCharFormat(fmt);

}

void MainWindow::ShowBoldBtn()
{
    QTextCharFormat fmt;
    //设置是否加粗
    fmt.setFontWeight (boldBtn->isChecked () ? QFont::Bold : QFont::Normal);
    textedit->mergeCurrentCharFormat (fmt);

}

void MainWindow::ShowitalicBtn()
{
    QTextCharFormat fmt;

    fmt.setFontItalic(italicBtn->isChecked());
    textedit->mergeCurrentCharFormat (fmt);

}

void MainWindow::ShowunderBtn()
{
    QTextCharFormat fmt;

    fmt.setFontUnderline(underBtn->isChecked());
    textedit->mergeCurrentCharFormat (fmt);
}

void MainWindow::AboutAuthorMessage()
{
    QMessageBox::about(this,tr("About author"),tr("About the author:author is a BIOS Engineer and study QT is purely a hobby!"));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::CTRL)
    {
        key_ctrl_release = 1;
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    key_ctrl_release = 0;
}

/*
Note:
-->重写函数wheelEvent()，按住ctrl + 鼠标滚轮 可以让字体放大缩小
-->如何判断ctrl是否按下，通过重写函数keyPressEvent和keyReleaseEvent

-->Bug:
-->只有滚动条达到顶端后者底端的时候才有效...
*/
void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0 && (key_ctrl_release == 1))
    {
        textedit->zoomIn();
    }
    else if((event->delta() < 0) && (key_ctrl_release == 1))
    {
        textedit->zoomOut();
    }
}
