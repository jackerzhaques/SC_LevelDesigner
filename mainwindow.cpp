#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup the sprite containers
    for(int i = 0; i < Sprite::N_TYPES; i++){
        QList<QList<Sprite*>> typeList;
        for(int j = 0; j < Sprite::N_DIRS; j++){
            QList<Sprite*> dirList;
            typeList.append(dirList);
        }
        this->Sprites.append(typeList);
    }

    this->FullSheetView         = new GraphicsView();
    this->SpriteEditView        = new GraphicsView();
    this->SpritePreview         = new GraphicsView();

    this->FullSheetView->setMaximumSize(300,300);
    this->SpriteEditView->setMaximumSize(300,300);
    this->SpritePreview->setMaximumSize(300,300);
    this->FullSheetView->setMinimumSize(250,250);
    this->SpriteEditView->setMinimumSize(250,250);
    this->SpritePreview->setMinimumSize(250,250);

    this->SpritesheetScene      = new QGraphicsScene();
    this->AnimatedSpriteScene   = new QGraphicsScene();

    this->FullSheetView->setScene(this->SpritesheetScene);
    this->SpriteEditView->setScene(this->SpritesheetScene);
    this->SpritePreview->setScene(this->AnimatedSpriteScene);
    this->FullSheetView->setMouseTracking(true);
    this->SpriteEditView->setMouseTracking(true);

    this->SpritesheetSelection = new QGraphicsRectItem();
    this->SpritesheetSelection->setRect(0,0,100,100);

    this->Anchor = new QGraphicsEllipseItem();
    this->Anchor->setRect(85,85,10,10);
    this->Anchor->setBrush(QBrush(Qt::red));

    this->Origin = new QGraphicsEllipseItem();
    this->Origin->setRect(45,95,10,10);
    this->Origin->setBrush(QBrush(Qt::blue));

    this->SpritesheetScene->addItem(this->SpritesheetSelection);
    this->SpritesheetScene->addItem(this->Anchor);
    this->SpritesheetScene->addItem(this->Origin);

    this->ui->SpriteMakerTab->layout()->addWidget(this->FullSheetView);
    this->ui->SpriteMakerTab->layout()->addWidget(this->SpriteEditView);
    this->ui->SpriteMakerTab->layout()->addWidget(this->SpritePreview);

    this->AnimatedSprite = new QGraphicsPixmapItem();
    this->AnimatedSpriteScene->addItem(this->AnimatedSprite);

    this->AnimationOrigin = new QGraphicsEllipseItem();
    this->AnimatedSpriteScene->addItem(this->AnimationOrigin);
    this->AnimationOrigin->setRect(0,0,15,15);
    this->AnimationOrigin->setBrush(QBrush(Qt::blue));
    this->SetEllipseObjectPos(this->AnimationOrigin, QPointF(0,0));

    connect(this->FullSheetView, SIGNAL(mousePressed(QPoint)), this, SLOT(FullSpritesheetClicked(QPoint)));
    connect(this->SpriteEditView, SIGNAL(mousePressed(QPoint)), this, SLOT(ZoomedSpritesheetClicked(QPoint)));
    connect(this->FullSheetView, SIGNAL(mouseMoved(QPointF)), this, SLOT(FullSpritesheetMouseMoved(QPointF)));
    connect(this->SpriteEditView, SIGNAL(mouseMoved(QPointF)), this, SLOT(ZoomedSpritesheetMouseMoved(QPointF)));
    this->SpriteEditView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->SpriteEditView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->SpritePreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->SpritePreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->AnimationTimer = new QTimer(this);
    connect(this->AnimationTimer, SIGNAL(timeout()), this, SLOT(AdvanceAnimationFrame()));
    this->AnimationTimer->start(DEFAULT_FRAME_RATE);

    this->AddSprite();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FullSpritesheetClicked(QPoint pos)
{
    QPointF MappedPos = this->FullSheetView->mapToScene(pos);
    this->HandleClick(MappedPos);
}

void MainWindow::ZoomedSpritesheetClicked(QPoint pos)
{
    QPointF MappedPos = this->SpriteEditView->mapToScene(pos);
    this->HandleClick(MappedPos);
}

