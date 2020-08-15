#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeGuiElements(); //Startsettings
    initializeConnections(); //SIGNALS AND SLOTS
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->m_app;
    delete this->m_watcher;
}

//Initialization
void MainWindow::initializeConnections()
{
    connect(ui->doubleSpinBox_toolPropertieBoundarySize, SIGNAL(valueChanged(qreal)), m_app->getAppState(), SLOT(setToolPropertieSelectedWidth(qreal)));
    connect(ui->doubleSpinBox_toolPropertieBoundarySize, SIGNAL(valueChanged(qreal)), m_app->getAppState(), SLOT(setToolPropertieSelectedHeight(qreal)));
    connect(ui->doubleSpinBox_boundarySize, SIGNAL(valueChanged(qreal)), m_app->getAppState(), SLOT(setSelectedWidth(qreal)));
    connect(ui->doubleSpinBox_boundarySize, SIGNAL(valueChanged(qreal)), m_app->getAppState(), SLOT(setSelectedHeight(qreal)));
    connect(ui->doubleSpinBox_toolPropertieTextScale, SIGNAL(valueChanged(qreal)), m_app->getAppState(), SLOT(setSelectedTextScale(qreal)));
    connect(this->m_app->getScene(), SIGNAL(mouseClicked(QPointF*)), this->m_app->getAppState(), SLOT(setSelectedPosition(QPointF*)));
    connect(this->m_app->getScene(), SIGNAL(mouseClicked(QPointF*)), this->m_app, SLOT(onCanvasClicked()));
    connect(this, SIGNAL(colorChanged(QColor)), this->m_app->getAppState(), SLOT(setSelectedColor(QColor)));
    connect(this, SIGNAL(colorToolPropertieChanged(QColor)), this->m_app->getAppState(), SLOT(setToolPropertieSelectedColor(QColor)));
    connect(this, SIGNAL(guiEnabledChanged()),this,SLOT(onGuiEnabledChanged()));
    connect(this->m_app->getScene(), SIGNAL(deleteKeyPressed()), this->m_app, SLOT(removeSelectedItems()));
    connect(ui->doubleSpinBox_toolPropertieBoundarySize, SIGNAL(valueChanged(qreal)), this->m_app, SLOT(onSelectedItemSizeChanged(qreal)));
    connect(ui->doubleSpinBox_toolPropertieBorderSize, SIGNAL(valueChanged(qreal)), this->m_app, SLOT(onSelectedItemBorderSizeChanged(qreal)));
    connect(m_watcher, SIGNAL(signal_toolButtonLeftClicked(QObject*)), this, SLOT(on_toolButtonLeftClicked(QObject*)));
    connect(this->m_app->getScene(), SIGNAL(mouseReleasedOnCustomScene()), this->m_app, SLOT(onItemSelected()));
    connect(this->m_app, SIGNAL(signal_selectedItemUpdate(QColor, qreal, QString, qreal)), this, SLOT(onItemSelectedUpdate(QColor, qreal, QString, qreal)));
    connect(ui->checkBox_toolPropertieStandardText, SIGNAL(toggled(bool)), this->m_app->getAppState(), SLOT(setToolPropertieStandardtextChecked(bool)));
    connect(ui->checkBox_toolPropertieStandardText, SIGNAL(toggled(bool)), ui->lineEdit_toolPropertieText, SLOT(setEnabled(bool)));
    connect(ui->lineEdit_toolPropertieText, SIGNAL(textChanged(QString)), this->m_app->getAppState(), SLOT(setToolPropertieSelectedText(QString)));
    connect(ui->lineEdit_text, SIGNAL(textChanged(QString)), this->m_app->getAppState(), SLOT(setSelectedText(QString)));
}

