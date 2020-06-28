#include <QVector>
#include <cmath>
#include <numeric>
#include <algorithm>

struct maxelem
{
    double max;
    QVector <int> spots;
};

class line{
   QVector <double> numbers;
   public:
   line() {}
   void add_number(const double &n) {this->numbers.append(n);}
   double sum() {
    double s=0.0;
    for(auto &x:this->numbers)
    {
        s+=x;
    }
    return s;
   }
   double sqrtsum() {
       double vecsum=this->sum();
       return sqrt(vecsum);
   }
   double average()
   {
       return this->sum()/this->numbers.size();
   }
   maxelem find_max()
   {
       maxelem maxclue;
       maxclue.max=this->numbers.at(0);
       for(auto &x:this->numbers)
       {
           if(x>maxclue.max)
           {
               maxclue.max=x;
           }
       }
       for(int i=0;i<this->numbers.size();i++)
       {
           if(this->numbers.at(i)==maxclue.max)
           {
               maxclue.spots.append(i+1);
           }
       }
       return maxclue;
   }
   QString to_str()
   {
       QString n;
       n="SUM="+QString::number(this->sum())+"\t SQRT OF SUM="+QString::number(this->sqrtsum())+"\t AVERAGE="+QString::number(this->average())+"\n";
       n+="Max element:"+QString::number(this->find_max().max)+" found on positions:";
       for(auto &y:this->find_max().spots)
       {
           n+=QString::number(y)+" ";
       }
       return n;
   }
   QString info_to_html()
   {
       QString htmlcon="<h2 style=text-align:center; font-family:calibri;>LINE DETAILS</h2><ul>\n";
       int i=1;
       for(auto x:this->numbers)
       {
           htmlcon+="<li>NUMBER_"+QString::number(i)+":"+QString::number(x)+"</li>\n";
       }
       htmlcon+="</li>";
       return htmlcon;
   }
};