void MainWindow::FullSpritesheetMouseMoved(QPointF pos)
{
    QPointF mappedPos = this->FullSheetView->mapToScene(pos.toPoint());
    this->HandleDrag(mappedPos);
}

void MainWindow::ZoomedSpritesheetMouseMoved(QPointF pos)
{
    QPointF mappedPos = this->SpriteEditView->mapToScene(pos.toPoint());

    //Do not handle drag events
    if(this->PlacingMode != DRAG){
        this->HandleDrag(mappedPos);
    }
}

void MainWindow::AdvanceAnimationFrame()
{
    int typeIndex = this->ui->SpriteTypeCombo->currentIndex();
    int dirIndex = this->ui->SpriteDirCombo->currentIndex();
    bool SpriteExists = this->Sprites[typeIndex][dirIndex].size() > 0;

    if(this->FullSpritesheet && this->AutoplayEnabled && SpriteExists){
        Sprite* animFrame = this->Sprites[typeIndex][dirIndex][this->CurrentFrame];

        QPixmap relativePixmap = this->FullSpritesheet->pixmap().copy(animFrame->rect().toRect());
        this->AnimatedSprite->setPixmap(relativePixmap);

        //Adjust the origin to the rect
        QPoint origin = animFrame->origin().toPoint();
        QPoint frameOrigin = animFrame->rect().topLeft().toPoint();
        int dx = frameOrigin.x() - origin.x();
        int dy = frameOrigin.y() - origin.y();
        origin.setX(dx);
        origin.setY(dy);


        //Adjust the pixmap to the origin
        QPoint adjustedPos = QPoint(ObjectPos.x() + origin.x(), ObjectPos.y() + origin.y());

        this->AnimatedSprite->setPos(adjustedPos);

        this->CurrentFrame++;
        if(this->CurrentFrame >= this->Sprites[typeIndex][dirIndex].size()){
            this->CurrentFrame = 0;
        }

        this->ScaleAnimatedSprite(this->AnimationViewPercentage);

        //Adjust the QTimer for this sprite's period
        this->AnimationTimer->setInterval(animFrame->period());
    }
}

void MainWindow::on_AddFrameButton_released()
{
    this->AddSprite();
}

void MainWindow::AddSprite()
{
    Sprite *NewSprite = new Sprite(this);
    if(this->CurrentSprite){
        this->SaveCurrentSprite();
        this->CurrentSprite->CopyTo(NewSprite);
    }

    Sprite::SpriteType type = static_cast<Sprite::SpriteType>(this->ui->SpriteTypeCombo->currentIndex());
    Sprite::Direction dir = static_cast<Sprite::Direction>(this->ui->SpriteDirCombo->currentIndex());

    //The type and dir may not be the same as the selected sprite
    //So we must always set it manually
    NewSprite->setType(type);
    NewSprite->setDir(dir);

    int typeIndex = this->ui->SpriteTypeCombo->currentIndex();
    int dirIndex = this->ui->SpriteDirCombo->currentIndex();
    int spriteIndex = this->ui->SpriteList->currentRow();

    this->CurrentSprite = NewSprite;
    this->Sprites[typeIndex][dirIndex].insert(spriteIndex + 1, NewSprite);

    this->RefreshList();
    this->ui->SpriteList->setCurrentRow(spriteIndex + 1);
}

void MainWindow::AddSprite(Sprite::SpriteType type, Sprite::Direction dir,
                           QPointF anchor, QPointF origin, QRectF rect,
                           int index, int period)
{
    Sprite *sprite = new Sprite(this);
    sprite->setType(type);
    sprite->setDir(dir);
    sprite->setAnchor(anchor);
    sprite->setOrigin(origin);
    sprite->setRect(rect);
    sprite->setPeriod(period);

    this->Sprites[type][dir].insert(index, sprite);
}

void MainWindow::ClearSprites()
{
    for(int t = 0; t < Sprite::N_TYPES; t++){
        for(int d = 0; d < Sprite::N_DIRS; d++){
            Sprites[t][d].clear();
        }
    }
}

void MainWindow::RemoveSelectedSprite()
{
    int typeIndex = this->ui->SpriteTypeCombo->currentIndex();
    int dirIndex = this->ui->SpriteDirCombo->currentIndex();
    int spriteIndex = this->ui->SpriteList->currentRow();

    this->Sprites[typeIndex][dirIndex].removeAt(spriteIndex);
    this->RefreshList();
    this->ui->SpriteList->setCurrentRow(spriteIndex - 1);
}

