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
    dummyHolder(new QLabel),
    key(0)
{
    dummyHash = QHash<int, QString>();
    dummyHash.insert(13111,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(13112,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(13113,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(13114,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(13115,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(13211,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(13212,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(13213,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(13214,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(13215,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(13311,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(13312,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(13313,":/icons/QuickBodyPosture/standing_bothArms_overHead_noBending.png");
    dummyHash.insert(13314,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(13315,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(23111,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(23112,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(23113,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(23114,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(23115,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(23211,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(23212,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(23213,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(23214,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(23215,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(23311,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(23312,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(23313,":/icons/QuickBodyPosture/sitting_bothArms_overHead_noBending.png");
    dummyHash.insert(23314,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(23315,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(31111,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(31112,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(31113,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(31114,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(31115,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(31211,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(31212,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(31213,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(31214,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(31215,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(31311,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(31312,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(31313,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    dummyHash.insert(31314,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(31315,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(32111,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(32112,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(32113,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(32114,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(32115,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(32211,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(32212,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(32213,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(32214,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(32215,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(32311,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(32312,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(32313,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    dummyHash.insert(32314,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(32315,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(33111,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(33112,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(33113,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(33114,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(33115,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(33211,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(33212,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(33213,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(33214,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(33215,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(33311,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(33312,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(33313,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_noBending.png");
    dummyHash.insert(33314,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(33315,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(43111,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(43112,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(43113,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_noBending.png");
    dummyHash.insert(43114,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(43115,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(43211,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(43212,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(43213,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_noBending.png");
    dummyHash.insert(43214,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(43215,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(43311,":/icons/QuickBodyPosture/walking_arms_overHead_strongBendingFront.png");
    dummyHash.insert(43312,":/icons/QuickBodyPosture/walking_arms_overHead_lightBendingFront.png");
    dummyHash.insert(43313,":/icons/QuickBodyPosture/walking_arms_overHead_noBending.png");
    dummyHash.insert(43314,":/icons/QuickBodyPosture/walking_arms_overHead_lightBendingBack.png");
    dummyHash.insert(43315,":/icons/QuickBodyPosture/walking_arms_overHead_strongBendingBack.png");

    dummyHash.insert(53111,":/icons/QuickBodyPosture/running_arms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(53112,":/icons/QuickBodyPosture/running_arms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(53113,":/icons/QuickBodyPosture/running_arms_atElbowHeight_noBending.png");
    dummyHash.insert(53114,":/icons/QuickBodyPosture/running_arms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(53115,":/icons/QuickBodyPosture/running_arms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(53211,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(53212,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(53213,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_noBending.png");
    dummyHash.insert(53214,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(53215,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(53311,":/icons/QuickBodyPosture/running_arms_overHead_strongBendingFront.png");
    dummyHash.insert(53312,":/icons/QuickBodyPosture/running_arms_overHead_lightBendingFront.png");
    dummyHash.insert(53313,":/icons/QuickBodyPosture/running_arms_overHead_noBending.png");
    dummyHash.insert(53314,":/icons/QuickBodyPosture/running_arms_overHead_lightBendingBack.png");
    dummyHash.insert(53315,":/icons/QuickBodyPosture/running_arms_overHead_strongBendingBack.png");

    dummyHash.insert(13121,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(13122,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(13123,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(13124,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(13125,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(13221,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(13222,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(13223,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(13224,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(13225,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(13321,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(13322,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(13323,":/icons/QuickBodyPosture/standing_bothArms_overHead_noBending.png");
    dummyHash.insert(13324,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(13325,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(23121,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(23122,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(23123,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(23124,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(23125,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(23221,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(23222,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(23223,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(23224,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(23225,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(23321,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(23322,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(23323,":/icons/QuickBodyPosture/sitting_bothArms_overHead_noBending.png");
    dummyHash.insert(23324,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(23325,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(31121,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(31122,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(31123,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(31124,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(31125,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(31221,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(31222,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(31223,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(31224,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(31225,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(31321,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(31322,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(31323,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    dummyHash.insert(31324,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(31325,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(32121,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(32122,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(32123,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(32124,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(32125,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(32221,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(32222,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(32223,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(32224,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(32225,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(32321,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(32322,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(32323,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    dummyHash.insert(32324,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(32325,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(33121,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(33122,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(33123,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(33124,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(33125,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(33221,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(33222,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(33223,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(33224,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(33225,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(33321,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(33322,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(33323,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_noBending.png");
    dummyHash.insert(33324,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(33325,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(43121,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(43122,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(43123,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_noBending.png");
    dummyHash.insert(43124,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(43125,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(43221,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(43222,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(43223,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_noBending.png");
    dummyHash.insert(43224,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(43225,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(43321,":/icons/QuickBodyPosture/walking_arms_overHead_strongBendingFront.png");
    dummyHash.insert(43322,":/icons/QuickBodyPosture/walking_arms_overHead_lightBendingFront.png");
    dummyHash.insert(43323,":/icons/QuickBodyPosture/walking_arms_overHead_noBending.png");
    dummyHash.insert(43324,":/icons/QuickBodyPosture/walking_arms_overHead_lightBendingBack.png");
    dummyHash.insert(43325,":/icons/QuickBodyPosture/walking_arms_overHead_strongBendingBack.png");

    dummyHash.insert(53121,":/icons/QuickBodyPosture/running_arms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(53122,":/icons/QuickBodyPosture/running_arms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(53123,":/icons/QuickBodyPosture/running_arms_atElbowHeight_noBending.png");
    dummyHash.insert(53124,":/icons/QuickBodyPosture/running_arms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(53125,":/icons/QuickBodyPosture/running_arms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(53221,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(53222,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(53223,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_noBending.png");
    dummyHash.insert(53224,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(53225,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(53321,":/icons/QuickBodyPosture/running_arms_overHead_strongBendingFront.png");
    dummyHash.insert(53322,":/icons/QuickBodyPosture/running_arms_overHead_lightBendingFront.png");
    dummyHash.insert(53323,":/icons/QuickBodyPosture/running_arms_overHead_noBending.png");
    dummyHash.insert(53324,":/icons/QuickBodyPosture/running_arms_overHead_lightBendingBack.png");
    dummyHash.insert(53325,":/icons/QuickBodyPosture/running_arms_overHead_strongBendingBack.png");


    dummyHash.insert(13131,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(13132,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(13133,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(13134,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(13135,":/icons/QuickBodyPosture/standing_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(13231,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(13232,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(13233,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(13234,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(13235,":/icons/QuickBodyPosture/standing_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(13331,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(13332,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(13333,":/icons/QuickBodyPosture/standing_bothArms_overHead_noBending.png");
    dummyHash.insert(13334,":/icons/QuickBodyPosture/standing_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(13335,":/icons/QuickBodyPosture/standing_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(23131,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(23132,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(23133,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(23134,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(23135,":/icons/QuickBodyPosture/sitting_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(23231,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(23232,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(23233,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(23234,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(23235,":/icons/QuickBodyPosture/sitting_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(23331,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(23332,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(23333,":/icons/QuickBodyPosture/sitting_bothArms_overHead_noBending.png");
    dummyHash.insert(23334,":/icons/QuickBodyPosture/sitting_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(23335,":/icons/QuickBodyPosture/sitting_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(31131,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(31132,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(31133,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(31134,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(31135,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(31231,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(31232,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(31233,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(31234,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(31235,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(31331,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(31332,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(31333,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    dummyHash.insert(31334,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(31335,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(32131,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(32132,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(32133,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(32134,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(32135,":/icons/QuickBodyPosture/kneelingRight_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(32231,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(32232,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(32233,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(32234,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(32235,":/icons/QuickBodyPosture/kneelingRight_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(32331,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(32332,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(32333,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_noBending.png");
    dummyHash.insert(32334,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(32335,":/icons/QuickBodyPosture/kneelingRight_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(33131,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(33132,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(33133,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_noBending.png");
    dummyHash.insert(33134,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(33135,":/icons/QuickBodyPosture/kneeling_bothArms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(33231,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(33232,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(33233,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_noBending.png");
    dummyHash.insert(33234,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(33235,":/icons/QuickBodyPosture/kneeling_bothArms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(33331,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingFront.png");
    dummyHash.insert(33332,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingFront.png");
    dummyHash.insert(33333,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_noBending.png");
    dummyHash.insert(33334,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_lightBendingBack.png");
    dummyHash.insert(33335,":/icons/QuickBodyPosture/kneeling_bothArms_overHead_strongBendingBack.png");

    dummyHash.insert(43131,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(43132,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(43133,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_noBending.png");
    dummyHash.insert(43134,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(43135,":/icons/QuickBodyPosture/walking_arms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(43231,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(43232,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(43233,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_noBending.png");
    dummyHash.insert(43234,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(43235,":/icons/QuickBodyPosture/walking_arms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(43331,":/icons/QuickBodyPosture/walking_arms_overHead_strongBendingFront.png");
    dummyHash.insert(43332,":/icons/QuickBodyPosture/walking_arms_overHead_lightBendingFront.png");
    dummyHash.insert(43333,":/icons/QuickBodyPosture/walking_arms_overHead_noBending.png");
    dummyHash.insert(43334,":/icons/QuickBodyPosture/walking_arms_overHead_lightBendingBack.png");
    dummyHash.insert(43335,":/icons/QuickBodyPosture/walking_arms_overHead_strongBendingBack.png");

    dummyHash.insert(53131,":/icons/QuickBodyPosture/running_arms_atElbowHeight_strongBendingFront.png");
    dummyHash.insert(53132,":/icons/QuickBodyPosture/running_arms_atElbowHeight_lightBendingFront.png");
    dummyHash.insert(53133,":/icons/QuickBodyPosture/running_arms_atElbowHeight_noBending.png");
    dummyHash.insert(53134,":/icons/QuickBodyPosture/running_arms_atElbowHeight_lightBendingBack.png");
    dummyHash.insert(53135,":/icons/QuickBodyPosture/running_arms_atElbowHeight_strongBendingBack.png");
    dummyHash.insert(53231,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_strongBendingFront.png");
    dummyHash.insert(53232,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_lightBendingFront.png");
    dummyHash.insert(53233,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_noBending.png");
    dummyHash.insert(53234,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_lightBendingBack.png");
    dummyHash.insert(53235,":/icons/QuickBodyPosture/running_arms_atShoulderHeight_strongBendingBack.png");
    dummyHash.insert(53331,":/icons/QuickBodyPosture/running_arms_overHead_strongBendingFront.png");
    dummyHash.insert(53332,":/icons/QuickBodyPosture/running_arms_overHead_lightBendingFront.png");
    dummyHash.insert(53333,":/icons/QuickBodyPosture/running_arms_overHead_noBending.png");
    dummyHash.insert(53334,":/icons/QuickBodyPosture/running_arms_overHead_lightBendingBack.png");
    dummyHash.insert(53335,":/icons/QuickBodyPosture/running_arms_overHead_strongBendingBack.png");

    shown = true;

    btnName->setMaximumWidth(150);
    connect(btnName, SIGNAL(clicked()), this, SLOT(btnNameClicked()));

    qlpcQuickLegPosture->setValues(QUICK_LEG_POSTURE_TEXTS,LEFT_RIGHT_TEXTS,tr("Quick Leg Posture"));
    connect(qlpcQuickLegPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(qlpcQuickLegPostureChanged(int,int)));
    connect(qlpcQuickLegPosture, SIGNAL(specificationChanged(int)), this, SLOT(qlpcQuickLegPostureSpecificationChagend(int)));

    voscQuickArmPosture->setValues(QUICK_ARM_POSTURE_TEXTS,LEFT_RIGHT_TEXTS, tr("Quick Arm Posture"));
    connect(voscQuickArmPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(voscQuickArmPostureChanged(int,int)));

    voscQuickTrunkPosture->setValues(QUICK_TRUNK_POSTURE_TEXTS, tr("Quick Trunk Posture") );
    connect(voscQuickTrunkPosture, SIGNAL(selectionChanged(int)), this, SLOT(voscQuickTrunkPostureChanged(int)));



    dummyHolder->setPixmap(dummy_standing_bothArms_atElbowHeight_strongBendingFront);
    dummyHolder->setFixedSize(QSize(275,313));

    verticalLayout->addWidget(qlpcQuickLegPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickArmPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickTrunkPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(dummyHolder);

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
    dummyHolder->setPixmap(dummyHash.value(key));
}


//GETTER/SETTER

QString QuickSelectionControl::getName() const{
    return this->name;
}
