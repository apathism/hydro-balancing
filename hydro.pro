TEMPLATE = app
CONFIG += qt

SOURCES += Main.cpp

HEADERS += Storage.h
SOURCES += Storage.cpp

HEADERS += Wizard.h
SOURCES += Wizard.cpp

HEADERS += PageIntro.h
SOURCES += PageIntro.cpp

HEADERS += PageSpecification.h
SOURCES += PageSpecification.cpp

HEADERS += PageSpecificationFile.h
SOURCES += PageSpecificationFile.cpp

HEADERS += PageSpecificationData.h
SOURCES += PageSpecificationData.cpp

HEADERS += PagePrecision.h
SOURCES += PagePrecision.cpp

HEADERS += PageIterationInfo.h
SOURCES += PageIterationInfo.cpp

HEADERS += PageIteration.h
SOURCES += PageIteration.cpp

HEADERS += PageFinal.h
SOURCES += PageFinal.cpp

RESOURCES += hydro.qrc

TRANSLATION += hydro_ru.ts

OBJECTS_DIR = temp/obj
MOC_DIR = temp/moc
RCC_DIR = temp/rcc