void MainWindow::RefreshList()
{
    this->ui->SpriteList->clear();
    int typeIndex = this->ui->SpriteTypeCombo->currentIndex();
    int dirIndex = this->ui->SpriteDirCombo->currentIndex();
    QString typeLabel = this->TypeStrings[typeIndex];
    QString dirLabel = this->DirStrings[dirIndex];
    QList<Sprite*> *listPointer = &this->Sprites[typeIndex][dirIndex];

    for(int i = 0; i < listPointer->size(); i++){
        this->ui->SpriteList->addItem(typeLabel + " - " + dirLabel + ": " + QString::number(i + 1));
    }
}

void MainWindow::SaveCurrentSprite()
{
    //Save the sprite's data
    this->CurrentSprite->setAnchor(this->Anchor->rect().center());
    this->CurrentSprite->setOrigin(this->Origin->rect().center());
    this->CurrentSprite->setRect(this->SpritesheetSelection->rect());
    this->CurrentSprite->setPeriod(this->ui->SpritePeriodInput->value());
}

void MainWindow::AdjustSelectionRect(QPointF target)
{
    QPointF center = this->Anchor->rect().center();

    QRectF NewRect = this->SpritesheetSelection->rect();

    //Right side
    if(target.x() > center.x()){
        //Bottom right corner
        if(target.y() > center.y()){
            NewRect.setBottomRight(target);
        }
        //Top right corner
        if(target.y() < center.y()){
            NewRect.setTopRight(target);
        }
    }
    //Left side
    else{
        //Bottom left corner
        if(target.y() > center.y()){
            NewRect.setBottomLeft(target);
        }
        //Top left corner
        if(target.y() < center.y()){
            NewRect.setTopLeft(target);
        }
    }

    //Assign the rect
    this->SpritesheetSelection->setRect(NewRect);
    this->AdjustZoomedView();
}

void MainWindow::AdjustZoomedView()
{
    QRectF AdjustedRect = this->SpritesheetSelection->rect();
    int dw = static_cast<int>(AdjustedRect.width() * 0.10);
    int dh = static_cast<int>(AdjustedRect.height() * 0.10);
    AdjustedRect.adjust(-dw, -dh, dw, dh);

    this->SpriteEditView->fitInView(AdjustedRect);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    QRectF rect = this->SpritesheetSelection->rect();
    switch(keyEvent->key()){
        case Qt::Key_Control:
            this->SetPlacingMode(ANCHOR);
            break;
        case Qt::Key_Tab:
            this->SetPlacingMode(ORIGIN);
            break;
        case Qt::Key_Alt:
            this->SetPlacingMode(DRAG);
            break;
        default:
            //Do nothing
            break;
    }
    this->SpritesheetSelection->setRect(rect);
    this->AdjustZoomedView();
}

void MainWindow::SavePlacingObjectPos()
{
    switch(this->PlacingMode){
        case ANCHOR:
            this->SavedPlacePos = this->Anchor->pos();
            break;
        case ORIGIN:
            this->SavedPlacePos = this->Origin->pos();
            break;
        case DRAG:
            this->SavedPlacePos = this->Origin->pos();
            break;
        default:
            //Does not need to be saved
            break;
    }
}

void MainWindow::SetPlacingObjectPos()
{
    switch(this->PlacingMode){
        case ANCHOR:
            this->SetEllipseObjectPos(this->Anchor, this->SavedPlacePos);
            break;
        case ORIGIN:
            this->SetEllipseObjectPos(this->Origin, this->SavedPlacePos);
            break;
        case DRAG:
            this->SetRectObjectPos(this->SpritesheetSelection, this->SavedPlacePos);
            this->AdjustZoomedView();
            break;
        default:
            //Does not need to be saved
            break;
    }
}

void MainWindow::SetPlacingMode(MainWindow::PlaceMode mode)
{
    //If reassigning to the current mode, return to normal
    if(this->PlacingMode == mode){
        this->SetPlacingObjectPos();
        this->PlacingMode = NORMAL;
    }
    else{
        this->PlacingMode = mode;
        this->SavePlacingObjectPos();
    }

    int ComboBoxIndex = static_cast<int>(this->PlacingMode);
    if(ComboBoxIndex < N_MODES){
        this->ui->PlaceModeCombo->setCurrentIndex(ComboBoxIndex);
    }
}

