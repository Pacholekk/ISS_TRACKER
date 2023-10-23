#include "mainwindow.h"


#include <QApplication>
/*!
 * \brief Główna funkcja programu.
 * \param argc Liczba argumentów wiersza poleceń.
 * \param argv Tablica argumentów wiersza poleceń.
 * \return Kod zakończenia programu.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
