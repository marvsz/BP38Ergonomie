#ifndef REMARKS_H
#define REMARKS_H

#import "textfield.h"

class Remarks
{
public:
    Remarks(TextField* problemId, TextField* problemDescription, TextField* sanctionId, TextField* sanctionDescription, TextField* factoryPerception);
    ~Remarks();

private:
    TextField* problemId;
    TextField* problemDescription;
    TextField* sanctionId;
    TextField* sanctionDescription;
    TextField* factoryPerception;
};


#endif // REMARKS_H
