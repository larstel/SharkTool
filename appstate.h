#ifndef APPSTATE_H
#define APPSTATE_H
#include <QAbstractGraphicsShapeItem>

namespace app {
    enum Tool {RECTANGLE, CIRCLE, TEXT, RECTANGLE_TEXT, CIRCLE_TEXT, POINT_TEXT, DELETE, SELECT, RESIZE, MOVE, PAINT, RENAME, BORDER_SIZE};

    /**
     * @brief The AppState class
     * @details This class contains important data
     * It says which item is selected an save all the items in an enum
     * Additionally it safe the basis properties of the items
     * @author Lars Telöken
     * @version 1.0
     * @date 2018-12-08
     */
    class AppState : public QObject
    {
        Q_OBJECT
    signals:
        /**
         * @brief widthChanged - signal
         * @param width - the width of an item
         * @details This method is called in AppState::setSelectedWidth
         * It emit the standard width of an item if it change
         */
        void widthChanged(qreal width);
        /**
         * @brief heightChanged - signal
         * @param height - the height of an item
         * @details This method is called in AppState::setSelectedHeight
         * It emit the standard height of an item if it change
         */
        void heightChanged(qreal height);
        /**
         * @brief toolChanged - signal
         * @param tool - the tool which is selected in the toolmenu
         * @details This Method is called in AppState::setSelectedHeight
         * It emit the selected tool if it change
         */
        void toolChanged(qint8 tool);
        /**
         * @brief signal_textScaleChanged - signal
         * @param textScale - the scale of a text
         * @details This method is called in AppState::setSelectedTextScale
         * It emit the selectd standard scale of a text if it change
         */
        void signal_textScaleChanged(qreal textScale);
    public slots:
        /**
         * @brief setSelectedTextScale - setter of selected text scale
         * @param textScale - the standard text scale of an item
         * @details This method is called in a connect in the MainWindow if the value of doubleSpinBox_toolPropertieTextScale changed
         * It is the standard value if an item is created
         */
        void setSelectedTextScale(qreal textScale);
        /**
         * @brief setSelectedText - setter of text
         * @param text - the standard text of an item
         * @details This method is called in a connect in the MainWindow if the value of lineEdit_text changed
         * It is the standard value if an item is created
         */
        void setSelectedText(QString text);
        /**
         * @brief setToolPropertieSelectedText - setter of selected text tool propertie
         * @param text - the text for an special tool
         * @details This method is called in a connect in the MainWindow if the value of lineEdit_toolPropertieText changed
         * It is the the value if an item exist and get changes
         */
        void setToolPropertieSelectedText(QString text);
        /**
         * @brief setToolPropertieStandardtextChecked - setter of standard text checked tool propertie
         * @param isChecked - a bool which is checked if the user wants a standard text for all items
         * @details This method is called in a connect in the MainWindow if the value of checkBox_toolPropertieStandardText changed
         * It is the value if an item exist and get changes
         */
        void setToolPropertieStandardtextChecked(bool isChecked);
        /**
         * @brief setToolPropertieSelectedBorder - setter of selected border size tool propertie
         * @param border - the new border size
         * @details It is the value if an item exist and get changes
         */
        void setToolPropertieSelectedBorder(qreal border);
        /**
         * @brief setSelectedTool - setter of selected tool
         * @param tool - which tool is selected
         * @details This method is called in MainWindow::on_toolButtonLeftClicked
         * It is the standard value if an item is created
         */
        void setSelectedTool(Tool tool);
        /**
         * @brief setSelectedTool - setter of selected tool
         * @param tool - which tool is selected
         * @details This method is called in MainWindow::on_toolButtonLeftClicked
         * It is the standard value if an item is created
         */
        void setSelectedTool(qint8 tool);
        /**
         * @brief setSelectedColor - setter of selected color
         * @param color - the current color
         * @details This method is called in a connect in the MainWindow, if the MainWindow emit an color change
         * It is the standard value if an item is created
         */
        void setSelectedColor(QColor color);
        /**
         * @brief setToolPropertieSelectedColor - setter of selected color tool propertie
         * @param color - the current color
         * @param This method is called in a connect in the MainWindow, if the MainWIndow emit an color change of the propertie color
         * It is the value if an item exist and get changes
         */
        void setToolPropertieSelectedColor(QColor color);
        /**
         * @brief setSelectedWidth - the setter of selected width
         * @param width - the current width
         * @details This method is called in a connect in the MainWindow, if doubleSpinBox_boundarySize change its value
         * It is the standard value if an item is created
         */        
        void setSelectedWidth(qreal width);
        /**
         * @brief setToolPropertieSelectedWidth - the setter of selected width tool propertie
         * @param width - the current width
         * @details This method is called in a connect in the MainWindow, if the doubleSpinBox_toolPropertieBoundarySize change its value
         * It is the value if an item exist and get changes
         */
        void setToolPropertieSelectedWidth(qreal width);
        /**
         * @brief setSelectedHeight - setter of selected height
         * @param height - the current height
         * @details This method is called in a connect in the MainWindow, if the doubleSpinBox_boundarySize change its value
         * It is the standard value if an item is created
         */
        void setSelectedHeight(qreal height);
        /**
         * @brief setToolPropertieSelectedHeight - setter of selected height tool propertie
         * @param height - the current height
         * @details This method is called in a connect in the MainWindow, if the doubleSpinBox_toolPropertieBoundarySize change its value
         * Ist is the value if an item exist an get changes
         */
        void setToolPropertieSelectedHeight(qreal height);
        /**
         * @brief setSelectedPosition - setter of selected position
         * @param selectedPosition - the current position
         * @details This method is called in a connect in the MainWindow, if the scene emit a mouse click
         * It is the standrad value if an item is created
         */
        void setSelectedPosition(QPointF *selectedPosition);

