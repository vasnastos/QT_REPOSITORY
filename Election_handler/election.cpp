#include "election.h"

election::election(QString sc,QString sn,QString cf,QString cn,size_t ctv,QString p,QString c,size_t vc)
{
    this->statecode=sc;
    this->statename=sn;
    this->Countryfips=cf;
    this->countryname=cn;
    this->CountryTotalVote=ctv;
    this->party=p;
    this->candicate=c;
    this->votecount=vc;
}
QString election::get_state_name()const {return this->statename;}
QString election::get_state_code()const {return this->statecode;}
QString election::get_Countryfips()const {return this->Countryfips;}
QString election::get_country_name()const {return this->countryname;}
size_t election::getCountrytottalvote()const {return this->CountryTotalVote;}
QString election::getParty()const {return this->party;}
size_t election::get_votecount()const {return this->votecount;}