void MainWindow::HandleClick(QPointF pos)
{
    switch(this->PlacingMode){
        case NORMAL:
            this->AdjustSelectionRect(pos);
            break;
        case ANCHOR:
            this->SetPlacingMode(NORMAL);
            break;
        case ORIGIN:
            this->SetPlacingMode(NORMAL);
            break;
        case DRAG:
            this->SetPlacingMode(NORMAL);
            break;
        default:
            //Do nothing, invalid case
            break;
    }
}

void MainWindow::HandleDrag(QPointF pos)
{
    switch(PlacingMode){
        case ANCHOR:
            this->SetEllipseObjectPos(this->Anchor, pos);
            break;
        case ORIGIN:
            this->SetEllipseObjectPos(this->Origin, pos);
            break;
        case DRAG:
            this->SetRectObjectPos(this->SpritesheetSelection, pos);
            this->AdjustZoomedView();
            break;
        default:
            //Ignore
            break;
    }

    this->SaveCurrentSprite();
}

void MainWindow::SetEllipseObjectPos(QGraphicsEllipseItem *item, QPointF pos)
{
    double width = PLACE_SIZE;
    double height = PLACE_SIZE;
    item->setRect(pos.x() - width/2, pos.y() - height/2, width, height);
}

void MainWindow::SetRectObjectPos(QGraphicsRectItem *item, QPointF pos)
{
    //When setting QGraphicsRectItem position
    //setPos is glitchy and results in unpredictable behavior, unsure why
    //Instead we are setting the rect
    //When setting the rect, if you only set the x,y coordinates, the bottom
    // right corner will not move, resulting in a stretching rect.
    // To fix this, save the size before setting the position and then reassign
    // the size after

    QRectF rect = item->rect();
    double width = rect.width();
    double height = rect.height();
    rect.setX(pos.x() - rect.width()/2);
    rect.setY(pos.y() - rect.height()/2);
    rect.setWidth(width);
    rect.setHeight(height);
    item->setRect(rect);
}

void MainWindow::SetAnimation()
{
    this->CurrentFrame = 0;
}

/*
 * Scales the view to the current sprite type
 */
void MainWindow::ScaleAnimatedSprite(double ViewPercentage)
{
    //Get the bounding rect of the first sprite in this type
    //We don't use the current bounding rect, because it will change between sprites
    //If we used the current bounding rect, it wouldn't give a clean preview (constantly rescaling)
    int spriteType = this->ui->SpriteTypeCombo->currentIndex();
    int spriteDir = this->ui->SpriteDirCombo->currentIndex();
    QRect spriteRect = this->Sprites[spriteType][spriteDir][0]->rect().toRect();
    QPixmap pix = this->FullSpritesheet->pixmap().copy(spriteRect);
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem();
    p->setPixmap(pix);

    QRectF animRect = p->boundingRect();

    //Scale to the largest dimension
    int size = 0;
    if(animRect.width() > animRect.height()){
        //Scale width to view
        size = static_cast<int>(animRect.width() / ViewPercentage);
    }
    else{
        //Scale height to view
        size = static_cast<int>(animRect.height() / ViewPercentage);
    }
    //Set (0,0) to be at
    // x center
    // y just above bottom
    animRect.setRect(-size/2,-size * 0.90,size,size);

    this->SpritePreview->fitInView(animRect);

}

