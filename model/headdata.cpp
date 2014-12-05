#include "headdata.h"

HeadData::HeadData(Analyst* analyst, Factory* factory, Company* company, QDate* begin, QDate* end)
{
    this->analyst=analyst;
    this->begin=begin;
    this->company=company;
    this->end=end;
    this->factory=factory;
}

HeadData::~HeadData(){

}
