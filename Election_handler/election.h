#ifndef ELECTION_H
#define ELECTION_H

#include <QString>
class election
{
 private:
    QString statecode;
    QString statename;
    QString Countryfips;
    QString countryname;
    size_t  CountryTotalVote;
    QString party;
    QString candicate;
    size_t votecount;
public:
    election(QString sc,QString sn,QString cf,QString cn,size_t ctv,QString p,QString c,size_t vc);
    QString get_state_name()const;
    QString get_state_code()const;
    QString get_Countryfips()const;
    QString get_country_name()const;
    size_t getCountrytottalvote()const;
    QString getParty()const;
    size_t get_votecount()const;
};

#endif // ELECTION_H
