#include "server.h"

Server::Server(QWidget *parent) : QDialog(parent){
    setFixedSize(400,200);

    tport = 6666;

    tSrv = new QTcpServer(this);

    // connect(tSrv, &QTcpServer::newConnection, this, sendmsg());
    connect(tSrv,SIGNAL(newConnection()),this,SLOT(sendmsg()));

    initserver();
}
void Server::sendmsg(){
    payloadsize=1024*4;
    totalbytes=0;
    byteswritten=0;
    bytestobewrite=0;
}
void Server::sendfilename(QString filename){

}
void Server::initserver(){

}
void Server::refused(){

}
