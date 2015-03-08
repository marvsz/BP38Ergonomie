#include "quickselectioncontrol.h"
#include "../../separator.h"
#include <qDebug>
QuickSelectionControl::QuickSelectionControl(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout),
    verticalLayout(new QHBoxLayout()),
    mainContent(new QWidget()),
    btnName(new QPushButton()),
    qlpcQuickLegPosture(new QuickLegPostureControl),
    voscQuickArmPosture(new QuickArmPostureControl),
    voscQuickTrunkPosture(new VerticalOptionSelectionControl),
    //hans(new QPixmap),
    hansHolder(new QLabel),
    key(0)
{
    hansHash = QHash<int, QString>();
    hansHash.insert(13111,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(13112,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(13113,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(13114,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(13115,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(13211,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(13212,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(13213,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(13214,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(13215,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(13311,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(13312,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(13313,":/icons/QuickBodyPosture/standing_bothArms_overHead_noBending.png");
    hansHash.insert(13314,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(13315,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(23111,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(23112,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(23113,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(23114,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(23115,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(23211,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(23212,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(23213,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(23214,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(23215,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(23311,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(23312,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(23313,":/icons/QuickBodyPosture/sitting_bothArms_overHead_noBending.png");
    hansHash.insert(23314,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(23315,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(31111,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(31112,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(31113,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(31114,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(31115,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(31211,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(31212,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(31213,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(31214,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(31215,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(31311,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(31312,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(31313,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    hansHash.insert(31314,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(31315,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(32111,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(32112,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(32113,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(32114,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(32115,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(32211,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(32212,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(32213,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(32214,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(32215,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(32311,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(32312,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(32313,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    hansHash.insert(32314,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(32315,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(33111,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(33112,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(33113,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(33114,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(33115,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(33211,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(33212,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(33213,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(33214,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(33215,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(33311,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(33312,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(33313,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_noBending.png");
    hansHash.insert(33314,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(33315,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(43111,"");
    hansHash.insert(43112,"");
    hansHash.insert(43113,"");
    hansHash.insert(43114,"");
    hansHash.insert(43115,"");
    hansHash.insert(43211,"");
    hansHash.insert(43212,"");
    hansHash.insert(43213,"");
    hansHash.insert(43214,"");
    hansHash.insert(43215,"");
    hansHash.insert(43311,"");
    hansHash.insert(43312,"");
    hansHash.insert(43313,"");
    hansHash.insert(43314,"");
    hansHash.insert(43315,"");

    hansHash.insert(43111,"");
    hansHash.insert(43112,"");
    hansHash.insert(43113,"");
    hansHash.insert(43114,"");
    hansHash.insert(43115,"");
    hansHash.insert(43211,"");
    hansHash.insert(43212,"");
    hansHash.insert(43213,"");
    hansHash.insert(43214,"");
    hansHash.insert(43215,"");
    hansHash.insert(43311,"");
    hansHash.insert(43312,"");
    hansHash.insert(43313,"");
    hansHash.insert(43314,"");
    hansHash.insert(43315,"");

    hansHash.insert(13121,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(13122,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(13123,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(13124,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(13125,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(13221,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(13222,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(13223,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(13224,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(13225,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(13321,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(13322,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(13323,":/icons/QuickBodyPosture/standing_bothArms_overHead_noBending.png");
    hansHash.insert(13324,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(13325,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(23121,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(23122,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(23123,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(23124,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(23125,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(23221,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(23222,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(23223,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(23224,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(23225,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(23321,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(23322,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(23323,":/icons/QuickBodyPosture/sitting_bothArms_overHead_noBending.png");
    hansHash.insert(23324,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(23325,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(31121,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(31122,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(31123,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(31124,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(31125,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(31221,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(31222,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(31223,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(31224,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(31225,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(31321,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(31322,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(31323,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    hansHash.insert(31324,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(31325,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(32121,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(32122,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(32123,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(32124,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(32125,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(32221,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(32222,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(32223,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(32224,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(32225,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(32321,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(32322,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(32323,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    hansHash.insert(32324,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(32325,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(33121,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(33122,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(33123,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(33124,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(33125,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(33221,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(33222,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(33223,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(33224,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(33225,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(33321,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(33322,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(33323,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_noBending.png");
    hansHash.insert(33324,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(33325,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(43121,"");
    hansHash.insert(43122,"");
    hansHash.insert(43123,"");
    hansHash.insert(43124,"");
    hansHash.insert(43125,"");
    hansHash.insert(43221,"");
    hansHash.insert(43222,"");
    hansHash.insert(43223,"");
    hansHash.insert(43224,"");
    hansHash.insert(43225,"");
    hansHash.insert(43321,"");
    hansHash.insert(43322,"");
    hansHash.insert(43323,"");
    hansHash.insert(43324,"");
    hansHash.insert(43325,"");

    hansHash.insert(43121,"");
    hansHash.insert(43122,"");
    hansHash.insert(43123,"");
    hansHash.insert(43124,"");
    hansHash.insert(43125,"");
    hansHash.insert(43221,"");
    hansHash.insert(43222,"");
    hansHash.insert(43223,"");
    hansHash.insert(43224,"");
    hansHash.insert(43225,"");
    hansHash.insert(43321,"");
    hansHash.insert(43322,"");
    hansHash.insert(43323,"");
    hansHash.insert(43324,"");
    hansHash.insert(43325,"");


    hansHash.insert(13131,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(13132,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(13133,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(13134,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(13135,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(13231,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(13232,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(13233,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(13234,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(13235,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(13331,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(13332,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(13333,":/icons/QuickBodyPosture/standing_bothArms_overHead_noBending.png");
    hansHash.insert(13334,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(13335,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(23131,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(23132,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(23133,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(23134,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(23135,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingBack.png");
    hansHash.insert(23231,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(23232,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(23233,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(23234,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(23235,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(23331,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(23332,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(23333,":/icons/QuickBodyPosture/sitting_bothArms_overHead_noBending.png");
    hansHash.insert(23334,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(23335,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(31131,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(31132,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(31133,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(31134,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(31135,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(31231,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(31232,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(31233,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(31234,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(31235,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(31331,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(31332,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(31333,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    hansHash.insert(31334,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(31335,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(32131,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(32132,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(32133,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(32134,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(32135,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(32231,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(32232,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(32233,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(32234,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(32235,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(32331,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(32332,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(32333,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    hansHash.insert(32334,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(32335,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(33131,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingFront.png");
    hansHash.insert(33132,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingFront.png");
    hansHash.insert(33133,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_noBending.png");
    hansHash.insert(33134,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingBack.png");
    hansHash.insert(33135,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(33231,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingFront.png");
    hansHash.insert(33232,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingFront.png");
    hansHash.insert(33233,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_noBending.png");
    hansHash.insert(33234,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingBack.png");
    hansHash.insert(33235,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    hansHash.insert(33331,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingFront.png");
    hansHash.insert(33332,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingFront.png");
    hansHash.insert(33333,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_noBending.png");
    hansHash.insert(33334,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingBack.png");
    hansHash.insert(33335,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingBack.png");

    hansHash.insert(43131,"");
    hansHash.insert(43132,"");
    hansHash.insert(43133,"");
    hansHash.insert(43134,"");
    hansHash.insert(43135,"");
    hansHash.insert(43231,"");
    hansHash.insert(43232,"");
    hansHash.insert(43233,"");
    hansHash.insert(43234,"");
    hansHash.insert(43235,"");
    hansHash.insert(43331,"");
    hansHash.insert(43332,"");
    hansHash.insert(43333,"");
    hansHash.insert(43334,"");
    hansHash.insert(43335,"");

    hansHash.insert(43131,"");
    hansHash.insert(43132,"");
    hansHash.insert(43133,"");
    hansHash.insert(43134,"");
    hansHash.insert(43135,"");
    hansHash.insert(43231,"");
    hansHash.insert(43232,"");
    hansHash.insert(43233,"");
    hansHash.insert(43234,"");
    hansHash.insert(43235,"");
    hansHash.insert(43331,"");
    hansHash.insert(43332,"");
    hansHash.insert(43333,"");
    hansHash.insert(43334,"");
    hansHash.insert(43335,"");



    btnName->setMaximumWidth(150);
    connect(btnName, SIGNAL(clicked()), this, SLOT(btnNameClicked()));

    qlpcQuickLegPosture->setValues(QUICK_LEG_POSTURE_TEXTS,LEFT_RIGHT_TEXTS,tr("Quick Leg Posture"));
    connect(qlpcQuickLegPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(qlpcQuickLegPostureChanged(int,int)));
    connect(qlpcQuickLegPosture, SIGNAL(specificationChanged(int)), this, SLOT(qlpcQuickLegPostureSpecificationChagend(int)));

    voscQuickArmPosture->setValues(QUICK_ARM_POSTURE_TEXTS,LEFT_RIGHT_TEXTS, tr("Quick Arm Posture"));
    connect(voscQuickArmPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(voscQuickArmPostureChanged(int,int)));

    voscQuickTrunkPosture->setValues(QUICK_TRUNK_POSTURE_TEXTS, tr("Quick Trunk Posture") );
    connect(voscQuickTrunkPosture, SIGNAL(selectionChanged(int)), this, SLOT(voscQuickTrunkPostureChanged(int)));



    hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_noBending);
    hansHolder->setFixedSize(QSize(275,313));

    verticalLayout->addWidget(qlpcQuickLegPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickArmPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickTrunkPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(hansHolder);

    mainContent->setLayout(verticalLayout);

    mainLayout->addWidget(btnName);
    mainLayout->addWidget(mainContent);

    this->setLayout(mainLayout);
}

// PRIVATE SLOTS

void QuickSelectionControl::hideContent(){
    mainContent->hide();
}

void QuickSelectionControl::showContent(){
    mainContent->show();
}

void QuickSelectionControl::setExclusiveDisplayByName(const QString &name){
    if((name.compare(this->name) == 0) && !shown){
        showContent();
        shown = true;
    }
    else{
        hideContent();
        shown = false;
    }
}

void QuickSelectionControl::setName(const QString &name){
    this->name = name;
}

void QuickSelectionControl::setButtonIcon(const QString &objectName, const QSize &size){
    btnName->setObjectName(objectName);
    btnName->setFixedSize(size);
}

void QuickSelectionControl::btnNameClicked() {  
    emit requestShowContent(this->name);
}

void QuickSelectionControl::voscQuickTrunkPostureChanged(int id){
    emit quickTrunkPostureChanged(id);
    updateDummyPosture();
   /* switch (id) {
    case 1:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_strongBendingFront);
        break;
    case 2:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_lightBendingFront);
        break;
    case 3:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_noBending);
        break;
    case 4:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_lightBendingBack);
        break;
    case 5:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_strongBendingBack);
        break;
    default:
        hansHolder->setPixmap(hans);
        break;
    }*/
}

void QuickSelectionControl::voscQuickArmPostureChanged(int id, int sel){
    emit quickArmPostureChanged(id,sel);
    updateDummyPosture();
}

void QuickSelectionControl::qlpcQuickLegPostureChanged(int id,int sel){
    emit quickLegPostureChanged(id,sel);
    updateDummyPosture();
}

void QuickSelectionControl::qlpcQuickLegPostureSpecificationChagend(int sel){
    emit quickLegPostureSpecificationChanged(sel);
    updateDummyPosture();
}

void QuickSelectionControl::updateDummyPosture(){
    key=10000*qlpcQuickLegPosture->getSelectedID()+1000*qlpcQuickLegPosture->getSelectedSpecification()+100*voscQuickArmPosture->getSelectedID()+10*voscQuickArmPosture->getSelectedSpecification()+voscQuickTrunkPosture->getSelectedID();
    qDebug()<<key;
    hansHolder->setPixmap(hansHash.value(key));
}


//GETTER/SETTER

QString QuickSelectionControl::getName() const{
    return this->name;
}