QString MainWindow::ConvertToXML()
{
    QString xml;

    QDomDocument doc;

    QDomElement root = doc.createElement("spritesheet");
    //Create the spritesheet root element
    QString src = this->SpritesheetSource.split('/').last();
    root.setAttribute("Name", this->ui->SpritesheetNameEntry->text());
    root.setAttribute("src", src);
    doc.appendChild(root);

    //Create each frame element
    for(int t = 0; t < Sprite::N_TYPES; t++){
        for(int d = 0; d < Sprite::N_DIRS; d++){
            for(int i = 0; i < this->Sprites[t][d].size(); i++){
                Sprite *s = this->Sprites[t][d][i];

                QRectF rect = s->rect();
                QPointF anchor = s->anchor();
                QPointF origin = s->origin();

                QString rectText = QString(
                            "(" + QString::number(rect.x()) +
                            "," + QString::number(rect.y()) +
                            "," + QString::number(rect.width()) +
                            "," + QString::number(rect.height()) +
                            + ")");

                QString anchorText = QString("(" + QString::number(anchor.x()) +
                                             "," + QString::number(anchor.y()) + ")");

                QString originText = QString("(" + QString::number(origin.x()) +
                                             "," + QString::number(origin.y()) + ")");

                int period = s->period();

                QDomElement frame = doc.createElement("frame");
                frame.setAttribute("type", t);
                frame.setAttribute("dir", d);
                frame.setAttribute("index", i);
                frame.setAttribute("rect", rectText);
                frame.setAttribute("anchor", anchorText);
                frame.setAttribute("origin", originText);
                frame.setAttribute("period", period);
                root.appendChild(frame);
            }
        }
    }

    xml = doc.toString();

    return xml;
}

void MainWindow::OpenImage(QString filePath)
{
    QStringList filePathSplit = filePath.split("/");
    QString imageName = filePathSplit.last();
    this->SpritesheetFilePath = filePathSplit.join("/");

    this->SpritesheetSource = imageName;

    QPixmap pixmap = QPixmap(filePath);
    if(this->FullSpritesheet){
        this->FullSpritesheet->setPixmap(pixmap);
    }
    else{
        this->FullSpritesheet = new QGraphicsPixmapItem(pixmap);
        this->SpritesheetScene->addItem(this->FullSpritesheet);
    }
}

void MainWindow::OpenXML(QString filePath)
{
    QDomDocument doc;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Could not load spritesheet " << filePath;
    }
    else{
        doc.setContent(&file);
        file.close();

        //Clear all currently loaded sprite data
        this->ClearSprites();

        //Construct the path to this directory
        QStringList filePathSplit = filePath.split("/");
        filePathSplit.removeAt(filePathSplit.size() - 1);
        QString directory = filePathSplit.join("/");

        //Create the document object
        QDomElement root = doc.documentElement();

        //Construct the url to the image
        QString ImageURL = directory + "/" + root.attribute("src");
        this->OpenImage(ImageURL);
        this->ui->SpritesheetNameEntry->setText(root.attribute("Name", "No Name Found"));

        //Open each child element and load its properties
        QDomElement child = root.firstChild().toElement();

        while(!child.isNull()){
            //Load type and dir indices
            int typeIndex = child.attribute("type", "0").toInt();
            int dirIndex = child.attribute("dir", "0").toInt();

            //Bound the inputs
            if(typeIndex >= Sprite::N_TYPES){
                typeIndex = 0;
            }
            else if(typeIndex < 0){
                typeIndex = 0;
            }
            if(dirIndex >= Sprite::N_DIRS){
                dirIndex = 0;
            }
            else if(dirIndex < 0){
                dirIndex = 0;
            }

            //Cast to their enums
            Sprite::SpriteType type = static_cast<Sprite::SpriteType>(typeIndex);
            Sprite::Direction dir = static_cast<Sprite::Direction>(dirIndex);

            //Load sprite index
            int index = child.attribute("index", "0").toInt();
            int period = child.attribute("period", "200").toInt();

            //Load sprite positions/rects
            QPointF origin = this->StringToPointF(child.attribute("origin","(0,0)"));
            QPointF anchor = this->StringToPointF(child.attribute("anchor", "(0,0)"));
            QRectF rect = this->StringToRectF(child.attribute("rect", "(0,0,0,0)"));

            this->AddSprite(type, dir, anchor, origin, rect, index, period);

            child = child.nextSibling().toElement();
        }
    }

    this->RefreshList();
    this->AdjustZoomedView();
}

QPointF MainWindow::StringToPointF(QString string)
{
    //Remove parenthesis in front and back
    string.remove(0,1);
    string.remove(string.size() - 1, 1);

    //Separate the two numbers
    QStringList posAsStrings = string.split(",");

    if(posAsStrings.size() == 2){
        bool x_ok = false;
        bool y_ok = false;
        double x = posAsStrings[0].toDouble(&x_ok);
        double y = posAsStrings[1].toDouble(&y_ok);

        if(x_ok & y_ok){
            //Conversion succeeded
            return QPointF(x,y);
        }
    }

    //Conversion failed
    qDebug() << "Position string is corrupted" << string;
    return QPointF(0,0);
}

