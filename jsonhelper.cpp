#include "jsonhelper.h"

void JsonHelper::createJson(QString filePath, CustomScene *scene){
    qreal globalItemCounter = 0;
    QString globalItemCounterString = QString::number(globalItemCounter);

    QJsonObject recordObject;
    QJsonObject itemObject;

    foreach(QGraphicsItem *item, scene->items()){
        switch(item->type()){
            case 6: {break;} // LineItem of CustomTextItem do not have to save
            case 7: {break;} // images do not have to save
            case 8: {break;} // TextItem of CustomTextItem do not have to save
            case 65537: { // CustomRectangle
                CustomRectangle *rectangle = static_cast<CustomRectangle*>(item);

                QJsonArray posArray;
                posArray.push_back(rectangle->getPoint().x());
                posArray.push_back(rectangle->getPoint().y());

                itemObject.insert("Type", rectangle->type());
                itemObject.insert("Color", (qreal)rectangle->getColor().rgb());
                itemObject.insert("Height", rectangle->getHeight());
                itemObject.insert("Width", rectangle->getWidth());
                itemObject.insert("BorderSize", rectangle->getBorderSize());
                itemObject.insert("Position", posArray);
                recordObject.insert(globalItemCounterString, itemObject);

                globalItemCounter++;
                globalItemCounterString = QString::number(globalItemCounter);
                break;
            }
            case 65538: { // CustomCircle
                CustomCircle *circle = static_cast<CustomCircle*>(item);

                QJsonArray posArray;
                posArray.push_back(circle->getPoint().x());
                posArray.push_back(circle->getPoint().y());

                itemObject.insert("Type", circle->type());
                itemObject.insert("Color", (qreal)circle->getColor().rgb());
                itemObject.insert("Height", circle->getHeight());
                itemObject.insert("Width", circle->getWidth());
                itemObject.insert("BorderSize", circle->getBorderSize());
                itemObject.insert("Position", posArray);
                recordObject.insert(globalItemCounterString, itemObject);

                globalItemCounter++;
                globalItemCounterString = QString::number(globalItemCounter);
                break;
            }
            case 65539: { // CustomText
                CustomText *text = static_cast<CustomText*>(item);

                QJsonArray posArray;
                posArray.push_back(text->pos().x());
                posArray.push_back(text->pos().y());

                itemObject.insert("Type", text->type());
                itemObject.insert("Color", (qreal)text->getColor().rgb());
                itemObject.insert("Height", text->getHeight());
                itemObject.insert("Width", text->getWidth());
                itemObject.insert("Position", posArray);
                itemObject.insert("BorderSize", 0);
                itemObject.insert("Text", text->toPlainText());
                itemObject.insert("TextScale", text->getTextScale());
                recordObject.insert(globalItemCounterString, itemObject);

                globalItemCounter++;
                globalItemCounterString = QString::number(globalItemCounter);
                break;
            }
            case 65540: { // TextRectangle
                CustomTextRectangle *textRectangle = static_cast<CustomTextRectangle*>(item);

                QJsonArray posArray;
                posArray.push_back(textRectangle->getPoint().x());
                posArray.push_back(textRectangle->getPoint().y());

                itemObject.insert("Type", textRectangle->type());
                itemObject.insert("Color", (qreal)textRectangle->getColor().rgb());
                itemObject.insert("Height", textRectangle->getHeight());
                itemObject.insert("Width", textRectangle->getWidth());
                itemObject.insert("Position", posArray);
                itemObject.insert("BorderSize", textRectangle->getBorderSize());
                itemObject.insert("Text", textRectangle->getTextItem()->toPlainText());
                recordObject.insert(globalItemCounterString, itemObject);

                globalItemCounter++;
                globalItemCounterString = QString::number(globalItemCounter);
                break;
            }
            case 65541: { // TextCircle
                CustomTextCircle *textCircle = static_cast<CustomTextCircle*>(item);

                QJsonArray posArray;
                posArray.push_back(textCircle->getPoint().x());
                posArray.push_back(textCircle->getPoint().y());

                itemObject.insert("Type", textCircle->type());
                itemObject.insert("Color", (qreal)textCircle->getColor().rgb());
                itemObject.insert("Height", textCircle->getHeight());
                itemObject.insert("Width", textCircle->getWidth());
                itemObject.insert("Position", posArray);
                itemObject.insert("BorderSize", textCircle->getBorderSize());
                itemObject.insert("Text", textCircle->getTextItem()->toPlainText());
                recordObject.insert(globalItemCounterString, itemObject);

                globalItemCounter++;
                globalItemCounterString = QString::number(globalItemCounter);
                break;
            }
            case 65542: { // TextPoint
                CustomTextPoint *textPoint = static_cast<CustomTextPoint*>(item);

                QJsonArray posArray;
                posArray.push_back(textPoint->getPoint().x());
                posArray.push_back(textPoint->getPoint().y());

                itemObject.insert("Type", textPoint->type());
                itemObject.insert("Color", (qreal)textPoint->getColor().rgb());
                itemObject.insert("Height", textPoint->getHeight());
                itemObject.insert("Width", textPoint->getWidth());
                itemObject.insert("Position", posArray);
                itemObject.insert("BorderSize", textPoint->getBorderSize());
                itemObject.insert("Text", textPoint->getTextItem()->toPlainText());
                recordObject.insert(globalItemCounterString, itemObject);

                globalItemCounter++;
                globalItemCounterString = QString::number(globalItemCounter);
                break;
            }
            default: {
                qWarning() << "Something went wrong - jsonhelper/createJson";
                break;
            }
        }
    }

    // Save generell informations
    recordObject.insert("SaveDate", QJsonValue::fromVariant(QDate::currentDate()));
    recordObject.insert("SaveTime", QJsonValue::fromVariant(QTime::currentTime()));
    recordObject.insert("NumberOfItems", globalItemCounter);

    //QImage *image = new QImage(":/res/res/shark_splash.png");
    //QImage img{32, 32, QImage::Format_RGB32};
    auto pix = QPixmap::fromImage(scene->getImage());
    auto val = jsonValFromPixmap(pix);


    recordObject.insert("Image", val);

    //save to file
    QJsonDocument doc(recordObject);
    QFile file;
    file.setFileName(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream text(&file);
    text << doc.toJson();
    file.close();
}

void JsonHelper::readJson(QString filePath, CustomScene *scene, app::AppState *appState){  
    //handling the json file
    QString jsonInputString;
    QFile file;
    file.setFileName(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonInputString = file.readAll();
    file.close();

    //get strings
    QJsonDocument document = QJsonDocument::fromJson(jsonInputString.toUtf8());
    QJsonObject documentObject = document.object();


    auto pix2 = pixmapFrom(documentObject.value(QString("Image")));
    auto img2 = pix2.toImage();

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(img2));
    scene->addItem(item);

    qint8 numberOfItems = documentObject.value(QString("NumberOfItems")).toDouble();
    for(qint8 i = 0; i < numberOfItems; i++){
        QJsonValue value = documentObject.value(QString::number(i));
        QJsonObject item = value.toObject();
        //get data
        qreal color = item["Color"].toDouble();
        qreal height = item["Height"].toDouble();
        qreal width = item["Width"].toDouble();
        qreal borderSize = item["BorderSize"].toDouble();

        QJsonArray arrayPos = item["Position"].toArray();
        qreal posX = arrayPos[0].toDouble();
        qreal posY = arrayPos[1].toDouble();
        switch(item["Type"].toInt()){
            case 65537: { // CustomRectangle
                //create obj
                QBrush *brush = new QBrush();
                QColor colorObj = QColor();
                colorObj.setRgb(color);
                brush->setColor(colorObj);
                CustomRectangle *rectangle = new CustomRectangle(posX, posY, width, height, borderSize, *brush, appState);
                scene->addItem(rectangle);
                break;
            }
            case 65538: { // CustomCircle
                //create obj
                QBrush *brush = new QBrush();
                QColor colorObj = QColor();
                colorObj.setRgb(color);
                brush->setColor(colorObj);
                CustomCircle *circle = new CustomCircle(posX, posY, width, height, borderSize, *brush, appState);
                scene->addItem(circle);
                break;
            }
            case 65539: { // CustomText
                QString textString = item["Text"].toString();
                qreal textScale = item["TextScale"].toDouble();

                //create obj
                QColor colorObj = QColor();
                colorObj.setRgb(color);
                //brush->setColor(colorObj);
                CustomText *text = new CustomText(posX, posY, width, height, QBrush(colorObj), appState, textString, textScale);
                text->setText(textString);
                text->update();
                scene->addItem(text);
                break;
            }
            case 65540: { // TextRectangle
                QString textString = item["Text"].toString();

                //create obj
                QBrush *brush = new QBrush();
                QColor colorObj = QColor();
                colorObj.setRgb(color);
                brush->setColor(colorObj);
                CustomTextRectangle *textRectangle = new CustomTextRectangle(posX, posY, width, height, borderSize, *brush, appState, textString);
                scene->addItem(textRectangle);
                break;
            }
            case 65541: { // TextCircle
                QString textString = item["Text"].toString();

                //create obj
                QBrush *brush = new QBrush();
                QColor colorObj = QColor();
                colorObj.setRgb(color);
                brush->setColor(colorObj);
                CustomTextCircle *textCircle = new CustomTextCircle(posX, posY, width, height, borderSize, *brush, appState, textString);
                scene->addItem(textCircle);
                break;
            }
            case 65542: { // TextPoint
                QString textString = item["Text"].toString();

                //create obj
                QColor colorObj = QColor();
                colorObj.setRgb(color);
                CustomTextPoint *textPoint = new CustomTextPoint(posX, posY, width, height, borderSize, QBrush(colorObj), appState, textString);
                scene->addItem(textPoint);
                break;
            }
            default: {
                qWarning() << "Something went wrong - JsonHelper/readJson";
                break;
            }
        }
    }
}

QJsonValue JsonHelper::jsonValFromPixmap(const QPixmap &p) {
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG");
  auto const encoded = buffer.data().toBase64(); // convert to base 64
  return {QLatin1String(encoded)};
}

QPixmap JsonHelper::pixmapFrom(const QJsonValue &val) {
  auto const encoded = val.toString().toLatin1();
  QPixmap p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG"); // convert from base 64
  return p;
}
