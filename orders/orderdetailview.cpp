#include "orderdetailview.h"
#include "ui_orderdetailview.h"
#include "detailsmodel.h"
#include "templateModel.h"

OrderDetailView::OrderDetailView(DbManager *dbm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderDetailView)
{
    ui->setupUi(this);

    bool isRelational = true;
    detailModel = new CustomModel(dbm, "order_detail", isRelational, this);
    _detailModel = new DetailsModel(dbm,this);
    _detailModel->setHeaders({"uno","dos","tres","cuatro","cinco"});
    QSqlQuery query;


    query.prepare("SELECT * FROM customer_address "
                  "JOIN address ON "
                  "customer_address.fk_address_id=address.address_id");
    //const QString tmp = "SELECT * FROM customer_address JOIN address ON customer_address.fk_address_id=address.address_id";
    _detailModel->setQuery(query);
    //detailModel->setHeaders({"Id", "Customer_id", "Date", "Payment type"});

    //detailModel->setRelation(1, "orders", "order_id", "payment_type");
   // detailModel->setRelation(2, "products", "sku", "name");

    //ui->orderDetailTableView->setModel(detailModel->getRelationalModel());
    ui->orderDetailTableView->setModel(_detailModel);
    ui->orderDetailTableView->setEnabled(true);

    ui->orderDetailTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->orderDetailTableView->horizontalHeader()->setVisible(true);
    ui->orderDetailTableView->setAlternatingRowColors(true);
    ui->orderDetailTableView->setSortingEnabled(true);
    ui->orderDetailTableView->sortByColumn(0, Qt::DescendingOrder);
    //ui->orderDetailTableView->reset();
}

OrderDetailView::~OrderDetailView()
{
    delete ui;
}

void OrderDetailView::updateOrderDetailModel()
{
    _detailModel->updateModel();
    //ui->orderDetailTableView->setModel(_detailModel);
}