QRectF MainWindow::StringToRectF(QString string)
{
    //Remove parenthesis in front and back
    string.remove(0,1);
    string.remove(string.size() - 1, 1);

    //Separate the numbers
    QStringList posAsStrings = string.split(",");

    if(posAsStrings.size() == 4){
        bool x_ok = false;
        bool y_ok = false;
        bool w_ok = false;
        bool h_ok = false;
        double x = posAsStrings[0].toDouble(&x_ok);
        double y = posAsStrings[1].toDouble(&y_ok);
        double w = posAsStrings[2].toDouble(&w_ok);
        double h = posAsStrings[3].toDouble(&h_ok);

        if(x_ok && y_ok && w_ok && h_ok){
            //Conversion succeeded
            return QRectF(x,y,w,h);
        }
    }

    //Conversion failed
    qDebug() << "Position string is corrupted: " << string;
    return QRectF(0,0,1,1);
}

void MainWindow::on_SpriteList_currentRowChanged(int currentRow)
{
    if(currentRow >= 0){
        this->SaveCurrentSprite();

        int typeIndex = this->ui->SpriteTypeCombo->currentIndex();
        int dirIndex = this->ui->SpriteDirCombo->currentIndex();

        this->CurrentSprite = this->Sprites[typeIndex][dirIndex][currentRow];

        this->SetEllipseObjectPos(this->Anchor, this->CurrentSprite->anchor());
        this->SetEllipseObjectPos(this->Origin, this->CurrentSprite->origin());
        this->SpritesheetSelection->setRect(this->CurrentSprite->rect());
        this->AdjustZoomedView();
        this->SetAnimation();
    }
}

void MainWindow::on_SpriteDirCombo_currentIndexChanged(int index)
{
    this->SetAnimation();
    this->RefreshList();
}

void MainWindow::on_OpenSpriteButton_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                 "P:/Qt Projects/LevelDesigner",
                                 "Spritesheet files (*.xml *.png *.jpg *.jpeg);;"
                                 "XML files (*.xml);;"
                                 "Images (*.png *.jpg *.jpeg)");

    QString fileExtension = fileName.split('.').last().toLower();


    if(fileExtension == "png" || fileExtension == "jpg" || fileExtension == "jpeg"){
        this->OpenImage(fileName);
    }
    else if(fileExtension == "xml"){
        this->OpenXML(fileName);
    }
    else{
        qDebug() << "Invalid file type opened: " << fileExtension;
    }
}

void MainWindow::on_PlaceModeCombo_currentIndexChanged(int index)
{
    PlaceMode mode = static_cast<PlaceMode>(index);
    this->PlacingMode = mode;
}

void MainWindow::on_SpriteTypeCombo_currentIndexChanged(int index)
{
    this->SetAnimation();
    this->RefreshList();
}

void MainWindow::on_AutoplayCheck_toggled(bool checked)
{
    this->AutoplayEnabled = checked;
}

void MainWindow::on_HideOriginCheck_toggled(bool checked)
{
    if(checked){
        this->AnimationOrigin->hide();
    }
    else{
        this->AnimationOrigin->show();
    }
}

void MainWindow::on_ScaleSpriteSlider_valueChanged(int value)
{
    double perc = static_cast<double>(value) / 100.0;
    this->AnimationViewPercentage = perc;
}

void MainWindow::on_RemoveFrameButton_released()
{
    this->RemoveSelectedSprite();
}

void MainWindow::on_SaveAsButton_released()
{
    //Generate XML
    QString xml = this->ConvertToXML();

    //Get the path to the save file (user prompted)
    QString savePath = "P:/Qt Projects/LevelDesigner";
    QFile file(QFileDialog::getSaveFileName(this, "Save File",
                                            "P:/Qt Projects/LevelDesigner",
                                            "XML (*.xml)"));

    //Open the file and write the xml text to it
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Unable to open file";
    }
    else{
        QTextStream stream(&file);
        stream << xml;
        file.close();
    }
}

void MainWindow::on_SpritePeriodInput_valueChanged(int arg1)
{
    this->CurrentSprite->setPeriod(arg1);
}