    private:
        /**
         * @brief m_toolPropertieSelectedBorder - member of the class
         * @details it contains the selected border size of an item, if it have to be changed
         */
        qreal m_toolPropertieSelectedBorder;
        /**
         * @brief m_selectedTool - member of the class
         * @details it contains the tool which is selected in the toolmenu
         */
        Tool m_selectedTool;
        /**
         * @brief m_selectedColor - member of the class
         * @details it contains the selected color
         */
        QColor m_selectedColor;
        /**
         * @brief m_selectedWidth - member of the class
         * @details it contains the selected width
         */
        qreal m_selectedWidth;
        /**
         * @brief m_toolPropertieSeletedWidth - member of the class
         * @details it contains the selected width of an item, if it have to be changed
         */
        qreal m_toolPropertieSeletedWidth;
        /**
         * @brief m_toolPropertieSelectedColor - member of the class
         * @details it contains the selected color of an item, if it have to be changed
         */
        QColor m_toolPropertieSelectedColor;
        /**
         * @brief m_toolPropertieSelectedText - member of the class
         * @details it contains the selected text of an item, if it have to be changed
         */
        QString m_toolPropertieSelectedText;
        /**
         * @brief m_selectedText - member of the class
         * @details it contains the selected text of an item, if it have to be changed
         * it is initialize with a string, which is used if the selected text is empty
         * functions in this application recognize this string and react special
         */
        QString m_selectedText = "none!@#.<>!!@#";
        /**
         * @brief m_selectedHeight - member of the class
         * @details it contains the standard height of an item
         */
        qreal m_selectedHeight;
        /**
         * @brief m_toolPropertieSelectedHeight - member of the class
         * @details it contains the selected height of an item, if it have to be changed
         */
        qreal m_toolPropertieSelectedHeight;
        /**
         * @brief m_selectedPosition - member of the class
         * @details it contains the selected position of an item
         */
        QPointF *m_selectedPosition;
        /**
         * @brief m_selectedShape - member of the class
         * @details it contains a boolean which says if the standard text can be used or not
         */
        bool m_isToolPropertieStandardTextChecked;
        /**
         * @brief m_SelectedTextScale - member of the class
         * @details it contains the  standard selected text scale
         */
        qreal m_SelectedTextScale;
    public:
        /**
         * @brief getSelectedTextScale - getter of selected text scale
         * @return - returned the selected text scale
         * this is the standard value if an item is created
         */
        qreal getSelectedTextScale();
        /**
         * @brief getSelectedText - getter of selected text
         * @return - returned the selected text
         * @details This method is called in every constructor of an item with text
         * this is the standard value if an item is created
         */
        QString getSelectedText();
        /**
         * @brief getToolPropertieSelectedText - getter of selected text tool propertie
         * @return - returned the selected text tool propertie
         * @details This method is called in every constructor of an item with text and their mousePressEvent
         * it is the value if an item exists and get changed
         */
        QString getToolPropertieSelectedText();
        /**
         * @brief getToolPropertieStandardtextChecked - getter of standard text checked tool propertie
         * @return - returned a boolean if the standard text can be used or not
         * @details This method is called in the mousePressEvent of every item which contains text
         */
        bool getToolPropertieStandardtextChecked();
        /**
         * @brief Constructor - the constructor of the class
         * @details It defined m_selectedTool, m_selectedColor, m_selectedWidth, m_selectedHeight, m_selectedPosition and m_SelectedTextScale
         * it is the value if an item exists and get changed
         */
        AppState();
        /**
         * @brief getSelectedTool - getter of selected tool
         * @return returned a tool
         * @details This method is called in MainWindow::on_actionExport_as_triggered and every items mouseClickEvent
         */
        Tool getSelectedTool();
        /**
         * @brief getSelectedColor - getter of selected color
         * @return returned a tool
         * @details This method is called in MainWindow::onGuiEnabledChanged, MainWindow::setTextToolsGuiVisible, MainWindow::on_toolButtonLeftClicked and App::onCanvasClicked
         * this is the standard value if an item is created
         */
        QColor getSelectedColor();
        /**
         * @brief getToolPropertieSelectedColor - getter of selected color tool propertie
         * @return - returned a color
         * @details This method is called in MainWindow::on_pushButton_toolPropertieColor_clicked, MainWindow::on_toolButtonLeftClicked and every items mousePressEvent
         * it is the value if an item exists and get changed
         */
        QColor getToolPropertieSelectedColor();
        /**
         * @brief getSelectedWidth - getter of selected width
         * @return returned a width
         * @details This method is called in MainWindow::initializeGuiElements
         * this is the standard value if an item is created
         */
        qreal getSelectedWidth();
        /**
         * @brief getToolPropertieSelectedWidth - getter of selected width tool propertie
         * @return - returned theselected width
         * it is the value if an item exists and get changed
         */
        qreal getToolPropertieSelectedWidth();
        /**
         * @brief getSelectedHeight - getter of selected height
         * @return returned a height
         * @details This method is called in MainWindow::on_toolButtonLeftClicked
         * this is the standard value if an item is created
         */
        qreal getSelectedHeight();
        /**
         * @brief getToolPropertieSelectedHeight - getter of selected height tool propertie
         * @return - returned the selected height
         * @details This method is called in MainWindow::on_toolButtonLeftClicked
         * it is the value if an item exists and get changed
         */
        qreal getToolPropertieSelectedHeight();
        /**
         * @brief getSelectedPosition - getter of selected position
         * @return returned a height
         * @details This method is called in App::onCanvasClicked
         * this is the standard value if an item is created
         */
        QPointF *getSelectedPosition();

        /**
         * @brief Destructor - the destructor of the class
         */
        ~AppState();
    };
}
#endif // APPSTATE_H