void MainWindow::initializeGuiElements()
{
    setWindowTitle("SHARK Tool");
    this->m_app = new app::App(); //creates a new App Object
    setWindowIcon(QIcon(":/res/icons/res/icons/sharkIcon.png"));

    ui->canvas->setScene(this->m_app->getScene()); //set the Scene
    this->isCanvasActivated = false;

    //DISABLE
    ui->canvas->setEnabled(false); //disable canvasqpixmap
    ui->dockWidget_toolbox->setEnabled(false); //disable tool groupbox
    ui->dockWidget_properties->setEnabled(false);
    ui->pushButton_toolPropertieColor->setEnabled(false);
    ui->lineEdit_text->setEnabled(false);
    ui->lineEdit_toolPropertieText->setEnabled(false);

    //set standard parameter to spinBox_width/height
    ui->doubleSpinBox_toolPropertieBoundarySize->setValue(this->m_app->getAppState()->getSelectedWidth());

    //set checked
    ui->menuWindow->addAction(ui->dockWidget_toolbox->toggleViewAction());
    ui->menuWindow->addAction(ui->dockWidget_properties->toggleViewAction());
    ui->menuWindow->addAction(ui->mainToolBar->toggleViewAction());

    //deactivate tool properties
    setToolPropertiesInvisible();

    //
    QPixmap pix(":/1.png");
    ui->label_denied->setStyleSheet("border-image:url(:/res/icons/tools/res/icons/tools/denied.png);");
    ui->label_denied->setPixmap(pix);

    //TEST
    m_watcher = new ToolMenuWatcher(this);

    ui->pushButton_rectangleTool->installEventFilter(m_watcher);
    ui->pushButton_rectangleTool->setStyleSheet("border: none");
    ui->pushButton_rectangleTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangle.png"));

    ui->pushButton_circleTool->installEventFilter(m_watcher);
    ui->pushButton_circleTool->setStyleSheet("border: none");
    ui->pushButton_circleTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/circle.png"));

    ui->pushButton_textTool->installEventFilter(m_watcher);
    ui->pushButton_textTool->setStyleSheet("border: none");
    ui->pushButton_textTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/text.png"));

    ui->pushButton_rectangleTextTool->installEventFilter(m_watcher);
    ui->pushButton_rectangleTextTool->setStyleSheet("border: none");
    ui->pushButton_rectangleTextTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangleText.png"));

    ui->pushButton_circleTextTool->installEventFilter(m_watcher);
    ui->pushButton_circleTextTool->setStyleSheet("border: none");
    ui->pushButton_circleTextTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/circleText.png"));

    ui->pushButton_pointTextTool->installEventFilter(m_watcher);
    ui->pushButton_pointTextTool->setStyleSheet("border: none");
    ui->pushButton_pointTextTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/pointText.png"));

    ui->pushButton_delete->installEventFilter(m_watcher);
    ui->pushButton_delete->setStyleSheet("border: none");
    ui->pushButton_delete->setIcon(QIcon(":/res/icons/tools/res/icons/tools/trash.png"));

    ui->pushButton_select->installEventFilter(m_watcher);
    ui->pushButton_select->setStyleSheet("border: none");
    ui->pushButton_select->setIcon(QIcon(":/res/icons/tools/res/icons/tools/select.png"));

    ui->pushButton_move->installEventFilter(m_watcher);
    ui->pushButton_move->setStyleSheet("border: none");
    ui->pushButton_move->setIcon(QIcon(":/res/icons/tools/res/icons/tools/move.png"));

    ui->pushButton_borderSize->installEventFilter(m_watcher);
    ui->pushButton_borderSize->setStyleSheet("border: none");
    ui->pushButton_borderSize->setIcon(QIcon(":/res/icons/tools/res/icons/tools/borderSize.png"));

    ui->pushButton_paint->installEventFilter(m_watcher);
    ui->pushButton_paint->setStyleSheet("border: none");
    ui->pushButton_paint->setIcon(QIcon(":/res/icons/tools/res/icons/tools/paint.png"));

    ui->pushButton_rename->installEventFilter(m_watcher);
    ui->pushButton_rename->setStyleSheet("border: none");
    ui->pushButton_rename->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rename.png"));

    ui->pushButton_resize->installEventFilter(m_watcher);
    ui->pushButton_resize->setStyleSheet("border: none");
    ui->pushButton_resize->setIcon(QIcon(":/res/icons/tools/res/icons/tools/resize.png"));

    //set status tip
    ui->actionNew->setStatusTip(tr("Create new image"));
    ui->actionOpen->setStatusTip(tr("Open project"));
    ui->actionSave->setStatusTip(tr("Save project"));
    ui->actionImport->setStatusTip(tr("Import picture"));
    ui->actionExport_as->setStatusTip(tr("Export as image"));
    ui->actionPrint->setStatusTip(tr("Print image"));

    ui->actionAbout->setStatusTip(tr("Shows the application's About box"));
    ui->actionExit->setStatusTip(tr("Quit the application"));

    ui->pushButton_rectangleTool->setStatusTip(tr("Draw a rectangle"));
    ui->pushButton_circleTool->setStatusTip(tr("Draw a circle"));
    ui->pushButton_textTool->setStatusTip(tr("Place a text"));
    ui->pushButton_rectangleTextTool->setStatusTip(tr("Draw a rectangle with text"));
    ui->pushButton_circleTextTool->setStatusTip(tr("Draw a circle with text"));
    ui->pushButton_pointTextTool->setStatusTip(tr("Draw a point with text"));
    ui->pushButton_select->setStatusTip(tr("Select items"));
    ui->pushButton_move->setStatusTip(tr("Moves an item"));
    ui->pushButton_delete->setStatusTip(tr("Delete an item"));
    ui->pushButton_paint->setStatusTip(tr("Repaint an item"));
    ui->pushButton_borderSize->setStatusTip(tr("Resize the border of item"));
    ui->pushButton_rename->setStatusTip(tr("Rename an item with text"));
    ui->pushButton_resize->setStatusTip(tr("Resize an item"));
    ui->doubleSpinBox_boundarySize->setStatusTip(tr("Set the items size"));
    ui->doubleSpinBox_toolPropertieBoundarySize->setStatusTip(tr("Set the items size"));
    ui->doubleSpinBox_toolPropertieBorderSize->setStatusTip(tr("Set the items border size"));
    ui->doubleSpinBox_toolPropertieTextScale->setStatusTip(tr("Set the items text scale"));
    ui->lineEdit_text->setStatusTip(tr("Set the text"));
    ui->lineEdit_toolPropertieText->setStatusTip(tr("set the text"));
    ui->pushButton_toolPropertieColor->setStatusTip(tr("Set the items color"));
    ui->checkBox_toolPropertieStandardText->setToolTip(tr("Enable standardtext"));
    ui->label_denied->setStatusTip(tr("No tool properties"));

    //set shortcuts
    ui->actionNew->setShortcuts(QKeySequence::New);
    ui->actionOpen->setShortcuts(QKeySequence::Open);
    ui->actionSave->setShortcuts(QKeySequence::Save);
    ui->actionPrint->setShortcuts(QKeySequence::Print);
    ui->actionExit->setShortcuts(QKeySequence::Quit);
}

