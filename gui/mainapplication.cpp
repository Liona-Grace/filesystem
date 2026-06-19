#include "mainapplication.h"

#include <QApplication>
#include <QWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>

#include "filecontroller.h"

MainApplication::MainApplication(int& argc, char* argv[]) : argc(argc), argv(argv) {
    fileController = std::make_unique<FileController>();
}

MainApplication::~MainApplication() {}

int MainApplication::run() {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Filesystem Metadata Viewer");
    window.resize(700, 500);

    auto* layout = new QVBoxLayout(&window);
    auto* treeView = new QTreeView(&window);

    standardItemModel = new QStandardItemModel(&window);
    standardItemModel->setHorizontalHeaderLabels({"Name", "Type", "Blob"});

    treeView->setModel(standardItemModel);
    treeView->setColumnWidth(0, 250);

    layout->addWidget(treeView);

    loadMetadataContent("/home/liona/_apps/projects/metadata/filesystem_metadata.json");

    treeView->expandAll();

    window.show();
    return app.exec();
}

bool MainApplication::loadMetadataContent(const std::string& filePath) {
    std::string content;
    if (!fileController->readFileContent(filePath, content)) {
        std::cerr << "Failed to read metadata content from: " << filePath << std::endl;
        return false;
    }

    nlohmann::json rootJson;

    try {
        rootJson = nlohmann::json::parse(content);
    } catch (const std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }

    standardItemModel->removeRows(0, standardItemModel->rowCount());

    QStandardItem* rootItem = standardItemModel->invisibleRootItem();
    addJsonNodeToTree(rootJson, rootItem);

    return true;
}

void MainApplication::addJsonNodeToTree(const nlohmann::json& node, QStandardItem* parentItem) {
    const std::string name = node.value("name", "<unnamed>");
    const std::string type = node.value("type", "<unknown>");
    const std::string blob = node.value("blob", "");

    auto* nameItem = new QStandardItem(QString::fromStdString(name));
    auto* typeItem = new QStandardItem(QString::fromStdString(type));
    auto* blobItem = new QStandardItem(QString::fromStdString(blob));

    parentItem->appendRow({nameItem, typeItem, blobItem});

    if (type == "folder" && node.contains("children") && node["children"].is_array()) {
        for (const auto& child : node["children"]) {
            addJsonNodeToTree(child, nameItem);
        }
    }
}
