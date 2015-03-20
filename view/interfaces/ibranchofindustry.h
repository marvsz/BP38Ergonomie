#ifndef IBRANCHOFINDUSTRY
#define IBRANCHOFINDUSTRY

#include <QtPlugin>

class IBranchOfIndustry {

signals:
    virtual void saveBranchOfIndustry(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setBranchOfIndustry(QHash<QString, QVariant> values) = 0;
};


#define IBranchOfIndustry_iid "IBranchOfIndustry"
Q_DECLARE_INTERFACE(IBranchOfIndustry, IBranchOfIndustry_iid)

#endif // IBRANCHOFINDUSTRY