void MainWindow::onGuiEnabledChanged()
{
    //set standard color
    isCanvasActivated = true;
    ui->canvas->setEnabled(true); //disable canvas
    ui->dockWidget_toolbox->setEnabled(true); //disable tool groupbox
    ui->dockWidget_properties->setEnabled(true);
    ui->pushButton_toolPropertieColor->setEnabled(true);

    //set standard color
    QString qss = QString("background-color: %1").arg(this->m_app->getAppState()->getSelectedColor().name());
    ui->pushButton_toolPropertieColor->setStyleSheet(qss);

    //set the standard toolbutton on
    ui->pushButton_rectangleTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangleSelected.png"));

    //set standard Cursor
    ui->canvas->setCursor(Qt::CrossCursor);

    on_toolButtonLeftClicked(ui->pushButton_rectangleTool);
}

void MainWindow::onItemSelectedUpdate(QColor color, qreal height, QString text, qreal borderSize){
    QString qss = QString("background-color: %1").arg(color.name());
    ui->pushButton_toolPropertieColor->setStyleSheet(qss);
    ui->doubleSpinBox_toolPropertieBoundarySize->setValue(height);
    ui->doubleSpinBox_toolPropertieBorderSize->setValue(borderSize);
    if(text.contains("none!@#.<>!!@#", Qt::CaseInsensitive)==true){
        ui->lineEdit_toolPropertieText->setEnabled(false);
    } else {
        ui->lineEdit_toolPropertieText->setText(text);
    }
}

