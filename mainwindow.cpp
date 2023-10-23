
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iss_data.h"



/**
 * @brief Konstruktor klasy MainWindow
 * @param parent Wskaźnik do obiektu rodzica
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Nadanie nazwy okna
    setWindowTitle("ISS TRACKER");
    // Wczytaj obrazy mapy i satelity
    QPixmap map("/Users/patrykpacholskii/Desktop/SEM6/map.jpeg");
    QPixmap sat("/Users/patrykpacholskii/Desktop/SEM6/iss.png");


    // Pobierz szerokość i wysokość label_map
    int w = ui->label_map->width();
    int h = ui->label_map->height();

    // Utwórz obiekty QNetworkAccessManager i QTimer
    manager = new QNetworkAccessManager(this);
    timer = new QTimer(this);

    // Połącz sygnał timeout timera ze slotami
    connect(timer, &QTimer::timeout, this, &MainWindow::readSateliteData);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetworkResponse);

    // Ustaw pixmapę label_map i label_sat
    ui->label_map->setPixmap(map.scaled(w, h, Qt::KeepAspectRatio));
    ui->label_sat->setPixmap(sat);

    // Powtarzaj powyzsze operacje co 1s
    timer->start(1000);
}

/**
 * @brief Funkcja odczytująca dane satelity
 */

void MainWindow::readSateliteData()
{
    // Utwórz obiekt QUrl z adresem URL API
    QUrl url("https://api.wheretheiss.at/v1/satellites/25544");
    QNetworkRequest request(url);
     // Wyślij żądanie GET do API za pomocą managera
    manager->get(request);
}
/**
 * @brief Funkcja obsługująca odpowiedź sieciową
 * @param reply Obiekt QNetworkReply zawierający odpowiedź sieciową
 */

void MainWindow::handleNetworkResponse(QNetworkReply *reply)
{
    // Odczytaj dane odpowiedzi z obiektu reply
    QByteArray data = reply->readAll();
    // Sparsuj dane JSON do obiektu QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(data);
    // Pobierz główny obiekt JSON z dokumentu
    QJsonObject obj = doc.object();
    // Zczytaj dane wartości szerokości i długości geograficzne
    double latitude = obj.value("latitude").toDouble();
    double longitude = obj.value("longitude").toDouble();

    // Pobierz szerokość i wysokość label_map
    int w = ui->label_map->width();
    int h = ui->label_map->height();

    // Pobierz aktualną pixmapę label_map i label_sat
    QPixmap map = ui->label_map->pixmap();
    QPixmap sat = ui->label_sat->pixmap();

    // Oblicz współrzędne x i y satelity na mapie
    int x = calculateSatelliteXCoordinate(longitude, w);
    int y = calculateSatelliteYCoordinate(latitude, h, w);

    // Ustaw pixmapę i geometrię label_sat, aby zaktualizować jego pozycję na mapie
    ui->label_sat->setPixmap(sat);
    ui->label_sat->setGeometry(x, y, sat.width(), sat.height());

    // Ustaw pixmapę label_map, aby zachować oryginalny obraz mapy
    ui->label_map->setPixmap(map);
}
/**
 * @brief Funkcja obliczająca współrzędną x satelity na mapie
 * @param longitude Długość geograficzna satelity
 * @param mapWidth Szerokość mapy
 * @return Współrzędna x satelity na mapie
 */
int MainWindow::calculateSatelliteXCoordinate(double longitude, int mapWidth)
{
     // Oblicz współrzędną x
    return static_cast<int>((longitude + 180.0) * (mapWidth / 360.0));
}

/**
 * @brief Funkcja obliczająca współrzędną y satelity na mapie
 * @param latitude Szerokość geograficzna satelity
 * @param mapHeight Wysokość mapy
 * @param mapWidth Szerokość mapy
 * @return Współrzędna y satelity na mapie
 */
int MainWindow::calculateSatelliteYCoordinate(double latitude, int mapHeight, int mapWidth)
{
    double pi = 3.1415;
    double lat_rad = latitude * pi / 180;
    double mercn = log(tan((pi / 4) + lat_rad / 2));
    // Oblicz współrzędną y
    return static_cast<int>((mapHeight / 2) - (mapWidth * mercn / (2 * pi)));
}








/**
 * @brief Destruktor klasy MainWindow
 */


MainWindow::~MainWindow()
{
    delete ui;
}




/**
 * @brief Slot wywoływany po kliknięciu przycisku
 * Tworzy i wyświetla okno Iss_Data
 */
void MainWindow::on_pushButton_clicked()
{
    Iss_Data window;
    window.setModal(true);
    window.exec();
}




