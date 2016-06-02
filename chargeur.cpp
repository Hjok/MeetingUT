#include "chargeur.h"
#include <QList>
#include "Tour.h"

Chargeur::Chargeur(Meeting& _meeting) : meeting(_meeting)
{

}
ParseurXml::ParseurXml(Meeting &_meeting) : Chargeur(_meeting)
{

}

void ParseurXml::chargeMeeting(QString _chemin)
{
    //Variables tempiraires pour la création des tables
    QString idTable;
    QString labelTable;
    QString capaciteTable;

    //Variables tempraires pour la création des groupes
    QString nomGroupe;
    QString idGroupe;
    QMap<int, QMap<int, int>> interetsGroupes;
    int valeurInteret = -1;
    int groupeConcerne = -1;

    //Variables tempraires pour la création des individus
    QString nomIndividu;
    QString idIndividu;
    QList<int> groupesIndividu;

    //Création du document
    QDomDocument document;
    //Chargement du fichier XML
    QFile file(_chemin);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Si le fichier ne s'ouvre pas/n'existe pas
        throw 0;
    }
    else
    {
        if(!document.setContent(&file))
        {
            //Si le fichier n'est pas un fichier xml valide
            throw 0;
        }
        file.close();
    }
    //Récupération du premier élément du document
    //QDomElement input = document.firstChildElement();
    QDomNode speedMeeting = document.elementsByTagName("speedMeetingInput").at(0);
    QDomNodeList speedMeetingNode = speedMeeting.childNodes();
    for(int i = 0 ; i < speedMeetingNode.size() ; i++)
    {
        QDomNode node = speedMeetingNode.at(i);
        QDomElement currentElement = node.toElement();
        if(currentElement.tagName() == "dataList")
        {
            QDomNode dataList = document.elementsByTagName("dataList").at(0);
            QDomNodeList dataListNode = dataList.childNodes();
            for(int i = 0 ; i < dataListNode.size() ; i++)
            {
                QDomNode nodeDataList = dataListNode.at(i);
                QDomElement currentDataListElement = nodeDataList.toElement();
                //Récupération du nombre de tours
                if(currentDataListElement.tagName() == "tourNumber")
                {
                    meeting.definirNombreTours(currentDataListElement.text().toInt());
                }
                if(currentDataListElement.tagName() == "tableList")
                {
                    QDomNode tableList = document.elementsByTagName("tableList").at(0);
                    QDomNodeList tableListNode = tableList.childNodes();
                    for(int i = 0 ; i < tableListNode.size() ; i++)
                    {
                        QDomNode nodeTableList = tableListNode.at(i);
                        QDomElement currentTableListElement = nodeTableList.toElement();
                        if(currentTableListElement.tagName() == "table")
                        {
                            QDomNode table = currentTableListElement.firstChild();

                            while(!table.isNull())
                            {
                                QDomElement tableElement = table.toElement();
                                //Récupération du nombre de tours
                                if(tableElement.tagName() == "id")
                                {
                                    idTable = tableElement.text();
                                }
                                if(tableElement.tagName() == "label")
                                {
                                    labelTable = tableElement.text();
                                }
                                if(tableElement.tagName() == "capacity")
                                {
                                    capaciteTable = tableElement.text();
                                }
                                table = table.nextSibling();
                            }

                            if(!idTable.isEmpty() && !labelTable.isEmpty() && !capaciteTable.isEmpty())
                            {
                                meeting.ajoutTable(labelTable, capaciteTable.toInt(), idTable.toInt());
                                idTable=QString();
                                labelTable=QString();
                                capaciteTable=QString();
                            }
                        }
                    }
                }
            }
        }
        if(currentElement.tagName() == "groupList")
        {
            QDomNode groupList = document.elementsByTagName("groupList").at(0);
            QDomNodeList groupListNode = groupList.childNodes();
            for(int i = 0 ; i < groupListNode.size() ; i++)
            {
                QDomNode nodeGroupList = groupListNode.at(i);
                QDomElement currentGroupListElement = nodeGroupList.toElement();
                if(currentGroupListElement.tagName() == "group")
                {
                    QDomNode group = currentGroupListElement.firstChild();

                    while(!group.isNull())
                    {
                        QDomElement groupElement = group.toElement();
                        if(groupElement.tagName() == "id")
                        {
                            idGroupe=groupElement.text();
                        }
                        if(groupElement.tagName() == "name")
                        {
                            nomGroupe=groupElement.text();
                        }
                        if(groupElement.tagName() == "interestList")
                        {
                            QDomNode interest = groupElement.firstChild();

                            while(!interest.isNull())
                            {
                                QDomElement interestElement = interest.toElement();
                                if(interestElement.tagName() == "interest")
                                {
                                    QDomNode interestNode = interestElement.firstChild();

                                    while(!interestNode.isNull())
                                    {
                                        QDomElement interestNodeElement = interestNode.toElement();
                                        if(interestNodeElement.tagName() == "id")
                                        {
                                            groupeConcerne = interestNodeElement.text().toInt();
                                        }
                                        if(interestNodeElement.tagName() == "value")
                                        {
                                            valeurInteret = interestNodeElement.text().toInt();
                                        }
                                        interestNode = interestNode.nextSibling();
                                        if(groupeConcerne > -1 && valeurInteret > -1)
                                        {
                                            interetsGroupes[idGroupe.toInt()][groupeConcerne] =  valeurInteret;
                                        }
                                    }
                                }
                                interest = interest.nextSibling();
                            }
                        }
                        group = group.nextSibling();
                    }

                    if(!idGroupe.isEmpty() && !nomGroupe.isEmpty() && !interetsGroupes[idGroupe.toInt()].isEmpty())
                    {
                        meeting.obtenirGroupeManager().ajouterGroupe(nomGroupe, idGroupe.toInt());
                        nomGroupe=QString();
                        idGroupe=QString();
                    }
                }
            }
            meeting.obtenirGroupeManager().definirMatriceInteret(interetsGroupes);
        }
        if(currentElement.tagName() == "personList")
        {
            QDomNode personList = document.elementsByTagName("personList").at(0);
            QDomNodeList personListNode = personList.childNodes();
            for(int i = 0 ; i < personListNode.size() ; i++)
            {
                QDomNode nodePersonList = personListNode.at(i);
                QDomElement currentPersonListElement = nodePersonList.toElement();
                if(currentPersonListElement.tagName() == "person")
                {
                    QDomNode person = currentPersonListElement.firstChild();

                    while(!person.isNull())
                    {
                        QDomElement personElement = person.toElement();
                        if(personElement.tagName() == "id")
                        {
                            idIndividu = personElement.text();
                        }
                        if(personElement.tagName() == "name")
                        {
                            nomIndividu = personElement.text();
                        }
                        if(personElement.tagName() == "groupList")
                        {
                            QDomNode personGroups = personElement.firstChild();

                            while(!personGroups.isNull())
                            {
                                QDomElement personGroupsElement = personGroups.toElement();
                                if(personGroupsElement.tagName()=="group"){
                                    groupesIndividu.append(personGroupsElement.text().toInt());

                                }
                                personGroups = personGroups.nextSibling();
                            }
                        }

                        person = person.nextSibling();
                    }

                    if(!idIndividu.isEmpty() && !nomIndividu.isEmpty() && !groupesIndividu.empty())
                    {
                        meeting.ajoutIndividu(nomIndividu, idIndividu.toInt(), groupesIndividu);
                        idIndividu=QString();
                        nomIndividu=QString();
                        groupesIndividu.clear();
                    }
                }
            }
        }
    }

}
void ParseurXml::chargeSolution(QString _chemin)
{
    //Création du document
    QDomDocument document;
    //Chargement du fichier XML
    QFile file(_chemin);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Si le fichier ne s'ouvre pas/n'existe pas
        throw 0;
    }
    else
    {
        if(!document.setContent(&file))
        {
            //Si le fichier n'est pas un fichier xml valide
            throw 0;
        }
    }

    meeting.nouvelleSolution();
    meeting.obtenirSolution()->print();

    //Variables temporaires pour les rencontres
    QString tableRencontre;
    QString valeurRencontre;
    QList<int> personnesRencontre;

    Tour nouveauTour;

    //Variables temporaires de métadonnées
    QString cleMetaDonnees;
    QString valeurMetaDonnees;

    QDomNode speedMeetingOutput = document.elementsByTagName("speedMeetingOutput").at(0);
    QDomNodeList speedMeetingOutputNode = speedMeetingOutput.childNodes();
    for(int i = 0 ; i < speedMeetingOutputNode.size() ; i++)
    {
        QDomNode node = speedMeetingOutputNode.at(i);
        QDomElement currentElement = node.toElement();
        if(currentElement.tagName() == "tourList")
        {
            QDomNode tourList = document.elementsByTagName("tourList").at(0);
            QDomNodeList tourListNode = tourList.childNodes();
            for(int i = 0 ; i < tourListNode.size() ; i++)
            {
                QDomNode nodeTourList = tourListNode.at(i);
                QDomElement currentTourListElement = nodeTourList.toElement();
                //Récupération du nombre de tours
                if(currentTourListElement.tagName() == "tour")
                {
                    nouveauTour=Tour();
                    //QDomNode tour = document.elementsByTagName("tour").at(0);
                    QDomNodeList tourNode = currentTourListElement.childNodes();
                    for(int i = 0 ; i < tourNode.size() ; i++)
                    {
                        QDomNode nodeTour = tourNode.at(i);
                        /*QDomElement currentTourElement = nodeTour.toElement();
                        if(currentTourElement.tagName() == "tableList")
                        {*/
                            //QDomNode tableList = document.elementsByTagName("tableList").at(0);

                            /*QDomNodeList tableListNode =nodeTour.childNodes();
                            for(int i = 0 ; i < tableListNode.size() ; i++)
                            {
                                QDomNode nodeTableList = tableListNode.at(i);*/
                                QDomElement currentTableListElement = nodeTour.toElement();
                                if(currentTableListElement.tagName() == "table")
                                {
                                    QDomNode table = currentTableListElement.firstChild();

                                    while(!table.isNull())
                                    {
                                        QDomElement tableElement = table.toElement();
                                        if(tableElement.tagName() == "id")
                                        {
                                            tableRencontre= tableElement.text();
                                        }
                                        if(tableElement.tagName() == "value")
                                        {
                                            valeurRencontre = tableElement.text();
                                        }
                                        if(tableElement.tagName() == "personList")
                                        {

                                            QDomNode person = tableElement.firstChild();

                                            while(!person.isNull())
                                            {
                                                QDomElement personElement = person.toElement();
                                                if(personElement.tagName() == "person")
                                                {
                                                    personnesRencontre.append(personElement.text().toInt());
                                                }
                                                person = person.nextSibling();
                                            }
                                        }
                                        table = table.nextSibling();
                                    }
                                }
                                if(!tableRencontre.isEmpty() && !valeurRencontre.isEmpty() && ! personnesRencontre.empty())
                                {
                                    nouveauTour.ajoutRencontre(Rencontre(tableRencontre.toInt(),personnesRencontre, valeurRencontre.toInt()));
                                    personnesRencontre.clear();
                                    tableRencontre=QString();
                                    valeurRencontre=QString();
                                }
                            //}
                        //}
                    }

                    nouveauTour.completerPersonnesNonPlacees();

                    nouveauTour.definirNumeroTour(meeting.obtenirSolution()->obtenirNumeroNouveauTour());
                    meeting.obtenirSolution()->ajoutTour(nouveauTour);
                }
            }

        }
        if(currentElement.tagName() == "metaDataList")
        {
            QDomNode metaDataList = document.elementsByTagName("metaDataList").at(0);
            QDomNodeList metaDataListNode = metaDataList.childNodes();
            for(int i = 0 ; i < metaDataListNode.size() ; i++)
            {
                QDomNode nodeMetaDataList = metaDataListNode.at(i);
                QDomElement currentMetaDataListElement = nodeMetaDataList.toElement();
                //Récupération du nombre de tours
                if(currentMetaDataListElement.tagName() == "metaData")
                {

                    QDomNode metaData =currentMetaDataListElement.firstChild();

                    while(!metaData.isNull())
                    {
                        QDomElement metaDataElement = metaData.toElement();
                        //Récupération du nombre de tours
                        if(metaDataElement.tagName() == "name")
                        {
                            cleMetaDonnees = metaDataElement.text();
                        }
                        if(metaDataElement.tagName() == "value")
                        {
                            valeurMetaDonnees = metaDataElement.text();
                        }

                        metaData = metaData.nextSibling();
                    }
                    if(!cleMetaDonnees.isEmpty() && ! valeurMetaDonnees.isEmpty())
                    {
                        Meeting::obtenirenirInstance().obtenirSolution()->obtenirMetaDonnees()[cleMetaDonnees]=valeurMetaDonnees;
                        cleMetaDonnees=QString();
                        valeurMetaDonnees=QString();
                    }
                }
            }
        }
    }
    meeting.solutionConstruite();
}
void ParseurXml::sauveMeeting(QString _chemin)
{
    QMap<int, int> interets;
    QMap<int, int>::iterator j;
    QFile fichier(_chemin);
    fichier.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&fichier);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("speedMeetingInput");


    xmlWriter.writeStartElement("dataList");
    xmlWriter.writeTextElement("tourNumber", QString::number(meeting.obtenirNombreTours()));
    xmlWriter.writeStartElement("tableList");
    //Liste des tables
    for(int i=0; i<meeting.obtenirTables().length(); i++)
    {
        xmlWriter.writeStartElement("table");
        xmlWriter.writeTextElement("id", QString::number(meeting.obtenirTables().at(i).obtenirId()));
        xmlWriter.writeTextElement("label", meeting.obtenirTables().at(i).obtenirLabel());
        xmlWriter.writeTextElement("capacity", QString::number(meeting.obtenirTables().at(i).obtenirNombreDePlaces()));
        xmlWriter.writeEndElement();
    }
    //End tableList
    xmlWriter.writeEndElement();
    //End dataList
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("groupList");

    for(int i=0; i<meeting.obtenirGroupeManager().obtenirGroupes().length(); i++)
    {
        xmlWriter.writeStartElement("group");
        xmlWriter.writeTextElement("id", QString::number(meeting.obtenirGroupeManager().obtenirGroupes().at(i).obtenirId()));
        xmlWriter.writeTextElement("name", meeting.obtenirGroupeManager().obtenirGroupes().at(i).obtenirNom());
        xmlWriter.writeStartElement("interestList");
        interets=meeting.obtenirGroupeManager().obtenirListeInteretIds(&(meeting.obtenirGroupeManager().obtenirGroupes().at(i)));
        for(j=interets.begin(); j!= interets.end(); ++j)
        {
            xmlWriter.writeStartElement("interest");
            xmlWriter.writeTextElement("id", QString::number(j.key()));
            xmlWriter.writeTextElement("value", QString::number(j.value()));
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }


    //End groupList
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement("personList");
    for(int i=0; i<meeting.obtenirIndividus().length(); i++)
    {
        xmlWriter.writeStartElement("person");
        xmlWriter.writeTextElement("id", QString::number(meeting.obtenirIndividus()[i].obtenirId()));
        xmlWriter.writeTextElement("name", meeting.obtenirIndividus()[i].obtenirNom());
        xmlWriter.writeStartElement("groupList");
        for(int k=0; k<meeting.obtenirIndividus()[i].obtenirGroupes().length(); k++)
        {
            xmlWriter.writeTextElement("group", QString::number(meeting.obtenirIndividus()[i].obtenirGroupes()[k]->obtenirId()));
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    //End speedMeetingInput
    xmlWriter.writeEndElement();

        fichier.close();
}