void MainWindow::on_actionImport_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open Image File", QDir::currentPath());
    if (!filePath.isNull())
    {        
        QImage *image = new QImage(filePath);

        m_app->getScene()->setImage(*image);//for json

        qreal height = image->height();
        qreal width = image->width();
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
        this->m_app->setGraphicsPixmapItem(item);

        if(width <= height){
            ui->canvas->setFixedHeight(height/(width/ui->canvas->width()));
        } else if(height > width){
            ui->canvas->setFixedWidth(width/(height/ui->canvas->height()));
        }
        ui->canvas->fitInView(item, Qt::KeepAspectRatio);
        ui->canvas->setSceneRect(0, 0, width, height);
        ui->canvas->scene()->addItem(item);
        ui->canvas->show();

        //ENABLE
        //isCanvasActivated = true;
        emit guiEnabledChanged();
        ui->canvas->setEnabled(true); //enable canvas
        ui->dockWidget_toolbox->setEnabled(true); //enable tool groupbox
        ui->dockWidget_properties->setEnabled(true);
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
   if(this->m_app->getGraphicsPixmapItem() != nullptr){
       ui->canvas->setSceneRect(0,0,800,1000);
       ui->canvas->fitInView(this->m_app->getGraphicsPixmapItem(),Qt::KeepAspectRatio);
   }
}

