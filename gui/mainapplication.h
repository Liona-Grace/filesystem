#ifndef __MAINAPPLICATION_H__
#define __MAINAPPLICATION_H__

#include <iostream>
#include <memory>

#include "nlohmann/json.hpp"

class FileController;
class QStandardItemModel;
class QStandardItem;

class MainApplication {
public:
    MainApplication(int& argc, char* argv[]);
    ~MainApplication();

    int run();

private:
    bool loadMetadataContent(const std::string& filePath);
    void addJsonNodeToTree(const nlohmann::json& node, QStandardItem* parentItem);

private:
    int argc;
    char** argv;

    std::unique_ptr<FileController> fileController;
    QStandardItemModel* standardItemModel;
};

#endif // __MAINAPPLICATION_H__