#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include "app.h"
#include <QtPrintSupport/QPrinter> // print the canvas
#include <QtPrintSupport/QPrintDialog> // print the canvas
#include "toolmenuwatcher.h"

namespace Ui {
/**
 * @brief The MainWindow class
 * @details The MainWIndow class is the root/container for all Widgets.
 * It contains the UI.
 * Additionally, it provides out-of-box window behaviours and design.
 * @author Lars Teloeken
 * @version 1.0
 * @date 2019-01-27
*/
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow - the MainWindow
     * @param parent - the parent for the MainWindow
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief setApp - setter of the app
     * @param app - the current app
     */
    void setApp(app::App *app);
    /**
     * @brief getApp - getter of the app
     * @return - returned the current app
     */
    app::App *getApp();
    /**
     * @brief Destructor- destructor of the class
     */
    ~MainWindow();

signals:
    /**
     * @brief guiEnabledChanged - signal
     * @details This signal is called in MainWindow
     * it emit if the gui have to be enabled
     */
    void guiEnabledChanged();
    /**
     * @brief colorChanged - signal
     * @details This signal is called in MainWindow
     * it emits in MainWindow::on_pushButton_toolPropertieColor_clicked
     */
    void colorChanged(QColor);
    /**
     * @brief colorToolPropertieChanged - signal
     * @details This signal is called in MainWindow
     * it emits in MainWindow::on_pushButton_toolPropertieColor_clicked
     */
    void colorToolPropertieChanged(QColor);

private slots:
    /**
     * @brief on_actionImport_triggered - slot
     * @details This method is called in MainWindow::on_actionImport_triggered
     * it is importing an image to the canvas
     */
    void on_actionImport_triggered();
    /**
     * @brief resizeEvent - slot
     * @details This method is called in MainWindow::resizeEvent
     * it resize the canvas is the MainWindow is rezised
     */
    void resizeEvent(QResizeEvent *);
    /**
     * @brief on_actionExport_as_triggered - slot
     * @details This method is called in MainWindow::on_actionExport_as_triggered
     * it is exporting the canvas to a image
     */
    void on_actionExport_as_triggered();
    /**
     * @brief on_actionExit_triggered - slot
     * @details This method is called in MainWindow::on_actionExit_triggered
     * it is clos the application
     */
    void on_actionExit_triggered();
    /**
     * @brief on_actionPrint_triggered - slot
     * @details this methid is called in MainWindow::on_actionPrint_triggered
     * it print the canvas as pdf or on a physical printer
     */
    void on_actionPrint_triggered();
    /**
     * @brief on_actionSave_triggered - slot
     * @details This method is called in MainWindow::on_actionSave_triggered
     * it save the canvas to an project file
     */
    void on_actionSave_triggered();
    /**
     * @brief on_actionAbout_triggered - slot
     * @details This method is called in MainWindow::on_actionAbout_triggered
     * it is open the about message box
     */
    void on_actionAbout_triggered();
    /**
     * @brief on_actionNew_triggered - slot
     * @details This methid is called in MainWindow::on_actionNew_triggered
     * it creates a new canvas
     */
    void on_actionNew_triggered();
    /**
     * @brief onGuiEnabledChanged - slot
     * @details This method is called in MainWindow::onGuiEnabledChanged
     * it enables all GUI Elements
     */
    void onGuiEnabledChanged();
    /**
     * @brief on_actionOpen_triggered - slot
     * @details This method is called in MainWindow::on_actionOpen_triggered
     * it opens a project file
     */
    void on_actionOpen_triggered();
    /**
     * @brief on_toolButtonLeftClicked - slot
     * @param object - the current object
     * @details This method is called in MainWindow::on_toolButtonLeftClicked
     * it recognize if the user clicked on a tool button
     */
    void on_toolButtonLeftClicked(QObject* object);
    /**
     * @brief onItemSelectedUpdate - slot
     * @param color - the current color
     * @param height - the current height
     * @param text - the current text
     * @param borderSize - the current borderSize
     * @details This method is called in MainWindow::onItemSelectedUpdate
     * it updates the GUI if an item change their properties
     */
    void onItemSelectedUpdate(QColor color, qreal height, QString text, qreal borderSize);
    /**
     * @brief on_pushButton_toolPropertieColor_clicked - slot
     * @details This method is called in MainWindow::on_pushButton_toolPropertieColor_clicked
     * it opens a color picker and set the selected color
     */
    void on_pushButton_toolPropertieColor_clicked();

private:
    /**
     * @brief ui - the curreent ui
     */
    Ui::MainWindow *ui;
    /**
     * @brief m_app - member of the class
     * @details the current app
     */
    app::App *m_app;
    /**
     * @brief isCanvasActivated - member of the class
     * @details the current status of the activation of the canvas
     */
    bool isCanvasActivated;
    /**
     * @brief m_watcher - member of the class
     * @details the current watcher of the menu tool buttons
     */
    ToolMenuWatcher *m_watcher;
    /**
     * @brief initializeGuiElements - method
     * @details This method is called in MainWindow::initializeGuiElements
     * it initialize all gui elements
     */
    void initializeGuiElements();
    /**
     * @brief initializeConnections - method
     * @details This method is called in MainWindow::initializeConnections
     * it initialize all connections
     */
    void initializeConnections();
    /**
     * @brief setToolPropertiesInvisible - method
     * @details This method is called in MainWindow::setToolPropertiesInvisible
     * it set all tool propertie GUI elements invisible
     */
    void setToolPropertiesInvisible();
    /**
     * @brief setTextToolsGuiVisible - method
     * @details This method is called in MainWindow::setTextToolsGuiVisible
     * it set alls text tool gui elements visible
     */
    void setTextToolsGuiVisible();
    /**
     * @brief setToolsIconsUnselected - method
     * @details This method is called in MainWindow::setToolsIconsUnselected
     * it set all tool icons in the tool menu unselected (to grey)
     */
    void setToolsIconsUnselected();
};

#endif // MAINWINDOW_H
