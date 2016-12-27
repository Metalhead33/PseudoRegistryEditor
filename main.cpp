#include "MainWindow.hpp"
#include <QApplication>

namespace Structure {

Directory* ROOT_DIRECTORY;

}

int main(int argc, char *argv[])
{
    Structure::ROOT_DIRECTORY = new Structure::Directory("root",0);
    FILE* failor = fopen("/home/metalhead33/testfile2","rb");
    Structure::Io::Unserialize(failor);
    fclose(failor);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
