#include "Header.h"
#include <fstream>

using std::ifstream;
using std::ofstream;


void writeToFileTxt() {
    string path(pathToDataBases);
    path.append(txtBase);
    cout << sizeof(path) << endl << path << endl;
    
    //ifstream   in("test2.txt");
    ofstream   out(path);

    Product* pro = new Product;
    pro->id = 2;
    pro->units = Units::LITERS;
    out << *pro;
    delete pro;

    //const int len = STRLEN;
    //char   line[len], * word;

    //cout << "Введите слово";
    //cin >> word;

    //while (!in.eof())
    //{
    //    in.getline(line, len);
    //    if (strcmp(line, word) != 0)
    //    {
    //        out << line << endl;
    //    }

    //}
    ////rename
    //cout << "Слово успешно удалено";

    //char* file_name = "text.txt";
    //string buf, rem;

    //cout << "String to remove: ";

    //getline(std::cin, rem);

    //ifstream ifs(file_name);
    //if (!ifs.is_open()) {
    //    std::cerr << "Can't open file for read!" << std::endl;
    //    return 1;
    //}
    //while (getline(ifs, buf))
    //    if (buf != rem)
    //        vec.push_back(buf);
    //ifs.close();

    //std::ofstream ofs(file_name);
    //if (!ofs.is_open()) {
    //    std::cerr << "Can't open file for write!" << std::endl;
    //    return 1;
    //}
    //std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(ofs, "\n"));
    //in.close();
    out.close();
}