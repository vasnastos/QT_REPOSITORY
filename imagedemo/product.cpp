#include "product.h"

product::product(int i,QPixmap pix,QString d,double pr):id(i),image(pix),category(d),price(pr) {}
void product::set_pixmap(QPixmap p) {this->image=p;}
int product::getid()const {return this->id;}
QPixmap product::getimage() {return this->image;}
QString product::getcategory()const {return this->category;}
double product::getprice()const {return this->price;}
