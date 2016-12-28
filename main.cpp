#include "MainWindow.hpp"
#include <QApplication>

namespace Structure {

Directory* ROOT_DIRECTORY;

}

int main(int argc, char *argv[])
{
    Structure::ROOT_DIRECTORY = new Structure::Directory("root",0);
    if(argc > 1) {
    FILE* failor = fopen(argv[1],"rb");
    Structure::Io::Unserialize(failor);
    fclose(failor);
    }
    else
    {
        new Structure::Directory("Dir1",Structure::ROOT_DIRECTORY);
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