void MainWindow::on_actionExport_as_triggered()
{
    if(this->isCanvasActivated){
        QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);JPEG (*.JPEG);PNG (*.png)");
            if (!fileName.isNull())
            {
                QPixmap pixMap = this->ui->canvas->grab();
                pixMap.save(fileName);
            }
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is nothing to save!");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::on_pushButton_toolPropertieColor_clicked()
{
    QPushButton *pushButtonColor = qobject_cast<QPushButton*>(sender());
    QColorDialog *colorDialog = new QColorDialog(this->m_app->getAppState()->getToolPropertieSelectedColor(), this);
    QColor color;
    color = colorDialog->getColor();
    if(color.isValid()){
        if(this->m_app->getAppState()->getSelectedTool() == app::RECTANGLE){
            emit colorChanged(color);
        } else if(this->m_app->getAppState()->getSelectedTool() == app::PAINT){
            emit colorToolPropertieChanged(color);
        }
        QString qss = QString("background-color: %1").arg(this->m_app->getAppState()->getToolPropertieSelectedColor().name());
        pushButtonColor->setStyleSheet(qss);
    }
}

void MainWindow::on_actionPrint_triggered()
{
    if(this->isCanvasActivated){
        QPrinter printer;
        if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
            QPainter painter(&printer);
            painter.setRenderHint(QPainter::Antialiasing);
            ui->canvas->scene()->render(&painter);
        }
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is nothing to print!");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_actionSave_triggered()
{
    QString filePath= QFileDialog::getSaveFileName(this, "save project", QCoreApplication::applicationDirPath(), "SHARKSON (*.sharkson)");
        if (!filePath.isNull())
        {
            this->m_app->createJson(filePath);
        }
}

void MainWindow::on_actionAbout_triggered()
{    
    QMessageBox messageBox;
    messageBox.setIconPixmap(QPixmap(":/res/icons/res/icons/sharkIcon.png"));
    messageBox.about(this, tr("About SHARK Tool"), tr("With <b>SHARK Tool</b> (<b>S</b>imple <b>H</b>ighlight & m<b>ARK</b>) you can highlight and mark an image."));
}

void MainWindow::on_actionNew_triggered()
{
    emit guiEnabledChanged();
    if(!ui->canvas->scene()->items().isEmpty()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("New");
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Save: {
                on_actionExport_as_triggered();
                ui->canvas->scene()->clear();
                break;
            }
            case QMessageBox::Discard: {
                ui->canvas->scene()->clear();
                break;
            }
            case QMessageBox::Cancel: {
                // Cancel was clicked
                break;
            }
            default: {
                qWarning() << "Something went wrong - mainwindow/on_actionNew_triggered";
                break;
            }
        }
    } else {
        ui->canvas->scene()->clear();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open project", QDir::currentPath());
        if (!filePath.isNull())
        {
            this->m_app->readJson(filePath);
        }
}

void MainWindow::setToolPropertiesInvisible(){
    ui->label_toolPropertieBoundarySize->setVisible(false);
    ui->doubleSpinBox_toolPropertieBoundarySize->setVisible(false);
    ui->doubleSpinBox_boundarySize->setVisible(false);
    ui->label_toolPropertieBorderSize->setVisible(false);
    ui->doubleSpinBox_toolPropertieBorderSize->setVisible(false);
    ui->label_toolPropertieText->setVisible(false);
    ui->lineEdit_toolPropertieText->setVisible(false);
    ui->label_toolPropertieColor->setVisible(false);
    ui->pushButton_toolPropertieColor->setVisible(false);
    ui->label_denied->setVisible(false);
    ui->checkBox_toolPropertieStandardText->setVisible(false);
    ui->lineEdit_text->setVisible(false);
    ui->label_toolPropertieTextScale->setVisible(false);
    ui->doubleSpinBox_toolPropertieTextScale->setVisible(false);
}

void MainWindow::setTextToolsGuiVisible(){
    ui->label_toolPropertieBoundarySize->setVisible(true);
    ui->doubleSpinBox_boundarySize->setVisible(true);
    ui->label_toolPropertieBorderSize->setVisible(true);
    ui->doubleSpinBox_toolPropertieBorderSize->setVisible(true);
    ui->label_toolPropertieColor->setVisible(true);
    ui->pushButton_toolPropertieColor->setVisible(true);
    ui->label_toolPropertieText->setVisible(true);
    ui->lineEdit_text->setVisible(true);

    QString qss2 = QString("background-color: %1").arg(this->m_app->getAppState()->getSelectedColor().name());
    ui->pushButton_toolPropertieColor->setStyleSheet(qss2);
}

void MainWindow::setToolsIconsUnselected(){
    ui->pushButton_pointTextTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/pointText.png"));
    ui->pushButton_circleTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/circle.png"));
    ui->pushButton_textTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/text.png"));
    ui->pushButton_rectangleTextTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangleText.png"));
    ui->pushButton_circleTextTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/circleText.png"));
    ui->pushButton_rectangleTool->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangle.png"));
    ui->pushButton_delete->setIcon(QIcon(":/res/icons/tools/res/icons/tools/trash.png"));
    ui->pushButton_select->setIcon(QIcon(":/res/icons/tools/res/icons/tools/select.png"));
    ui->pushButton_move->setIcon(QIcon(":/res/icons/tools/res/icons/tools/move.png"));
    ui->pushButton_borderSize->setIcon(QIcon(":/res/icons/tools/res/icons/tools/borderSize.png"));
    ui->pushButton_paint->setIcon(QIcon(":/res/icons/tools/res/icons/tools/paint.png"));
    ui->pushButton_rename->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rename.png"));
    ui->pushButton_resize->setIcon(QIcon(":/res/icons/tools/res/icons/tools/resize.png"));
}

void MainWindow::on_toolButtonLeftClicked(QObject *object)
{
    setToolPropertiesInvisible();

    QPushButton *button = qobject_cast<QPushButton*>(object);

    setToolsIconsUnselected();

    if(button == ui->pushButton_circleTool){
        m_app->getAppState()->setSelectedTool(app::CIRCLE);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/circleSelected.png"));
        ui->canvas->setCursor(Qt::CrossCursor);

        ui->label_toolPropertieBoundarySize->setVisible(true);
        ui->doubleSpinBox_boundarySize->setVisible(true);
        ui->label_toolPropertieBorderSize->setVisible(true);
        ui->doubleSpinBox_toolPropertieBorderSize->setVisible(true);
        ui->label_toolPropertieColor->setVisible(true);
        ui->pushButton_toolPropertieColor->setVisible(true);

        QString qss2 = QString("background-color: %1").arg(this->m_app->getAppState()->getSelectedColor().name());
        ui->pushButton_toolPropertieColor->setStyleSheet(qss2);

        ui->doubleSpinBox_boundarySize->setValue(this->m_app->getAppState()->getSelectedHeight());
    } else if(button == ui->pushButton_circleTextTool){
        m_app->getAppState()->setSelectedTool(app::CIRCLE_TEXT);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/circleTextSelected.png"));
        ui->canvas->setCursor(Qt::CrossCursor);

        setTextToolsGuiVisible();
    } else if(button == ui->pushButton_pointTextTool){
        m_app->getAppState()->setSelectedTool(app::POINT_TEXT);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/pointTextSelected.png"));
        ui->canvas->setCursor(Qt::CrossCursor);

        setTextToolsGuiVisible();
    } else if(button == ui->pushButton_rectangleTextTool){
        m_app->getAppState()->setSelectedTool(app::RECTANGLE_TEXT);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangleTextSelected.png"));
        ui->canvas->setCursor(Qt::CrossCursor);

        setTextToolsGuiVisible();
    } else if(button == ui->pushButton_rectangleTool){
        m_app->getAppState()->setSelectedTool(app::RECTANGLE);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/rectangleSelected.png"));
        ui->canvas->setCursor(Qt::CrossCursor);

        ui->label_toolPropertieBoundarySize->setVisible(true);
        ui->doubleSpinBox_boundarySize->setVisible(true);
        ui->label_toolPropertieBorderSize->setVisible(true);
        ui->doubleSpinBox_toolPropertieBorderSize->setVisible(true);
        ui->label_toolPropertieColor->setVisible(true);
        ui->pushButton_toolPropertieColor->setVisible(true);

        QString qss2 = QString("background-color: %1").arg(this->m_app->getAppState()->getSelectedColor().name());
        ui->pushButton_toolPropertieColor->setStyleSheet(qss2);

        ui->doubleSpinBox_boundarySize->setValue(this->m_app->getAppState()->getSelectedHeight());
    } else if(button == ui->pushButton_textTool){
        m_app->getAppState()->setSelectedTool(app::TEXT);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/textSelected.png"));
        ui->canvas->setCursor(Qt::CrossCursor);

        ui->label_toolPropertieText->setVisible(true);
        ui->lineEdit_text->setVisible(true);
        ui->label_toolPropertieTextScale->setVisible(true);
        ui->doubleSpinBox_toolPropertieTextScale->setVisible(true);

    } else if(button == ui->pushButton_delete){
        m_app->getAppState()->setSelectedTool(app::DELETE);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/trashSelected.png"));
        ui->canvas->setCursor(Qt::PointingHandCursor);

        ui->label_denied->setVisible(true);
    } else if(button == ui->pushButton_select){
        m_app->getAppState()->setSelectedTool(app::SELECT);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/selectSelected.png"));
        ui->canvas->setCursor(Qt::ArrowCursor);

        ui->label_denied->setVisible(true);
    } else if(button == ui->pushButton_move){
        m_app->getAppState()->setSelectedTool(app::MOVE);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/moveSelected.png"));
        ui->canvas->setCursor(Qt::SizeAllCursor);

        ui->label_denied->setVisible(true);
    } else if(button == ui->pushButton_rename){
        m_app->getAppState()->setSelectedTool(app::RENAME);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/renameSelected.png"));
        ui->canvas->setCursor(Qt::IBeamCursor);

        ui->label_toolPropertieText->setVisible(true);
        ui->lineEdit_toolPropertieText->setVisible(true);
        ui->checkBox_toolPropertieStandardText->setVisible(true);
    } else if(button == ui->pushButton_paint){
        m_app->getAppState()->setSelectedTool(app::PAINT);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/paintSelected.png"));
        ui->canvas->setCursor(Qt::PointingHandCursor);

        ui->label_toolPropertieColor->setVisible(true);
        ui->pushButton_toolPropertieColor->setVisible(true);

        QString qss = QString("background-color: %1").arg(this->m_app->getAppState()->getToolPropertieSelectedColor().name());
        ui->pushButton_toolPropertieColor->setStyleSheet(qss);
    } else if(button == ui->pushButton_borderSize){
        m_app->getAppState()->setSelectedTool(app::BORDER_SIZE);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/borderSizeSelected.png"));
        ui->canvas->setCursor(Qt::SplitHCursor);

        ui->label_toolPropertieBorderSize->setVisible(true);
        ui->doubleSpinBox_toolPropertieBorderSize->setVisible(true);
    } else if(button == ui->pushButton_resize){
        m_app->getAppState()->setSelectedTool(app::RESIZE);
        button->setIcon(QIcon(":/res/icons/tools/res/icons/tools/resizeSelected.png"));
        ui->canvas->setCursor(Qt::SizeFDiagCursor);

        ui->label_toolPropertieBoundarySize->setVisible(true);
        ui->doubleSpinBox_toolPropertieBoundarySize->setVisible(true);

        ui->doubleSpinBox_toolPropertieBoundarySize->setValue(this->m_app->getAppState()->getToolPropertieSelectedHeight());
    }
}
