#include "globals.h"
#include "map.h"


void globals::setLevelDone(QString path) {
    QFile qfile(QDir().currentPath() + "/map/config.txt");
    QFile qtemp(QDir().currentPath() + "/map/configtemp.txt");
    qfile.open(QFile::ReadOnly);
    qtemp.open(QFile::WriteOnly);
    QTextStream writeStreamConfig(&qtemp);
    writeStreamConfig.setCodec(QTextCodec::codecForName("UTF-8"));
    while (!qfile.atEnd()) {
        QString s = qfile.readLine();
        int solved = s[s.size() - 3].digitValue();
        QString name = s.mid(0, s.size() - 4);
        if (name == path) {
            writeStreamConfig << name << " " << 1 << "\r\n";
        }
        else {
            writeStreamConfig << s;
        }
    }
    qfile.remove();
    qtemp.rename(QDir().currentPath() + "/map/config.txt");
    qtemp.close();
}

QString globals::goToLevel() {
    QFile qfile(QDir().currentPath() + "/map/config.txt");
    qfile.open(QFile::ReadOnly | QFile::Text);
    QString name = nullptr;
    while (!qfile.atEnd()) {
        QString s = qfile.readLine();
        if (s[s.size() - 2].digitValue() == 0) {
            name = s.mid(0, s.size() - 3);
            Map map;
            map.ReadFrom(name);
            if (!map.isValid()) {
                name = nullptr;
            }
            else {
                break;
            }
        }
    }
    qfile.close();
    if (name == nullptr) {
        return nullptr;

    }
    else {
        return name;
    }
}

QString globals::nameOfLevelFromPath(QString path) {
    std::string s = path.toStdString();
    return QString::fromStdString(s.substr(s.find_last_of('/') + 1, s.find_last_of('.') - s.find_last_of('/') - 1));
}
