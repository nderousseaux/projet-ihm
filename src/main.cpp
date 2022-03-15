#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;

#include "../include/ColorPair.h"
#include "../include/CompareColorPair.h"
#include "../include/XmlReader.h"

int main()
{
    XMLReader reader = XMLReader();
    reader.read("/Users/nderousseaux/Documents/etudes/ecole/superieur/l3_info/s6/ihm_interaction_homme_machine/ihm_tps/exemple_themes/darkTheme.xml");
}
